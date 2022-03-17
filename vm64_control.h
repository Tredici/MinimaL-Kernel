
#ifndef VM64_CONTROL
#define VM64_CONTROL

/* Read Write 16 bits control fields */
short vmx_read_virtual_processor_identifier();
short vmx_read_posted_interrupt_notification_vector();
short vmx_read_eptp_index();

void vmx_write_virtual_processor_identifier(short val);
void vmx_write_posted_interrupt_notification_vector(short val);
void vmx_write_eptp_index(short val);


/* Read Only 32 bits fields! */
int vmx_read_vm_instruction_error();
int vmx_read_vm_exit_reason();
int vmx_read_vm_exit_interruption_information();
int vmx_read_vm_exit_interruption_error_code();
int vmx_read_idt_vectoring_information_field();
int vmx_read_idt_vectoring_error_code();
int vmx_read_vm_exit_instruction_length();
int vmx_read_vm_exit_instruction_information();


/* Read Write 32 bits control fields */
long vmx_read_pin_based_vm_execution_controls();
long vmx_read_primary_processor_based_vm_execution_controls();
long vmx_read_exception_bitmap();
long vmx_read_page_fault_error_code_mask();
long vmx_read_page_fault_error_code_match();
long vmx_read_cr3_target_count();
long vmx_read_vm_exit_controls();
long vmx_read_vm_exit_msr_store_count();
long vmx_read_vm_exit_msr_load_count();
long vmx_read_vm_entry_controls();
long vmx_read_vm_entry_msr_load_count();
long vmx_read_vm_entry_interruption_information_field();
long vmx_read_vm_entry_exception_error_code();
long vmx_read_vm_entry_instruction_length();
long vmx_read_tpr_threshold();
long vmx_read_secondary_processor_based_vm_execution_controls();
long vmx_read_ple_gap();
long vmx_read_ple_window();

void vmx_write_pin_based_vm_execution_controls(long val);
void vmx_write_primary_processor_based_vm_execution_controls(long val);
void vmx_write_exception_bitmap(long val);
void vmx_write_page_fault_error_code_mask(long val);
void vmx_write_page_fault_error_code_match(long val);
void vmx_write_cr3_target_count(long val);
void vmx_write_vm_exit_controls(long val);
void vmx_write_vm_exit_msr_store_count(long val);
void vmx_write_vm_exit_msr_load_count(long val);
void vmx_write_vm_entry_controls(long val);
void vmx_write_vm_entry_msr_load_count(long val);
void vmx_write_vm_entry_interruption_information_field(long val);
void vmx_write_vm_entry_exception_error_code(long val);
void vmx_write_vm_entry_instruction_length(long val);
void vmx_write_tpr_threshold(long val);
void vmx_write_secondary_processor_based_vm_execution_controls(long val);
void vmx_write_ple_gap(long val);
void vmx_write_ple_window(long val);


/* Read Write Natural-Width Control Fields */
long vmx_read_cr0_guest_host_mask();
long vmx_read_cr4_guest_host_mask();
long vmx_read_cr0_read_shadow();
long vmx_read_cr4_read_shadow();
long vmx_read_cr3_target_value_0();
long vmx_read_cr3_target_value_1();
long vmx_read_cr3_target_value_2();
long vmx_read_cr3_target_value_3();

void vmx_write_cr0_guest_host_mask(long val);
void vmx_write_cr4_guest_host_mask(long val);
void vmx_write_cr0_read_shadow(long val);
void vmx_write_cr4_read_shadow(long val);
void vmx_write_cr3_target_value_0(long val);
void vmx_write_cr3_target_value_1(long val);
void vmx_write_cr3_target_value_2(long val);
void vmx_write_cr3_target_value_3(long val);

/* Read Only Natural width fields */
long vmx_read_exit_qualification();
long vmx_read_io_rcx();
long vmx_read_io_rsi();
long vmx_read_io_rdi();
long vmx_read_io_rip();
long vmx_read_guest_linear_address();

/* Read Write 64 bits control fields */
/* 1st block */
long vmx_read_address_of_io_bitmap_a();
long vmx_read_address_of_io_bitmap_b();
long vmx_read_address_of_msr_bitmaps();
long vmx_read_vm_exit_msr_store_address();

void vmx_write_address_of_io_bitmap_a(long val);
void vmx_write_address_of_io_bitmap_b(long val);
void vmx_write_address_of_msr_bitmaps(long val);
void vmx_write_vm_exit_msr_store_address(long val);

/* 2nd block */
long vmx_read_vm_exit_msr_load_address();
long vmx_read_vm_entry_msr_load_address();
long vmx_read_executive_vmcs_pointer();
long vmx_read_pml_address();
long vmx_read_tsc_offset();
long vmx_read_virtual_apic_address();
long vmx_read_apic_access_address();
long vmx_read_posted_interrupt_descriptor_address();
long vmx_read_vm_function_controls();
long vmx_read_ept_pointer();
long vmx_read_eoi_exit_bitmap_0();
long vmx_read_eoi_exit_bitmap_1();
long vmx_read_eoi_exit_bitmap_2();
long vmx_read_eoi_exit_bitmap_3();
long vmx_read_eptp_list_address();
long vmx_read_vmread_bitmap_address();
long vmx_read_vmwrite_bitmap_address();
long vmx_read_virtualization_exception_information_address();
long vmx_read_xss_exiting_bitmap();

void vmx_write_vm_exit_msr_load_address(long val);
void vmx_write_vm_entry_msr_load_address(long val);
void vmx_write_executive_vmcs_pointer(long val);
void vmx_write_pml_address(long val);
void vmx_write_tsc_offset(long val);
void vmx_write_virtual_apic_address(long val);
void vmx_write_apic_access_address(long val);
void vmx_write_posted_interrupt_descriptor_address(long val);
void vmx_write_vm_function_controls(long val);
void vmx_write_ept_pointer(long val);
void vmx_write_eoi_exit_bitmap_0(long val);
void vmx_write_eoi_exit_bitmap_1(long val);
void vmx_write_eoi_exit_bitmap_2(long val);
void vmx_write_eoi_exit_bitmap_3(long val);
void vmx_write_eptp_list_address(long val);
void vmx_write_vmread_bitmap_address(long val);
void vmx_write_vmwrite_bitmap_address(long val);
void vmx_write_virtualization_exception_information_address(long val);
void vmx_write_xss_exiting_bitmap(long val);

/* 3rd block */
long vmx_read_encls_exiting_bitmap();
long vmx_read_sub_page_permission_table_pointer();
long vmx_read_tsc_multiplier();
long vmx_read_tertiary_processor_based_vm_execution_controls();
long vmx_read_enclv_exiting_bitmap();

void vmx_write_encls_exiting_bitmap(long val);
void vmx_write_sub_page_permission_table_pointer(long val);
void vmx_write_tsc_multiplier(long val);
void vmx_write_tertiary_processor_based_vm_execution_controls(long val);
void vmx_write_enclv_exiting_bitmap(long val);

#endif

