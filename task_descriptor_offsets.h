/**
 * This file contains the offsets in bytes
 * of the fields of the tast_descriptr struct
 * defined in filed "tr.h"
 */

#ifndef TASK_DESCRIPTOR_OFFSETS
#define TASK_DESCRIPTOR_OFFSETS

/**
 * General Purpose Registers offsets
 */
#define TD_RAX  0X00
#define TD_RBX  0X08
#define TD_RCX  0X10
#define TD_RDX  0X18
#define TD_RDI  0X20
#define TD_RSI  0X28
#define TD_RBP  0X30
#define TD_R8   0X38
#define TD_R9   0X40
#define TD_R10  0X48
#define TD_R11  0X50
#define TD_R12  0X58
#define TD_R13  0X60
#define TD_R14  0X68
#define TD_R15  0X70

/**
 * Current (top stack) offset
 */
#define TD_RSP  0X78

/**
 * Control Registers offset
 */
#define TD_CR3  0X80

#endif
