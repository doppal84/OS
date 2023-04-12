#ifndef H_CONSOLE
#define H_CONSOLE
void clear_screen();
void print_character(char c);
void print_string(char* str);
void print_line(char* str);
#endif

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BYTES_PER_CHARACTER 2
#define VGA_BYTES_PER_ROW (VGA_WIDTH*VGA_BYTES_PER_CHARACTER)
#define VGA_TOTAL_BYTES (VGA_HEIGHT*VGA_WIDTH*VGA_BYTES_PER_CHARACTER)

