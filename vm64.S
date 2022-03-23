/**
 * Ths file contains code to handle VM initialisation
 * code in 64 bit execution context
 *
 * Se Intel Manual Vol. 3 Chapters 22-29 and
 * Appendix A.1 for details
 *  (A.1 BASIC VMX INFORMATION)
 *
 * For VMX instruction summary see Intel Manual Vol. 2
 *  [B.18 VMX INSTRUCTIONS]
 */


#include "vm64_errors.h"

/**
 * To be set to enable VMX
 *
 * See Intel Manual Vol. 3
 *  [22.7 ENABLING AND ENTERING VMX OPERATION]
 */
#define CR4_VMXE (1 << 13)

/**
 * MSR (Model Specific Register) controlling VMX
 */
#define IA32_FEATURE_CONTROL 0x3a
#define IA32_FEATURE_CONTROL_LOCK (1 << 0)
#define IA32_FEATURE_CONTROL_VMXON_IN_SMX (1 << 1)
#define IA32_FEATURE_CONTROL_VMXON_OUTSIDE_SMX (1 << 2)

/**
 * See Intel manual Vol. 3
 *  [29.2 CONVENTIONS]
 *
 *  CF:  0
 *  PF:  2
 *  AF:  4
 *  ZF:  6
 *  SF:  7
 *  OF: 11
 */
#define VMmask (1<<0 | 1<<2 | 1<<4 | 1<<6 | 1<<7 | 1<<11)

/**
 * MSR for VMX data
 */
#define IA32_VMX_BASIC 0x480

.data
/*VMCS_POINTER:
    .long VMCS
VMXON_POINTER:
    .long VMXON_region*/

VM64_MSG:
    .asciz "Hello VM!"

.global vm64
.text
.code64

#define GPR_TOTAL_SIZE (8*15)
/**
 * Macro definitions, see:
 *  https://sourceware.org/binutils/docs/as.html#Macro
 */
.macro PUSHALL_GPR
    push %r15
    push %r14
    push %r13
    push %r12
    push %r11
    push %r10
    push %r9
    push %r8
    push %rbp
    push %rsi
    push %rdi
    push %rdx
    push %rcx
    push %rbx
    push %rax
.endm
.macro CLEARALL_GPR
    xor %rax,%rax
    xor %rbx,%rbx
    xor %rcx,%rcx
    xor %rdx,%rdx
    xor %rdi,%rdi
    xor %rsi,%rsi
    xor %rbp,%rbp
    xor %r8, %r8
    xor %r9, %r9
    xor %r10,%r10
    xor %r11,%r11
    xor %r12,%r12
    xor %r13,%r13
    xor %r14,%r14
    xor %r15,%r15
.endm
.macro POPALL_GPR
    pop %rax
    pop %rbx
    pop %rcx
    pop %rdx
    pop %rdi
    pop %rsi
    pop %rbp
    pop %r8
    pop %r9
    pop %r10
    pop %r11
    pop %r12
    pop %r13
    pop %r14
    pop %r15
.endm


vm64:
    call check_vm_support
    call enable_vmx

    call init_vm64_data_structures

    /* Enter VM */
    /* Exit VM */

    ret

.global set_cr4_vmxe
set_cr4_vmxe:
    /**
     *  [22.7 ENABLING AND ENTERING VMX OPERATION]
     *  Before system software can enter VMX operation,
     *  it enables VMX by setting CR4.VMXE[bit 13] = 1.
     *  VMX operation is then entered by executing the
     *  VMXON instruction.
     *  VMXON causes an invalid-opcode exception (#UD)
     *  if executed with CR4.VMXE = 0.
     *  Once in VMX operation, it is not possible to clear
     *  CR4.VMXE (see Section 22.8). System software leaves
     *  VMX operation by executing the VMXOFF instruction.
     *  CR4.VMXE can be cleared outside of VMX operation
     *  after executing of VMXOFF.
     *
     * Set CR4_VMXE
     */
    mov %cr4, %rax
    or $CR4_VMXE, %rax
    mov %rax, %cr4
    xor %rax, %rax
    ret

/**
 * See Intel Manual Vol. 3
 *  [22.7 ENABLING AND ENTERING VMX OPERATION]
 *  VMX operation is then entered by executing the
 *  VMXON instruction.
 */
