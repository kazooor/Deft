#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include "terminal/core.h"

void kernel_main()
{
    terminal_initialize(VGA_COLOR_GREEN, VGA_COLOR_BLACK);

    terminal_writestring("---- WELCOME TO THE SHIT KERNEL (C) 2019 github.com/kazoor ----!\n");
}