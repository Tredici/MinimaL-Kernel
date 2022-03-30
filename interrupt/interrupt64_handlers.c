
#include "interrupt64_handlers.h"
#include "video64bit.h"
#include "error64.h"
#include "string64.h"
#include "tr.h"

void handle_div0_c()
{
    set_background_color(7);
    set_foreground_color(8);
    print_current_task_status();
    panic64("Exception DIV0!");
}

void handle_int3_c()
{
    set_background_color(7);
    set_foreground_color(8);
    print_current_task_status();
    panic64("Exception Breakpoint!");
}

void handle_ud_c(void *rip)
{
    set_background_color(7);
    set_foreground_color(8);
    print_current_task_status();
    char buffer[80] = "#UD(";
    char *tmp;
    tmp = strcat64(buffer, hex64((long)rip));
    tmp = strcat64(tmp, ") ");
    tmp = strcat64(tmp, hex64(*(long*)rip));
    panic64(buffer);
}

void handle_double_f_c()
{
    set_background_color(7);
    set_foreground_color(8);
    print_current_task_status();
    panic64("Double fault!");
}

void handle_stack_f_c()
{
    set_background_color(7);
    set_foreground_color(8);
    print_current_task_status();
    panic64("Stack fault!");
}

void handle_gpe_c(long error)
{
    set_background_color(7);
    set_foreground_color(8);
    print_current_task_status();
    char buffer[80] = "General Protection Exception(";
    char *tmp;
    tmp = strcat64(buffer, ltoa64(error));
    tmp = strcat64(tmp, ")");
    panic64(buffer);
}

void handle_tss_c()
{
    set_background_color(7);
    set_foreground_color(8);
    print_current_task_status();
    panic64("Exception TSS!");
}

void handle_snp_c()
{
    set_background_color(7);
    set_foreground_color(8);
    print_current_task_status();
    panic64("Exception SNP!");
}

void handle_pfe_c()
{
    set_background_color(7);
    set_foreground_color(8);
    print_current_task_status();
    panic64("Page fault!");
}
