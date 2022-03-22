
#include "vm64.h"
#include "video64bit.h"
#include "error64.h"

#include "tr.h"
#include "msr.h"
#include "vm64_host.h"
#include "vm64_guest.h"
#include "vm64_control.h"
#include "vm64_helpers.h"
#include "status_operations64.h"
#include "interrupt64.h"

#define VMsucceed (1<<0 | 1<<2 | 1<<4 | 1<<6 | 1<<7 | 1<<11)
#define VMfailinvalid (1<<2 | 1<<4 | 1<<6 | 1<<7 | 1<<11)

static void vmx_save_host_state();
static void vmx_prepare_guest_state();
static void vmx_configure_control_fields();
static void vmx_set_default_controls_values();

/**
 * Ensure validity of CR0 and CR4 value for HOST
 * state area in VMCS.
 *
 * See Intel Manual Vol. 3
 *  [25.2.2 Checks on Host Control Registers, MSRs, and SSP]
 *  +The CR0 field must not set any bit to a value not
 *   supported in VMX operation (see Section 22.8).
 *  +The CR4 field must not set any bit to a value not
 *   supported in VMX operation (see Section 22.8).
 *  +If bit 23 in the CR4 field (corresponding to CET)
 *   is 1, bit 16 in the CR0 field (WP) must also be 1.
 */
static void test_cr0_and_cr4(unsigned long cr0, unsigned long cr4)
{
    long test;
    if ((test = vmx_validate_cr0(cr0)))
    {
        putstr64("CRO BAD: "); puthex64(test); newline64();
        putstr64("my CRO:  "); puthex64(cr0); newline64();
        panic64("INVALID CR0");
    }
    if ((test = vmx_validate_cr4(cr4)))
    {
        putstr64("CR4 BAD: "); puthex64(test); newline64();
        putstr64("my CR4:  "); puthex64(cr4); newline64();
        panic64("INVALID CR4");
    }
    const long CR4_CET = 1L << 23;
    const long CR0_WP = 1L << 16;
    if (cr4 & CR4_CET && !(cr0 & CR0_WP))
    {
        panic64("CR4.CET and not CR0.WT");
    }
}

/**
 * Return 0 if selector is ok, nonzero otherwise.
 * See Intel Manual Vol. 3
 *  [25.2.3 Checks on Host Segment and Descriptor-Table Registers]
 *  The following checks are performed on fields in the
 *  host-state area that correspond to segment and
 *  descriptortable registers:
 *      +In the selector field for each of CS, SS, DS,
 *       ES, FS, GS and TR, the RPL (bits 1:0) and the
 *       TI flag (bit 2) must be 0.
 *      +The selector fields for CS and TR cannot be
 *       0000H.
 *      +The selector field for SS cannot be 0000H if
 *       the “host address-space size” VM-exit control
 *       is 0.
 *  On processors that support Intel 64 architecture,
 *  the base-address fields for FS, GS, GDTR, IDTR, and
 *  TR must contain canonical addresses.
 */
static int test_selector(unsigned short sel)
{
    const unsigned short RPL = (1 << 1) | (1 << 0);
    const unsigned short TI  =  1 << 2;
    if (sel & RPL)
        return 1;
    if (sel & TI)
        return 1;
    return 0;
}

static int vmx_success(int status)
{
    return !status;
}

static int vmx_fail_invalid(int status)
{
    // CF == 1, other are 0
    return status == 1;
}

int start_vm()
{
    int status;

    if (check_vm_support())
    {
        printline64("VMX supported!");
    }
    else
    {
        panic64("VMX not supported!");
    }
    printline64("Ciaooooooooooooo");
    putstr64("Rev Id = "); putu64(read_vmcs_revision_identifier()); newline64();
    putstr64("VMX    = "); putl64(read_IA32_VMX_BASIC()); newline64();
    set_cr4_vmxe();
    printline64("CR4.VMXE set!");
    void *vmx_region = get_vmx_region();
    putstr64("vmx_region = "); puthex64((unsigned long)vmx_region); newline64();
    putstr64("vmx_region = "); puti64((unsigned long)vmx_region); newline64();
    putstr64("*vmx_region = "); puthex64(*(unsigned long*)vmx_region); newline64();

    status = enter_vmx(vmx_region);
    if (!vmx_success(status))
    {
        printline64("enter_vmx failed!");
        if (vmx_fail_invalid(status))
        {
            panic64("vmx_fail_invalid");
        }
    }

    printline64("enter_vmx success");
    void *vmcs_region = get_vmcs_region();
    /**
     * See Intel Manual Vol. 3
     *  [23.11.3 Initializing a VMCS]
     *  In addition to its other functions, the VMCLEAR instruction
     *  initializes any implementation-specific information in
     *  the VMCS region referenced by its operand. To avoid the
     *  uncertainties of implementation-specific behavior, software
     *  should execute VMCLEAR on a VMCS region before making the
     *  corresponding VMCS active with VMPTRLD for the first time.
     *  (Figure 23-1 illustrates how execution of VMCLEAR puts a
     *  VMCS into a well-defined state.)
     */
    status = vmx_clear_vmcs(vmcs_region);
    if (!vmx_success(status))
    {
        panic64("vmx_clear_vmcs");
    }
    status = vmx_enable_vmcs_region(vmcs_region);
    if (!vmx_success(status))
    {
        panic64("Disaster VMPTRLD");
    }
    printline64("VMCS region enabled!");

    vmx_set_default_controls_values();

    printline64("Saving host state... ");
    vmx_save_host_state();
    printline64("DONE!");

    printline64("Preparing guest state... ");
    vmx_prepare_guest_state();
    printline64("DONE!");

    putstr64("Configuring VMCS control fields... ");
    vmx_configure_control_fields();
    printline64("DONE!");

    printline64("Launcing VMCS...");
    status = vmx_launch_current_vmcs();
    putstr64("status = "); puti64(status); newline64();
    putstr64("abort status = "); puti64(vmx_get_vmcs_region_abort_status(vmcs_region)); newline64();
    putstr64("exit reason = "); puti64(vmx_read_vm_exit_reason()); newline64();
    {
        int er = vmx_read_vm_instruction_error();
        putstr64("vm error = ");
        puti64(er);
        if (er)
        {
            putstr64(" [");
            putstr64(vmx_error_reason(er));
            putstr64("]");
        }
        newline64();
    }
    // status = vmx_clear_vmcs(vmcs_region);
    // if (!vmx_success(status))
    // {
    //     panic64("Disaster VMCLEAR");
    // }
    // printline64("VMCS successfully cleared!");

    printline64("Paninooo");

    return 0;
}

