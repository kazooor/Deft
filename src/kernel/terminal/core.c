#include <stdint.h>
#include <stddef.h>
#include "core.h"

// TODO: Move this.
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void terminal_initialize(enum vga_color foreground, enum vga_color background) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(foreground, background);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	unsigned char uchar = c;
	
	switch(c)
	{
		case '\n': 
			terminal_row++;
			terminal_column = 0;
			break;
		default:
			terminal_putentryat(uchar, terminal_color, terminal_column, terminal_row);
        	terminal_column++;
	}

	if(terminal_column > VGA_WIDTH)
	{
		terminal_column = 0;
		terminal_row++;
	}

	if(terminal_row >= VGA_HEIGHT)
	{
		size_t i, j;
		for(i = 0; i < VGA_HEIGHT - 1; i++)
		{
			for(j = VGA_HEIGHT - 2; j > 0; j--)
			{
				terminal_buffer[(j * VGA_HEIGHT) + i] = terminal_buffer[((j+1) * VGA_WIDTH) + i];
			}
		}
		
		for(i = 0; i < VGA_WIDTH - 1; i++)
		{
		 	terminal_putentryat(' ', terminal_color, i, VGA_HEIGHT-1);
		}
		
		terminal_row = VGA_HEIGHT - 1;
	}
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}