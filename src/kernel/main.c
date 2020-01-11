#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include "terminal/core.h"

void kernel_main()
{
    terminal_initialize();
    terminal_writestring("Hello from kernel.\n");
}