/**
 * See Intel Manual Vol. 3
 *  [26.5.1 Loading Host Control Registers, Debug Registers, MSRs]
 *  VM exits load new values for controls registers, debug registers,
 *  and some MSRs:
 *  [...]
 *      -CR0, CR3, and CR4 [...]
 *      -DR7 is set to 400H
 *      -The following MSRs are established as follows:
 *          -The IA32_DEBUGCTL MSR is cleared to 00000000_00000000H.
 *          -The IA32_SYSENTER_CS MSR is loaded from the IA32_SYSENTER_CS
 *           field. Since that field has only 32 bits, bits 63:32 of the
 *           MSR are cleared to 0.
 *          -The IA32_SYSENTER_ESP and IA32_SYSENTER_EIP MSRs are loaded
 *           from the IA32_SYSENTER_ESP and IA32_SYSENTER_EIP fields,
 *           respectively.
 *          -The following steps are performed on processors that
 *           support Intel 64 architecture:
 *              +The MSRs FS.base and GS.base are loaded from the
 *               base-address fields for FS and GS, respectively
 *               (see Section 26.5.2).
 *              +The LMA and LME bits in the IA32_EFER MSR are each loaded
 *               with the setting of the “host address-space size”
 *               VM-exit control.
 *          -If the “load IA32_PERF_GLOBAL_CTRL” VM-exit control is 1,
 *           the IA32_PERF_GLOBAL_CTRL MSR is loaded from the
 *           IA32_PERF_GLOBAL_CTRL field. Bits that are reserved in that
 *           MSR are maintained with their reserved values.
 *          -If the “load IA32_PAT” VM-exit control is 1, the IA32_PAT
 *           MSR is loaded from the IA32_PAT field. Bits that are reserved
 *           in that MSR are maintained with their reserved values.
 *          -If the “load IA32_EFER” VM-exit control is 1, the IA32_EFER
 *           MSR is loaded from the IA32_EFER field. Bits that are reserved
 *           in that MSR are maintained with their reserved values.
 *          -If the “clear IA32_BNDCFGS” VM-exit control is 1, the
 *           IA32_BNDCFGS MSR is cleared to 00000000_00000000H;
 *           otherwise, it is not modified.
 *          -If the “clear IA32_RTIT_CTL” VM-exit control is 1, the
 *           IA32_RTIT_CTL MSR is cleared to 00000000_00000000H;
 *           otherwise, it is not modified.
 *          -If the “load CET” VM-exit control is 1, the IA32_S_CET and
 *           IA32_INTERRUPT_SSP_TABLE_ADDR MSRs are loaded from the
 *           IA32_S_CET and IA32_INTERRUPT_SSP_TABLE_ADDR fields,
 *           respectively.
 *          -If the “load PKRS” VM-exit control is 1, the IA32_PKRS MSR is
 *           loaded from the IA32_PKRS field. Bits 63:32 of that MSR are
 *           maintained with zeroes.
 *  [...]
 *
 *  [26.5.2 Loading Host Segment and Descriptor-Table Registers]
 *  Each of the registers CS, SS, DS, ES, FS, GS, and TR is loaded as
 *  follows (see below for the treatment of LDTR):.
 *  [...]
 *
 *  [26.5.3 Loading Host RIP, RSP, RFLAGS, and SSP]
 *  RIP and RSP are loaded from the RIP field and the RSP field,
 *  respectively. RFLAGS is cleared, except bit 1, which is always set.
 *  If the “load CET” VM-exit control is 1, SSP (shadow-stack pointer)
 *  is loaded from the SSP field.
 */