.global enable_vmx
enable_vmx:
    /**
     * From Intel Manual Vol. 3:
     * [22.7 ENABLING AND ENTERING VMX OPERATION]
     *
     *  Before executing VMXON, software should allocate
     *  a naturally aligned 4-KByte region of memory that 
     *  a logical processor may use to support VMX operation.
     *  1 This region is called the VMXON region. The address
     *  of the VMXON region (the VMXON pointer) is provided
     *  in an operand to VMXON. Section 23.11.5,
     *  “VMXON Region,” details how software should initialize
     *  and access the VMXON region.
     *
     * [23.11.5 VMXON Region]
     *  Before executing VMXON, software should write the VMCS
     *  revision identifier (see Section 23.2) to the VMXON
     *  region. (Specifically, it should write the 31-bit VMCS
     *  revision identifier to bits 30:0 of the first 4 bytes
     *  of the VMXON region; bit 31 should be cleared to 0.) It
     *  need not initialize the VMXON region in any other way.
     *  Software should use a separate region for each logical
     *  processor and should not access or modify the VMXON
     *  region of a logical processor between execution of VMXON
     *  and VMXOFF on that logical processor. Doing otherwise
     *  may lead to unpredictable behavior (including behaviors
     *  identified in Section 23.11.1).
     *
     * [23.2 FORMAT OF THE VMCS REGION]
     *  Software should write the VMCS revision identifier to
     *  the VMCS region before using that region for a VMCS. The
     *  VMCS revision identifier is never written by the processor;
     *  VMPTRLD fails if its operand references a VMCS region whose
     *  VMCS revision identifier differs from that used by the
     *  processor. (VMPTRLD also fails if the shadow-VMCS indicator
     *  is 1 and the processor does not support the 1-setting of
     *  the “VMCS shadowing” VM-execution control; see Section
     *  23.6.2)
     * [IMPORTANT!!!!]
     *  Software can discover the VMCS revision identifier
     *  that a processor uses by reading the VMX capa-bility MSR
     *  IA32_VMX_BASIC (see Appendix A.1).
     */
    mov $IA32_FEATURE_CONTROL, %rcx
    rdmsr
    /* set enabling bits and lock bit */
    or $(IA32_FEATURE_CONTROL_VMXON_OUTSIDE_SMX | IA32_FEATURE_CONTROL_VMXON_IN_SMX | IA32_FEATURE_CONTROL_LOCK), %rax
    wrmsr
    xor %rax, %rax
    ret

/**
 * Read the VMCS revision identifier for the current
 * processor and put it in %rax
 *
 * See Intel Manual Vol. 3
 *  [23.2 FORMAT OF THE VMCS REGION]
 *  Software can discover the VMCS revision identifier
 *  that a processor uses by reading the VMX capa-bility
 *  MSR IA32_VMX_BASIC (see Appendix A.1).
 */
.global read_vmcs_revision_identifier
read_vmcs_revision_identifier:
    call read_IA32_VMX_BASIC
    /* now %rax contains all IA32_VMX_BASIC */
    /* maintains only lower 4 bytes */
    mov %eax, %eax
    /* now %rax contains VMX revision identifier */
    ret

.global get_vmx_region
get_vmx_region:
    /* Put processor VMCS revision identifier in %rax */
    call read_vmcs_revision_identifier
    /* Write VMCS revision identifier in VMXON region */
    lea VMXON_region, %rbx
    mov %eax, (%rbx)
    mov %rbx, %rax
    ret

.global get_vmcs_region
get_vmcs_region:
    /* Put processor VMCS revision identifier in %rax */
    call read_vmcs_revision_identifier
    /* Write VMCS revision identifier in VMXON region */
    lea VMCS_region, %rbx
    mov %eax, (%rbx)
    mov %rbx, %rax
    ret

/**
 * See Intel Manual Vol. 3
 *  [23.1 OVERVIEW]
 *
 * Receive a pointer to the a page
 * to be used as VMCS regiont and
 * activate it
 */
.global vmx_enable_vmcs_region
vmx_enable_vmcs_region:
    push %rdi
    /**
     * See Intel Manual Vol. 3
     *  [VMPTRLD—Load Pointer to Virtual-Machine Control Structure]
     */
    vmptrld (%rsp)
    pop %rax
    pushfq
    pop %rax
    and $VMmask, %rax
    ret


.global vmx_clear_vmcs
vmx_clear_vmcs:
    push %rdi
    /**
     * See Intel Manual Vol. 3
     *  [VMCLEAR—Clear Virtual-Machine Control Structure]
     */
    vmclear (%rsp)
    pop %rax
    pushfq
    pop %rax
    and $VMmask, %rax
    ret
    ret

/**
 * See Intel Manual Vol. 3
 *  [22.7 ENABLING AND ENTERING VMX OPERATION]
 *  VMX operation is then entered by executing the
 *  VMXON instruction.
 *
 * Receive as argument the pointer to the page
 * designed as vmx_region
 */
