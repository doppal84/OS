#include "console.h"
#include "portmap.h"
#include "keyboard.h"
#define VGA_WIDTH       80
#define VGA_HEIGHT      25
#define BYTES_PER_CHAR  2
#define VGA_MAX_INDEX   (VGA_WIDTH * VGA_HEIGHT * BYTES_PER_CHAR)
#define is_special_char(c) ((c) <= 31)

static void handle_special_char(char c);
static void set_terminal_font_color(char *color);
static void shift_terminal_up();

//char* const VGA_BUFFER = (char) 0xb8000;
unsigned int terminal_position = 0;

Color terminal_fg_color = LIGHT_GRAY;
Color terminal_bg_color = BLACK;

const char HELP_MENU[] = \
"help -> display this menu\n"\
"cls -> clear the screen\n"\
"echo [str] -> print a line to the screen\n"\
"set-terminal-font-color [color] -> change the font color\n"\
"exit -> exit the OS\n";

void init_terminal()
{
    terminal_fg_color = LIGHT_GRAY;
    terminal_bg_color = BLACK;
}

void update_cursor()
{
    uint16_t cursor_position = terminal_position >> 1;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) cursor_position);
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) (cursor_position >> 8));
}

static void read_until_newline() {
    unsigned char byte, c;
    while (1) {
        while ((byte = scan())) {
            c = charmap[byte];
            print_character(c);
            if (c == '\n') {
                return;
            }
        }
    }
}

void read_command(char *command_buf, char *args_buf)
{
    int index = 0, reading_command = 1, starting_position = terminal_position;
    *command_buf = *args_buf = '\0';
    read_until_newline();
    for (unsigned int i = starting_position; i < terminal_position; i+=2) 
    {
        char input = VGA_BUFFER[i];
        if (input == ' ' && reading_command)
        {
            command_buf[index] = '\0';
            command_buf = args_buf;
            index = 0;
            reading_command = 0;
        }
        else
        {
            command_buf[index++] = input;
        }
    }
    command_buf[index] = '\0'; 
}

int handle_command(char *command_buf, char *args_buf)
{
    if (!strcmp(command_buf, "help"))
    {
        print_string(HELP_MENU);
    } 
    else if (!strcmp(command_buf, "cls"))
    {
        clear_terminal();
    } 
    else if (!strcmp(command_buf, "echo"))
    {
        print_line(args_buf);
    }
    else if (!strcmp(command_buf, "exit"))
    {
        print_line("goodbye");
        return -1;
    }
    else if (!strcmp(command_buf, "set-terminal-font-color"))
    {
        set_terminal_font_color(args_buf);
    }
    else if (strlen(command_buf) == 0)
    {
        return 0;
    }
    else
    {
        print_string_with_color("Error: ", BLACK, RED);
        print_string_with_color(command_buf, terminal_bg_color, terminal_fg_color);
        print_line_with_color(" is not a valid command. Run 'help' for a list of commands.", BLACK, RED);
    }
    return 0;
}