static void vmx_save_host_state()
{
    unsigned short limit;
    void *ptr;

    if (store_idt_register((struct idt_gate_descriptor **)&ptr, &limit))
    {
        panic64("store_idt_register");
    }
    if (vmx_host_write_idtr_base((long)ptr))
        panic64("vmx_host_write_idtr_base");

    if (so_read_gdtr(&ptr, &limit))
    {
        panic64("so_read_gdtr");
    }
    if(vmx_host_write_gdtr_base((long)ptr))
        panic64("vmx_host_write_gdtr_base");
    /* TR not used, is this valid? */
    const long tss = (long)xdt_read_address(ptr, so_read_tr());
    if(vmx_host_write_tr_base(tss))
        panic64("vmx_host_write_tr_base");

    /**
     * See Intel Manual Vol. 3
     *  [25.2.3 Checks on Host Segment and Descriptor-Table Registers]
     *  The following checks are performed on fields in the
     *  host-state area that correspond to segment and descriptor
     *  table registers:
     */
    /* 16 bits host state field */
    /* Save segment selectors */
    {
        long sel = so_read_cs();
        if (test_selector(sel) || !sel)
            panic64("Invalid cs!");
        if (vmx_host_write_cs(sel))
            panic64("vmx_host_write_cs");
    }
    {
        long sel = so_read_ds();
        if (test_selector(sel))
            panic64("Invalid ds!");
        if (vmx_host_write_ds(sel))
            panic64("vmx_host_write_ds");
    }
    {
        long sel = so_read_ss();
        if (test_selector(sel))
            panic64("Invalid ss!");
        if (vmx_host_write_ss(sel))
            panic64("vmx_host_write_ss");
    }
    {
        long sel = so_read_es();
        if (test_selector(sel))
            panic64("Invalid es!");
        if (vmx_host_write_es(sel))
            panic64("vmx_host_write_es");
    }
    {
        long sel = so_read_fs();
        if (test_selector(sel))
            panic64("Invalid fs!");
        if (vmx_host_write_fs(sel))
            panic64("vmx_host_write_fs");
    }
    {
        long sel = so_read_gs();
        if (test_selector(sel))
            panic64("Invalid gs!");
        if (vmx_host_write_gs(sel))
            panic64("vmx_host_write_gs");
    }
    {
        long sel = so_read_tr();
        if (test_selector(sel) || !sel)
            panic64("Invalid tr!");
        if (vmx_host_write_tr(sel))
            panic64("vmx_host_write_tr");
    }

    if (vmx_host_write_fs_base(msr_read_ia32_fs_base()))
        panic64("vmx_host_write_fs_base");
    if (vmx_host_write_gs_base(msr_read_ia32_gs_base()))
        panic64("vmx_host_write_gs_base");

    /**
     * See Intel Manual Vol. 3
     *  [25.2.2 Checks on Host Control Registers, MSRs, and SSP]
     */
    test_cr0_and_cr4(so_read_cr0(), so_read_cr4());
    /* Save control registers */
    if (vmx_host_write_cr0(so_read_cr0()))
        panic64("vmx_host_write_cr0");
    if (vmx_host_write_cr3(so_read_cr3()))
        panic64("vmx_host_write_cr3");
    if (vmx_host_write_cr4(so_read_cr4()))
        panic64("vmx_host_write_cr4");


    /* 32 bit field */
    if (vmx_host_write_ia32_sysenter_cs(msr_read_ia32_sysenter_cs()))
        panic64("vmx_host_write_ia32_sysenter_cs");

    /* syscall */
    if (vmx_host_write_ia32_sysenter_esp(msr_read_ia32_sysenter_esp()))
        panic64("vmx_host_write_ia32_sysenter_esp");
    if (vmx_host_write_ia32_sysenter_eip(msr_read_ia32_sysenter_eip()))
        panic64("vmx_host_write_ia32_sysenter_eip");

    //vmx_host_write_ia32_pat(msr_read_ia32_pat());
    //vmx_host_write_ia32_efer(msr_read_ia32_efer());
    //vmx_host_write_ia32_perf_global_ctrl(msr_read_ia32_ia32_perf_global_ctrl());

    // msr_read_ia32_pkrs gives a #GP exception!
    //vmx_host_write_ia32_pkrs(msr_read_ia32_pkrs());
}