.global enter_vmx
enter_vmx:
    /**
     * See Intel Manual Vol. 3
     *  [22.7 ENABLING AND ENTERING VMX OPERATION]
     *  Before executing VMXON, software should allocate
     *  a naturally aligned 4-KByte region of memory that
     *  a logical processor may use to support VMX operation.
     *  1 This region is called the VMXON region. The address
     *  of the VMXON region (the VMXON pointer) is provided
     *  in an operand to VMXON.
     *  Section 23.11.5, “VMXON Region,” details how
     *  software should initialize and access the VMXON region.
     */
    /**
     * See Intel Manual Vol. 3
     *  [23.11.5 VMXON Region]
     *  Before executing VMXON, software should write the VMCS
     *  revision identifier (see Section 23.2) to the VMXON
     *  region.
     *  (Specifically, it should write the 31-bit VMCS revision
     *  identifier to bits 30:0 of the first 4 bytes of the VMXON
     *  region; bit 31 should be cleared to 0.)
     *  It need not initialize the VMXON region in any other way.
     *  Software should use a separate region for each logical
     *  processor and should not access or modify the VMXON region
     *  of a logical processor between execution of VMXON and
     *  VMXOFF on that logical processor. Doing otherwise may lead
     *  to unpre-dictable behavior (including behaviors identified
     *  in Section 23.11.1).
     */
    /**
     * Enter VMX mode.
     * See Intel Manual Vol. 3
     *  [29.3 VMXON—Enter VMX Operation]
     */
    push %rdi
    vmxon (%rsp)
    pop %rax
    pushfq
    pop %rax
    and $VMmask, %rax
    ret

.global vmxoff
vmxoff:
    /**
     * Enter VMX mode.
     * See Intel Manual Vol. 3
     *  [29.3 VMXOFF—Leave VMX Operation]
     */
    vmxoff
    pushf
    pop %rax
    and $VMmask, %rax
    ret

.global get_current_vmcs
get_current_vmcs:
    push %rax
    vmptrst (%rsp)
    pop %rax
    ret

.global vmx_launch_current_vmcs
vmx_launch_current_vmcs:
    /**
     * See Intel Manual Vol. 3
     *  [23.5 HOST-STATE AREA]
     * GP registers (and floating-point registers and so on)
     * are not saved before entries so they must be stored
     * and restored by software
     */
    PUSHALL_GPR

    /**
     * See Intel Manual Vol. 3
     *  [26.5.3 Loading Host RIP, RSP, RFLAGS, and SSP]
     *  RIP and RSP are loaded from the RIP field and the RSP field, respectively.
     *
     * RIP and RSP must be MANUALLY SAVED before launching a VM!
     */
    lea 1f(%rip), %rdi
    call vmx_host_write_rip
    mov %rsp, %rdi
    call vmx_host_write_rsp

    /* Clear all registers */
    CLEARALL_GPR
    /**
     * See Intel Manual Vol. 3
     *  [VMLAUNCH/VMRESUME—Launch/Resume Virtual Machine]
     */
    vmlaunch
1:
    pushf   /* Store RFLAGS to detect VM statuts */

        /* reserve 16 bytes for VM RIP and RSP */
        sub $16, %rsp
        /* PUSH VMX registers */
        PUSHALL_GPR                 /* %rsp decremented by GPR_TOTAL_SIZE */
        /* Get VM RIP and RSP */
        call vmx_guest_read_rsp
        mov %rax, GPR_TOTAL_SIZE(%rsp)      /* %rsp decremented by 8 */
        call vmx_guest_read_rip
        mov %rax, GPR_TOTAL_SIZE+8(%rsp)    /* %rsp decremented by 8 */
        /* Call function to print register status */
        mov %rsp, %rdi
        call vmx_debug_virtual_machine
        /* Clear stack */
        add $(GPR_TOTAL_SIZE+2*8), %rsp

    popf    /* Restore RFLAGS to detect VM statuts */

    /* restore registers after vm exit */
    POPALL_GPR

    /**
     * Check for absence of current VMCS
     * See Intel Manual Vol. 3
     *  [25.1 BASIC VM-ENTRY CHECKS]
     *  3. If there is no current VMCS, RFLAGS.CF is set to 1
     *      and control passes to the next instruction.
     *  4. If there is a current VMCS but the current VMCS is
     *      a shadow VMCS (see Section 23.10), RFLAGS.CF is
     *      set to 1 and control passes to the next instruction.
     *
     *  [...]
     *  If any of these checks fail, RFLAGS.ZF is set to 1 and
     *  control passes to the next instruction. An error number
     *  indicating the cause of the failure is stored in the VM
     *  instruction error field. See Chapter 29 for the error
     *  numbers.
     */
    /**
     * About local symbols:
     *  https://sourceware.org/binutils/docs/as/Symbol-Names.html
     */
    pushfq
    pop %rax
    and $VMmask, %rax
    ret


/**
 * Read MSR IA32_VMX_BASIC and return
 * value in EAX
 *
 * 
 */
