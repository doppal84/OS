#ifndef H_CONSOLE
#define H_CONSOLE

#include <stdint.h>
#include <string.h>
static char* const VGA_BUFFER = (char*) 0xb8000;

typedef enum {
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GRAY,
    DARK_GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    WHITE
} Color;

void clear_terminal();
void init_terminal();
void print_character(char c);
void print_integer(int num);
void print_character_with_color(char c, Color background, Color foreground);
void print_string(const char *str);
void print_string_with_color(const char *str, Color background, Color foreground);
void print_line(const char *str);
void print_line_with_color(const char *str, Color background, Color foreground);
void read_command(char *command_buf, char *args_buf);
int handle_command(char *command_buf, char *args_buf);
void update_cursor();
uint16_t get_cursor_position();

#endif