static void vmx_prepare_guest_state()
{
    unsigned short limit;
    void *ptr;

    if (store_idt_register((struct idt_gate_descriptor **)&ptr, &limit))
    {
        panic64("store_idt_register");
    }
    vmx_guest_write_idtr_base((long)ptr);
    vmx_guest_write_idtr_limit(limit);

    vmx_guest_write_ldtr_base(0L);
    vmx_guest_write_ldtr_limit(0L);

    if (so_read_gdtr(&ptr, &limit))
    {
        panic64("so_read_gdtr");
    }
    vmx_guest_write_gdtr_base((long)ptr);
    vmx_guest_write_gdtr_limit(limit);

    vmx_guest_write_ldtr_base(0L);
    const long tss = (long)xdt_read_address(ptr, so_read_tr());
    vmx_guest_write_tr_base(tss);
    /**
     * See Intel Manual Vol. 1
     *  [Figure 3-8. EFLAGS Register]
     *  Bit 1 must be set in EFLAGS.
     */
    vmx_guest_write_rflags(2);

    /* Set guest RSP and RIP */
    vmx_guest_write_rsp((long)vmx_get_guest_stack());
    vmx_guest_write_rip((long)vmx_get_guest_code());

    /* Set guest control registers */
    vmx_guest_write_cr0(so_read_cr0());
    vmx_guest_write_cr3(so_read_cr3());
    vmx_guest_write_cr4(so_read_cr4());


    vmx_guest_write_dr7(so_read_dr7());

    /* Set guest segment registers */
    /* CS */
    vmx_guest_write_cs((long)so_read_cs());
    vmx_guest_write_cs_base(0L);
    vmx_guest_write_cs_limit(-1L);
    /* DS */
    vmx_guest_write_ds((long)so_read_ds());
    vmx_guest_write_ds_base(0L);
    vmx_guest_write_ds_limit(-1L);
    /* SS */
    vmx_guest_write_ss((long)so_read_ss());
    vmx_guest_write_ss_base(0L);
    vmx_guest_write_ss_limit(-1L);
    /* ES */
    vmx_guest_write_es((long)so_read_es());
    vmx_guest_write_es_base(0L);
    vmx_guest_write_es_limit(-1L);
    /* FS */
    vmx_guest_write_fs((long)so_read_fs());
    vmx_guest_write_fs_base(0L);
    vmx_guest_write_fs_limit(-1L);
    /* GS */
    vmx_guest_write_gs((long)so_read_gs());
    vmx_guest_write_gs_base(0L);
    vmx_guest_write_gs_limit(-1L);

    vmx_guest_write_ldtr_selector(0L);
    vmx_guest_write_tr_selector(so_read_tr());

    /* syscall */
    vmx_guest_write_ia32_sysenter_esp(msr_read_ia32_sysenter_esp());
    vmx_guest_write_ia32_sysenter_eip(msr_read_ia32_sysenter_eip());

    /**
     * Access rights
     *
     * See Intel Manual Vol. 2
     *  [23.4.1 Guest Register State]
     *  The following fields for each of the registers
     *  CS, SS, DS, ES, FS, GS, LDTR, and TR:
     *      [...]
     *      -Access rights (32 bits). The format of this field
     *       is given in Table 23-2 and detailed as follows:
     *          +The low 16 bits correspond to bits 23:8 of the upper
     *           32 bits of a 64-bit segment descriptor. While bits
     *           19:16 of code-segment and data-segment descriptors
     *           correspond to the upper 4 bits of the segment limit,
     *           the corresponding bits (bits 11:8) are reserved in
     *           this VMCS field.
     *          [...]
     *
     * See Intel Manual Vol. 3
     *  [Table 23-2. Format of Access Rights]
     *  Bit Position(s) Field
     *  3:0             Segment type
     *  4               S — Descriptor type (0 = system; 1 = code or data)
     *  6:5             DPL — Descriptor privilege level
     *  7               P — Segment present
     *  11:8            Reserved
     *  12              AVL — Available for use by system software
     *  13              Reserved (except for CS)
     *                   L — 64-bit mode active (for CS only)
     *  14              D/B — Default operation size (0 = 16-bit segment;
     *                   1 = 32-bit segment)
     *  15              G — Granularity
     *  16              Segment unusable (0 = usable; 1 = unusable)
     *  31:17           Reserved
     *
     * Segment types:
     * See Intel Manual Vol. 3
     *  [3.4.5 Segment Descriptors]
     * and
     *  [3.4.5.1 Code- and Data-Segment Descriptor Types]
     * From
     *  [Table 3-1. Code- and Data-Segment Types]
     *  Type Field  Descriptor Type Description
     *  2           Data            Read/Write
     *  10          Code            Execute/Read
     */
    {
        const int offset_type   = 0;
        const int offset_S      = 4;
        const int offset_DPL    = 5;
        const int offset_P      = 7;
        const int offset_L      = 13; // Long mode code
        const int offset_DB     = 14; // Default operand size

        const int code_access   = (10 << offset_type)
                                | (0 << offset_S)
                                | (0 << offset_DPL)
                                | (1 << offset_P)
                                | (1 << offset_L)
                                | (0 << offset_DB);

        const int data_access   = (2 << offset_type)
                                | (0 << offset_S)
                                | (0 << offset_DPL)
                                | (1 << offset_P)
                                | (0 << offset_L)
                                | (0 << offset_DB);

        vmx_guest_write_es_access_rights(code_access);
        vmx_guest_write_cs_access_rights(data_access);
        vmx_guest_write_ss_access_rights(data_access);
        vmx_guest_write_ds_access_rights(data_access);
        vmx_guest_write_fs_access_rights(data_access);
        vmx_guest_write_gs_access_rights(data_access);
    }

    {
        /**
         * See Intel Manaul Vol. 3
         *  [23.4.2 Guest Non-Register State]
         */
        /**
         *  Activity state (32 bits). This field identifies the
         *   logical processor’s activity state. When a logical
         *   processor is executing instructions normally, it is
         *   in the active state. Execution of certain instructions
         *   and the occurrence of certain events may cause a logical
         *   processor to transition to an inactive state in which it
         *   ceases to execute instructions.
         *
         *  The following activity states are defined:
         *      -0: Active. The logical processor is executing
         *       instructions normally.
         *      -1: HLT. The logical processor is inactive because
         *       it executed the HLT instruction.
         *      -2: Shutdown. The logical processor is inactive
         *       because it incurred a triple fault 2 or some other
         *       serious error.
         *      -3: Wait-for-SIPI. The logical processor is inactive
         *       because it is waiting for a startup-IPI (SIPI).
         */
        vmx_guest_write_activity_state(0);
        /**
         *  Interruptibility state (32 bits). The IA-32 architecture
         *   includes features that permit certain events to be blocked
         *   for a period of time. This field contains information about
         *   such blocking. Details and the format of this field are
         *   given in Table 23-3.
         */
        vmx_guest_write_interruptibility_state(0);
        /**
         *  Pending debug exceptions (64 bits; 32 bits on processors
         *   that do not support Intel 64 architecture). IA-32
         *   processors may recognize one or more debug exceptions
         *   without immediately delivering them. 1 This field contains
         *   information about such exceptions. This field is described
         *   in Table 23-4.
         */
        vmx_guest_write_pending_debug_exceptions(0);
        /**
         *  VMCS link pointer (64 bits). If the “VMCS shadowing”
         *   VM-execution control is 1, the VMREAD and VMWRITE
         *   instructions access the VMCS referenced by this pointer
         *   (see Section 23.10). Otherwise, software should set this
         *   field to FFFFFFFF_FFFFFFFFH to avoid VM-entry failures
         *   (see Section 25.3.1.5).
         */
        vmx_guest_write_vmcs_link_pointer(-1L);
        /**
         *  VMX-preemption timer value (32 bits). This field is
         *   supported only on processors that support the 1-setting
         *   of the “activate VMX-preemption timer” VM-execution
         *   control. This field contains the value that the
         *   VMX-preemption timer will use following the next VM entry
         *   with that setting. See Section 24.5.1 and Section 25.7.4.
         */
        vmx_guest_write_vmx_preemption_timer_value(0L);
        /**
         *  Page-directory-pointer-table entries (PDPTEs; 64 bits each).
         *   These four (4) fields (PDPTE0, PDPTE1, PDPTE2, and PDPTE3)
         *   are supported only on processors that support the 1-setting
         *   of the “enable EPT” VM-execution control. They correspond
         *   to the PDPTEs referenced by CR3 when PAE paging is in use
         *   (see Section 4.4 in the Intel® 64 and IA-32 Architectures
         *   Software Developer’s Manual, Volume 3A). They are used only
         *   if the “enable EPT” VM-execution control is 1.
         */
        /***** NOT USED *****/

        /**
         * Guest interrupt status (16 bits). This field is supported
         *  only on processors that support the 1-setting of the
         *  “virtual-interrupt delivery” VM-execution control. It
         *  characterizes part of the guest’s virtual-APIC state and
         *  does not correspond to any processor or APIC registers.
         *  It comprises two 8-bit subfields:
         *      -Requesting virtual interrupt (RVI). This is the low
         *       byte of the guest interrupt status. The processor
         *       treats this value as the vector of the highest priority
         *       virtual interrupt that is requesting service. (The
         *       value 0 implies that there is no such interrupt.)
         *      -Servicing virtual interrupt (SVI). This is the high byte
         *       of the guest interrupt status. The processor treats this
         *       value as the vector of the highest priority virtual
         *       interrupt that is in service. (The value 0 implies
         *       that there is no such interrupt.)
         *  See Chapter 28 for more information on the use of this field.
         */
        /***** NOT USED *****/

        /**
         *  PML index (16 bits). This field is supported only on
         *   processors that support the 1-setting of the “enable PML”
         *   VM-execution control. It contains the logical index of
         *   the next entry in the page-modification log. Because the
         *   page-modification log comprises 512 entries, the PML index
         *   is typically a value in the range 0–511. Details of the
         *   page-modification log and use of the PML index are given
         *   in Section 27.2.6.
         */
        vmx_guest_write_pml_index(0L);
    }
}

