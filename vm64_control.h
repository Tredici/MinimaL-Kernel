
#ifndef VM64_CONTROL
#define VM64_CONTROL

/* Read Only fields! */
int vmx_guest_read_vm_instruction_error();
int vmx_guest_read_vm_exit_reason();
int vmx_guest_read_vm_exit_interruption_information();
int vmx_guest_read_vm_exit_interruption_error_code();
int vmx_guest_read_idt_vectoring_information_field();
int vmx_guest_read_guest_idt_vectoring_error_code();
int vmx_guest_read_guest_vm_exit_instruction_length();
int vmx_guest_read_guest_vm_exit_instruction_information();

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

#endif