static void set_terminal_font_color(char *color)
{
    if (*color == '-')
    {
        ++color;
    }
    if (!strcmp(color, "black"))
    {
        terminal_fg_color = BLACK;
    }
    else if (!strcmp(color, "blue"))
    {
        terminal_fg_color = BLUE;
    }
    else if (!strcmp(color, "green"))
    {
        terminal_fg_color = GREEN;
    }
    else  if (!strcmp(color, "cyan"))
    {
        terminal_fg_color = CYAN;
    }
    else if (!strcmp(color, "red"))
    {
        terminal_fg_color = RED;
    }
    else if (!strcmp(color, "magenta"))
    {
        terminal_fg_color = MAGENTA;
    }
    else if (!strcmp(color, "brown"))
    {
        terminal_fg_color = BROWN;
    }
    else if (!strcmp(color, "light gray"))
    {
        terminal_fg_color = LIGHT_GRAY;
    }
    else if (!strcmp(color, "dark gray"))
    {
        terminal_fg_color = DARK_GRAY;
    }
    else if (!strcmp(color, "light blue"))
    {
        terminal_fg_color = LIGHT_BLUE;
    }
     else if (!strcmp(color, "light green"))
    {
        terminal_fg_color = LIGHT_GREEN;
    }
    else if (!strcmp(color, "light cyan"))
    {
        terminal_fg_color = LIGHT_CYAN;
    }
    else if (!strcmp(color, "light red"))
    {
        terminal_fg_color = LIGHT_RED;
    }
    else if (!strcmp(color, "light magenta"))
    {
        terminal_fg_color = LIGHT_MAGENTA;
    }
    else if (!strcmp(color, "yellow"))
    {
        terminal_fg_color = YELLOW;
    }
    else if (!strcmp(color, "white"))
    {
        terminal_fg_color = WHITE;
    }
    else
    {
        print_string_with_color("Error: ", BLACK, RED);
        print_string_with_color(color, terminal_bg_color, terminal_fg_color);
        print_line_with_color(" is not a valid color.", BLACK, RED);
    }
}

uint16_t get_cursor_position() {
    uint16_t cursor_position = 0;
    outb(0x3D4, 0x0F);
    cursor_position |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    cursor_position |= ((uint16_t) inb(0x3D5)) << 8;
    return cursor_position;
}

void clear_terminal()
{
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * BYTES_PER_CHAR;)
    {
        VGA_BUFFER[i++] = 0;
        VGA_BUFFER[i++] = 7;
    }
    terminal_position = 0;
    update_cursor();
}

void print_character(char c)
{
    print_character_with_color(c, terminal_bg_color, terminal_fg_color);
}

void print_integer(int toPrint)
{
    char buf[1];
    itoa(buf, toPrint);
    print_string(buf);
}

void print_character_with_color(char c, Color background, Color foreground)
{
    if (is_special_char(c))
    {
        handle_special_char(c);
    }
    else
    {
        if (terminal_position + 2 > VGA_MAX_INDEX) {
            shift_terminal_up();
        }
        VGA_BUFFER[terminal_position++] = c;
        VGA_BUFFER[terminal_position++] = (background << 4) | foreground;
    }
    update_cursor();
}

void print_string(const char *str)
{
    print_string_with_color(str, terminal_bg_color, terminal_fg_color);
}

void print_string_with_color(const char *str, Color background, Color foreground)
{
    while (*str != '\0')
    {
        print_character_with_color(*str++, background, foreground);
    }
}


void print_line(const char *str)
{
    print_line_with_color(str, terminal_bg_color, terminal_fg_color);
}

void print_line_with_color(const char *str, Color background, Color foreground)
{
    print_string_with_color(str, background, foreground);
    print_character('\n');
}

static void handle_newline_character()
{
    terminal_position += (BYTES_PER_CHAR * VGA_WIDTH) - (terminal_position % (BYTES_PER_CHAR * VGA_WIDTH));
}

static void handle_backspace()
{
    VGA_BUFFER[--terminal_position] = (terminal_bg_color << 4) | terminal_fg_color;
    VGA_BUFFER[--terminal_position] = 0;
}

static void handle_special_char(char c)
{
    switch(c)
    {
        case '\n':
            handle_newline_character();
            break;
        case '\b':
            handle_backspace();
            break;
	default:
	    VGA_BUFFER[terminal_position++] = c;
            VGA_BUFFER[terminal_position++] = terminal_fg_color;


    }
}

static void shift_terminal_up()
{
    char *line = VGA_BUFFER;
    for (int i = 0; i < VGA_HEIGHT - 1; i++) {
        memcpy(line, line + VGA_WIDTH * BYTES_PER_CHAR, VGA_WIDTH * BYTES_PER_CHAR);
        line += VGA_WIDTH * BYTES_PER_CHAR;
    }
    memset(line, 0, VGA_WIDTH * BYTES_PER_CHAR);
    terminal_position -= VGA_WIDTH * BYTES_PER_CHAR;
}