.global read_IA32_VMX_BASIC
read_IA32_VMX_BASIC:
    push %rcx
    push %rdx
    
    xor %rax, %rax /* maybe unnecessary */
    xor %rdx, %rdx

    /**
     * From Intel Manual Vol. 3
     *
     * [A.1 BASIC VMX INFORMATION]
     *  Bits 30:0 contain the 31-bit VMCS revision
     *  identifier used by the processor. Processors
     *  that use the same VMCS revision identifier use
     *  the same size for VMCS regions (see subsequent
     *  item on bits 44:32).
     */
    mov $IA32_VMX_BASIC, %rcx
    rdmsr
    sal $32, %rdx /* Move result to the top 32 bits */
    or %rdx, %rax /* Move all result in RAX */

    pop %rdx
    pop %rcx
    ret

.global vmx_read_vmcs_field
vmx_read_vmcs_field:
    /**
     *  [VMREAD—Read Field from Virtual-Machine Control Structure]
     */
    vmread %rsi, (%rdi)
    pushf
    pop %rax
    and $VMmask, %rax
    ret


.global vmx_write_vmcs_field
vmx_write_vmcs_field:
    /**
     *  [VMREAD—Read Field from Virtual-Machine Control Structure]
     */
    vmwrite %rsi, %rdi
    pushf
    pop %rax
    and $VMmask, %rax
    ret

.global init_vm64_data_structures
init_vm64_data_structures:
    /**
     *  [23.11.3 Initializing a VMCS]
     *  Software should initialize fields in a VMCS (using
     *  VMWRITE) before using the VMCS for VM entry.
     *
     *  1.  VMCLEAR should be executed for a VMCS before
     *      it is used for VM entry for the first time.
     *  2.  VMLAUNCH should be used for the first VM entry
     *      using a VMCS after VMCLEAR has been executed for
     *      that VMCS.
     *  3.  VMRESUME should be used for any subsequent VM
     *      entry using a VMCS (until the next execution of
     *      VMCLEAR for the VMCS).
     */
    call read_vmcs_revision_identifier
    /**
     * Now bit 30:0 contains VMCS revision identifier
     * used by the processor (bit 31 is always 0 and
     * this is always ok), this must be copied in
     * the first four bytes of the VMCS
     */
    lea VMCS_region, %rbx
    mov %eax, (%rbx)
    /**
     * Load VMCS pointer.
     * See Intel Manual Vol. 3
     *  [22.5 VIRTUAL-MACHINE CONTROL STRUCTURE]
     *  [29.3 VMPTRLD—Load Pointer to Virtual-Machine Control Structure]
     */
    vmptrld (%rbx)
    ret

/**
 * Processor support for VM should be checked
 * See Vol. 3:
 *  [22.6 DISCOVERING SUPPORT FOR VMX]
 *  Before system software enters into VMX operation, it must
 *  discover the presence of VMX support in the processor.
 *  System software can determine whether a processor supports
 *  VMX operation using CPUID. If CPUID.1:ECX.VMX[bit 5] = 1,
 *  then VMX operation is supported. See Chapter 3,
 *  “Instruction Set Reference, A-L” of Intel® 64 and IA-32
 *  Architectures Software Developer’s Manual, Volume 2A.
 */
.global check_vm_support
check_vm_support:
    push %rbx
    push %rcx
    push %rdx
    /* CPUID.1:ECX.VMX[bit 5] = 1 */
    mov $1, %eax
     xor %rcx, %rcx
    cpuid

    /* Check ECX.VMX[bit 5] */
    xor %rax, %rax
    test $(1 << 5), %ecx
    mov $1, %edx /* TEMP */
    cmovnz %edx, %eax
    
    pop %rdx
    pop %rcx
    pop %rbx
    ret

.global vmx_get_guest_stack
vmx_get_guest_stack:
    lea VM_GUEST_STACK, %rax
    ret
.global vmx_get_guest_code
vmx_get_guest_code:
    lea vm_guest, %rax
    ret

vm_guest:
    mov $0xf5f5, %eax
    mov $0xf5f5, test
    hlt

.bss
/**
 * VMCS (Virtual Machine Control Structure)
 * must be 4KB aligned.
 * See Intel Volume 3
 *  [23.1 OVERVIEW]
 */
.align 4096
VMCS_region:
    .skip 4096

/**
 * See Intel Manual Vol. 3
 *  [23.11.5 VMXON Region]
 *  Before executing VMXON, software allocates a region of
 *  memory (called the VMXON region) 1 that the logical
 *  processor uses to support VMX operation. The physical
 *  address of this region (the VMXON pointer) is provided
 *  in an operand to VMXON.
 */
.align 4096
VMXON_region:
    .skip 4096

VM_GUEST_STACK:
    .skip 4096
