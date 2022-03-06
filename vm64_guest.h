
#ifndef VM64_GUEST
#define VM64_GUEST

short vmx_guest_read_cs();
short vmx_guest_read_ds();
short vmx_guest_read_ss();
short vmx_guest_read_es();
short vmx_guest_read_fs();
short vmx_guest_read_gs();

void vmx_guest_write_cs(short val);
void vmx_guest_write_ds(short val);
void vmx_guest_write_ss(short val);
void vmx_guest_write_es(short val);
void vmx_guest_write_fs(short val);
void vmx_guestw_itrd_gs(short val);

#endif