/**
 * See Intel manual Vol. 3
 *  [23.2 FORMAT OF THE VMCS REGION]
 */
int vmx_get_vmcs_region_abort_status(void *vmcs_region)
{
    return !vmcs_region ? -1 : *(1 + (int *)vmcs_region);
}

int vmx_vmcs_field_encoding(enum vmx_vmcs_field_access_type access, int index, enum vmx_vmcs_field_type type, enum vmx_vmcs_field_width width)
{
    if (! ((access & 1) == access && (index & 0x1ff) == index
        && (type & 3) == type && (width & 3) == width) )
    {
        return -1;
    }
    return access | index << 1 | type << 10 | width << 13;
}

/**
 * To be called on a VMCS before lauch to correctly
 * initialize fields to default values.
 *
 * See Intel Manual Vol. 3
 *  [A.2 RESERVED CONTROLS AND DEFAULT SETTINGS]
 *  As noted in Chapter 25, “VM Entries”, certain VMX controls
 *  are reserved and must be set to a specific value (0 or 1)
 *  determined by the processor. The specific value to which a
 *  reserved control must be set is its default setting.
 *
 *  Software can discover the default setting of a reserved control
 *  by consulting the appropriate VMX capability MSR
 *  (see Appendix A.3 through Appendix A.5).
 *
 * Maybe will be used to set VMCS fields to use optional processor-
 * dependent functionalities.
 */
static void vmx_set_default_controls_values()
{
    int test = (read_IA32_VMX_BASIC() >> 55) & 1;
    if (test == 0)
    {
        /**
         * See Intel Manual Vol. 3
         *  [A.2 RESERVED CONTROLS AND DEFAULT SETTINGS]
         *  If bit 55 of the IA32_VMX_BASIC MSR is read as 0, all
         *  the default1 controls are reserved and must be 1.
         *  VM entry will fail if any of these controls are 0
         *  (see Section 25.2.1).
         */
        printline64("    test = 0");
    }
    else
    {
        /**
         * See Intel Manual Vol. 3
         *  [A.2 RESERVED CONTROLS AND DEFAULT SETTINGS]
         *  If bit 55 of the IA32_VMX_BASIC MSR is read as 0, all
         *  the default1 controls are reserved and must be 1.
         *  VM entry will fail if any of these controls are 0
         *  (see Section 25.2.1).
         */
        printline64("    test = 1");
    }
}


