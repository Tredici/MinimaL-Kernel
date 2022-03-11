
#ifndef VM64_CONTROL
#define VM64_CONTROL

int vmx_guest_read_vm_instruction_error();
int vmx_guest_read_vm_exit_reason();
int vmx_guest_read_vm_exit_interruption_information();
int vmx_guest_read_vm_exit_interruption_error_code();
int vmx_guest_read_idt_vectoring_information_field();
int vmx_guest_read_guest_idt_vectoring_error_code();
int vmx_guest_read_guest_vm_exit_instruction_length();
int vmx_guest_read_guest_vm_exit_instruction_information();

#endif

