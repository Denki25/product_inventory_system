#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

#define DATA_FILE "data/products.dat"
#define HISTORY_FILE "data/history.txt"
#define ADMIN_PASSWORD "1234"

#define MAX_NAME_LENGTH 50
#define MAX_CATEGORY_LENGTH 30
#define MAX_USERNAME_LENGTH 30
#define MAX_PASSWORD_LENGTH 30
#define MAX_INPUT_LENGTH 256

typedef enum Color {
    COLOR_DEFAULT = 0,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_CYAN,
    COLOR_WHITE
} Color;

void clear_screen(void);
void sleep_ms(unsigned int milliseconds);
void enable_virtual_terminal(void);
void set_color(Color color);
void reset_color(void);
void print_banner(const char *title);
void print_section(const char *title);
void print_message(const char *label, const char *message, Color color);
void print_divider(void);
void loading_animation(const char *message, unsigned int milliseconds);
void wait_for_enter(void);

void ensure_data_directory(void);
void ensure_data_files(void);

int read_line(const char *prompt, char *buffer, size_t size);
int read_non_empty_string(const char *prompt, char *buffer, size_t size);
int read_int_in_range(const char *prompt, int min, int max, int *value);
int read_float_in_range(const char *prompt, float min, float max, float *value);
int prompt_yes_no(const char *prompt);
void read_password(const char *prompt, char *buffer, size_t size);

void trim_newline(char *text);
void to_lowercase(const char *source, char *destination, size_t size);
int contains_case_insensitive(const char *text, const char *pattern);
int strings_equal_case_insensitive(const char *left, const char *right);

const char *get_admin_password(void);

#endif