static void vmx_configure_control_fields()
{
    {
        long ctls;
        /**
         * VM execution control fields
         *
         * See Intel Manual Vol. 3
         *  [23.6 VM-EXECUTION CONTROL FIELDS]
         *  The VM-execution control fields govern VMX non-root
         *  operation. These are described in Section 23.6.1 through
         *  Section 23.6.8.
         */
        /**
         *  [23.6.1 Pin-Based VM-Execution Controls]
         *  The pin-based VM-execution controls constitute a 32-bit
         *  vector that governs the handling of asynchronous events
         *  (for example: interrupts). 1 Table 23-5 lists the controls.
         *  See Chapter 26 for how these controls affect processor
         *  behavior in VMX non-root operation.
         *
         *  All other bits in this field are reserved, some to 0 and
         *  some to 1. Software should consult the VMX capability MSRs
         *  IA32_VMX_PINBASED_CTLS and IA32_VMX_TRUE_PINBASED_CTLS (see
         *  Appendix A.3.1) to determine how to set reserved bits.
         *  Failure to set reserved bits properly causes subsequent VM
         *  entries to fail (see Section 25.2.1.1).
         */
        ctls = msr_read_ia32_vmx_pinbased_ctls();
        /**
         * See Intel Manual Vol. 3
         *  [A.3.1 Pin-Based VM-Execution Controls]
         *  The IA32_VMX_PINBASED_CTLS MSR (index 481H) reports on the
         *  allowed settings of most of the pin-based VM-execution
         *  controls (see Section 23.6.1):
         *      -Bits 31:0 indicate the allowed 0-settings of these
         *       controls. VM entry allows control X (bit X of the
         *       pin-based VM-execution controls) to be 0 if bit X in
         *       the MSR is cleared to 0; if bit X in the MSR is set to
         *       1, VM entry fails if control X is 0.
         *      -Bits 63:32 indicate the allowed 1-settings of these
         *       controls. VM entry allows control X to be 1 if bit 32+X
         *       in the MSR is set to 1; if bit 32+X in the MSR is
         *       cleared to 0, VM entry fails if control X is 1.
         */
        vmx_write_pin_based_vm_execution_controls(ctls & (ctls >> 32));
        /**
         *  [23.6.2 Processor-Based VM-Execution Controls]
         * See also
         *  [Table 23-6. Definitions of Primary Processor-Based VM-Execution Controls]
         *  Bit Position(s) Name            Description
         *  7               HLT exiting     This control determines
         *                                   whether executions of HLT
         *                                   cause VM exits.
         *  [...]
         *  31              Activate        This control determines
         *                   secondary       whether the secondary
         *                   controls        processor-based VM-
         *                                   execution controls are
         *                                   used. If this control is 0,
         *                                   the logical processor
         *                                   operates as if all the
         *                                   secondary processor-based
         *                                   VM-execution controls were
         *                                   also 0.
         *
         *  All other bits in this field are reserved, some to 0 and
         *  some to 1. Software should consult the VMX capability MSRs
         *  IA32_VMX_PROCBASED_CTLS and IA32_VMX_TRUE_PROCBASED_CTLS
         *  (see Appendix A.3.2) to determine how to set reserved bits.
         *  Failure to set reserved bits properly causes subsequent VM
         *  entries to fail (see Section 25.2.1.1).
         */
        ctls = msr_read_ia32_vmx_procbased_ctls();
        vmx_write_primary_processor_based_vm_execution_controls(
            (1L << 7) // HLT cause exiting
            | (ctls & (ctls >> 32))
        );
        /**
         *  [23.6.3 Exception Bitmap]
         *  The exception bitmap is a 32-bit field that contains one bit
         *  for each exception. When an exception occurs, its vector is
         *  used to select a bit in this field. If the bit is 1, the
         *  exception causes a VM exit. If the bit is 0, the exception
         *  is delivered normally through the IDT, using the descriptor
         *  corresponding to the exception’s vector.
         */
        vmx_write_exception_bitmap(0L);
        /**
         *  [23.6.4 I/O-Bitmap Addresses]
         *  A logical processor uses these bitmaps if and only if the
         *  “use I/O bitmaps” control is 1.
         */
        /***** NOT USED *****/
        /**
         *  [23.6.5 Time-Stamp Counter Offset and Multiplier]
         *  If the “RDTSC exiting” control is 0 and the “use TSC
         *  offsetting” control is 1, this field controls executions of
         *  the RDTSC and RDTSCP instructions.
         */
        /***** NOT USED *****/
        /**
         *  [23.6.6 Guest/Host Masks and Read Shadows for CR0 and CR4]
         *  VM-execution control fields include guest/host masks and
         *  read shadows for the CR0 and CR4 registers. These fields
         *  control executions of instructions that access those
         *  registers (including CLTS, LMSW, MOV CR, and SMSW). They
         *  are 64 bits on processors that support Intel 64 architecture
         *  and 32 bits on processors that do not.
         *
         *  In general, bits set to 1 in a guest/host mask correspond
         *  to bits “owned” by the host:
         *      -Guest attempts to set them (using CLTS, LMSW, or MOV to
         *       CR) to values differing from the corresponding bits in
         *       the corresponding read shadow cause VM exits.
         *      -Guest reads (using MOV from CR or SMSW) return values
         *       for these bits from the corresponding read shadow.
         *  Bits cleared to 0 correspond to bits “owned” by the guest;
         *  guest attempts to modify them succeed and guest reads
         *  return values for these bits from the control register
         *  itself.
         *
         * See Chapter 26 for details regarding how these fields affect
         *  VMX non-root operation.
         */
        vmx_write_cr0_guest_host_mask(0L);
        vmx_write_cr4_guest_host_mask(0L);
        vmx_write_cr0_read_shadow(0L);
        vmx_write_cr4_read_shadow(0L);
        /**
         *  [23.6.7 CR3-Target Controls]
         *  An execution of MOV to CR3 in VMX non-root operation does
         *  not cause a VM exit if its source operand matches one of
         *  these values. If the CR3-target count is n, only the first
         *  n CR3-target values are considered; if the CR3-target count
         *  is 0, MOV to CR3 always causes a VM exit
         */
        vmx_read_cr3_target_count(0L);
        /**
         *  [23.6.8 Controls for APIC Virtualization]
         */
        /***** NOT USED *****/
        /**
         *  [23.6.9 MSR-Bitmap Address]
         *  On processors that support the 1-setting of the “use MSR
         *  bitmaps” VM-execution control, the VM-execution control
         *  fields include the 64-bit physical address of four
         *  contiguous MSR bitmaps, which are each 1-KByte in size.
         *  This field does not exist on processors that do not support
         *  the 1-setting of that control.
         */
        /***** NOT USED *****/
        /**
         *  [23.6.11 Extended-Page-Table Pointer (EPTP)]
         *  The extended-page-table pointer (EPTP) contains the address
         *  of the base of EPT PML4 table (see Section 27.2.2), as well
         *  as other EPT configuration information. The format of this
         *  field is shown in Table 23-9.
         */
        /***** NOT USED *****/
        /**
         *  [23.6.12 Virtual-Processor Identifier (VPID)]
         *  The virtual-processor identifier (VPID) is a 16-bit field.
         *  It exists only on processors that support the 1-setting of
         *  the “enable VPID” VM-execution control. See Section 27.1
         *  for details regarding the use of this field.
         */
        /***** NOT USED *****/
        /**
         *  [23.6.13 Controls for PAUSE-Loop Exiting]
         *  On processors that support the 1-setting of the “PAUSE-loop
         *  exiting” VM-execution control, the VM-execution control fields
         *  include the following 32-bit fields:
         *      -PLE_Gap. Software can configure this field as an upper
         *       bound on the amount of time between two successive
         *       executions of PAUSE in a loop.
         *      -PLE_Window. Software can configure this field as an
         *       upper bound on the amount of time a guest is allowed
         *       to execute in a PAUSE loop.
         *  These fields measure time based on a counter that runs at
         *  the same rate as the timestamp counter (TSC). See Section
         *  24.1.3 for more details regarding PAUSE-loop exiting.
         */
        /***** NOT USED *****/
        /**
         *  [23.6.14 VM-Function Controls]
         *  The VM-function controls constitute a 64-bit vector that
         *  governs use of the VMFUNC instruction in VMX non-root
         *  operation. This field is supported only on processors that
         *  support the 1-settings of both the “activate secondary
         *  controls” primary processor-based VM-execution control
         *  and the “enable VM functions” secondary processor-based
         *  VM-execution control.
         */
        vmx_write_vm_function_controls(0L);
        /**
         *  [23.6.15 VMCS Shadowing Bitmap Addresses]
         *  [...]
         *  If the “VMCS shadowing” VM-execution control is 1,
         *  executions of VMREAD and VMWRITE may consult these
         *  bitmaps (see Section 23.10 and Section 29.3).
         */
        /***** NOT USED *****/
        /**
         *  [23.6.16 ENCLS-Exiting Bitmap]
         *  The ENCLS-exiting bitmap is a 64-bit field. If the “enable
         *  ENCLS exiting” VM-execution control is 1, execution of
         *  ENCLS causes a VM exit if the bit in this field
         *  corresponding to the value of EAX is 1. If the bit is 0,
         *  the instruction executes normally. See Section 24.1.3 for
         *  more information.
         */
        /***** NOT USED *****/
        /**
         *  [23.6.17 ENCLV-Exiting Bitmap]
         *  The ENCLV-exiting bitmap is a 64-bit field. If the “enable
         *  ENCLV exiting” VM-execution control is 1, execution of
         *  ENCLV causes a VM exit if the bit in this field
         *  corresponding to the value of EAX is 1. If the bit is 0,
         *  the instruction executes normally. See Section 24.1.3 for
         *  more information.
         */
        /***** NOT USED *****/
        /**
         *  [23.6.18 Control Field for Page-Modification Logging]
         *  [...]
         *  If the “enable PML” VM-execution control is 1, VM entry
         *  ensures that the PML address is 4-KByte aligned. The PML
         *  address exists only on processors that support the
         *  1-setting of the “enable PML” VM-execution control.
         */
        /***** NOT USED *****/
        /**
         *  [23.6.19 Controls for Virtualization Exceptions]
         * Related to EPT, not used.
         */
        /***** NOT USED *****/
        /**
         *  [23.6.20 XSS-Exiting Bitmap]
         *  On processors that support the 1-setting of the “enable
         *  XSAVES/XRSTORS” VM-execution control, the VM-execution control
         *  fields include a 64-bit XSS-exiting bitmap. If the “enable
         *  XSAVES/XRSTORS” VM-execution control is 1, executions of
         *  XSAVES and XRSTORS may consult this bitmap (see Section
         *  24.1.3 and Section 24.3).
         */
        /***** NOT USED *****/
        /**
         *  [23.6.21 Sub-Page-Permission-Table Pointer (SPPTP)]
         * Rlated to EPT, not used.
         */
        /***** NOT USED *****/
    }

    {
        long tmp;
        /**
         * About VM-exits
         *
         * See Intel Manual Vol. 3
         *  [23.7 VM-EXIT CONTROL FIELDS]
         *  The VM-exit control fields govern the behavior of VM exits.
         *  They are discussed in Section 23.7.1 and Section 23.7.2.
         *  [...]
         *  All other bits in this field are reserved, some to 0 and
         *  some to 1. Software should consult the VMX capability MSRs
         *  IA32_VMX_EXIT_CTLS and IA32_VMX_TRUE_EXIT_CTLS (see Appendix
         *  A.4) to determine how it should set the reserved bits.
         *  Failure to set reserved bits properly causes subsequent VM
         *  entries to fail (see Section 25.2.1.2).
         *
         * See Intel Manual Vol. 3
         *  [A.4 VM-EXIT CONTROLS]
         *  The IA32_VMX_EXIT_CTLS MSR (index 483H) reports on the
         *  allowed settings of most of the VM-exit controls (see
         *  Section 23.7.1):
         *      -Bits 31:0 indicate the allowed 0-settings of these
         *       controls. VM entry allows control X (bit X of the
         *       VM-exit controls) to be 0 if bit X in the MSR is
         *       cleared to 0; if bit X in the MSR is set to 1, VM
         *       entry fails if control X is 0
         *
         * Setting the field with exactly the content of MSR
         * IA32_VMX_EXIT_CTLS should work.
         */
        {
            const long Load_IA32_EFER = 1L << 21;
            tmp = msr_read_ia32_vmx_exit_ctls();
            tmp |= Load_IA32_EFER;
            vmx_write_vm_exit_controls(tmp);
        }

        /**
         *  [23.7.2 VM-Exit Controls for MSRs]
         *  A VMM may specify lists of MSRs to be stored and loaded on
         *  VM exits. The following VM-exit control fields determine
         *  how MSRs are stored on VM exits:
         *      -VM-exit MSR-store count (32 bits). [...]
         *      -VM-exit MSR-store address (64 bits). [...]
         *       If the VM-exit MSR-store count is not zero, the address
         *      must be 16-byte aligned.
         *  [...]
         *  The following VM-exit control fields determine how MSRs are loaded
         *  on VM exits:
         *      -VM-exit MSR-load count (32 bits). [...]
         *      -VM-exit MSR-load address (64 bits). [...]
         *       If the VM-exit MSR-load count is not zero, the address
         *       must be 16-byte aligned.
         *  See Section 26.6 for how this area is used on VM exits.
         *
         * Not used, set counts to 0.
         */
        vmx_write_vm_exit_msr_store_count(0L);
        vmx_write_vm_exit_msr_load_count(0L);
    }

    {
        /**
         * About VMX-entries
         *
         * See Intel Manual Vol. 3
         *  [23.8 VM-ENTRY CONTROL FIELDS]
         *  The VM-entry control fields govern the behavior of VM
         *  entries. They are discussed in Sections 23.8.1 through
         *  23.8.3.
         */
        /**
         * See Intel Manual Vol. 3
         *  [23.8.1 VM-Entry Controls]
         *  The VM-entry controls constitute a 32-bit vector that
         *  governs the basic operation of VM entries. Table 23-14
         *  lists the controls supported. See Chapter 23 for how these
         *  controls affect VM entries.
         *  [...]
         *  All other bits in this field are reserved, some to 0 and
         *  some to 1. Software should consult the VMX capability MSRs
         *  IA32_VMX_ENTRY_CTLS and IA32_VMX_TRUE_ENTRY_CTLS (see
         *  Appendix A.5) to determine how it should set the reserved
         *  bits. Failure to set reserved bits properly causes
         *  subsequent VM entries to fail (see Section 25.2.1.3).
         *
         * See Intel Manual Vol. 3
         *  [A.5 VM-ENTRY CONTROLS]
         *  The IA32_VMX_ENTRY_CTLS MSR (index 484H) reports on the
         *  allowed settings of most of the VM-entry controls (see
         *  Section 23.8.1):
         *      -Bits 31:0 indicate the allowed 0-settings of these
         *       controls. VM entry allows control X (bit X of the
         *       VM-entry controls) to be 0 if bit X in the MSR is
         *       cleared to 0; if bit X in the MSR is set to 1, VM
         *       entry fails if control X is 0.
         *
         * Setting the field with exactly the content of MSR
         * IA32_VMX_ENTRY_CTLS should work.
         */
        vmx_write_vm_entry_controls(msr_read_ia32_vmx_entry_ctls());

        /**
         *  [23.8.2 VM-Entry Controls for MSRs]
         *  A VMM may specify a list of MSRs to be loaded on VM entries.
         *  The following VM-entry control fields manage this
         *  functionality:
         *      -VM-entry MSR-load count (32 bits). [...]
         *      -VM-entry MSR-load address (64 bits). [...]
         *       If the VM-entry MSR-load count is not zero, the
         *       address must be 16-byte aligned.
         *
         *  See Section 25.4 for details of how this area is used on
         *  VM entries.
         *
         * Not used, set count to 0.
         */
        vmx_write_vm_entry_msr_load_count(0L);
    }


    /* 64 bits */
    //vmx_write_address_of_io_bitmap_a;
    //vmx_write_address_of_io_bitmap_b;
    //vmx_write_vm_exit_msr_store_address;

    //vmx_write_vm_exit_msr_load_address;
    //vmx_write_vm_entry_msr_load_address;
    //vmx_write_executive_vmcs_pointer;
    //vmx_write_tsc_offset;

    /* 32 bits */


    /* natural width */
}
