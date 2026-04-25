#include "../include/utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#include <direct.h>
#include <windows.h>
#define MKDIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#define MKDIR(path) mkdir(path, 0755)
#endif

static int read_keypress(void) {
#ifdef _WIN32
    return _getch();
#else
    struct termios old_settings;
    struct termios new_settings;
    int character = 0;

    tcgetattr(STDIN_FILENO, &old_settings);
    new_settings = old_settings;
    new_settings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
    character = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);

    return character;
#endif
}

static void discard_remaining_input(void) {
    int character = 0;

    do {
        character = getchar();
    } while (character != '\n' && character != EOF);
}

void sleep_ms(unsigned int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000U);
#endif
}

void enable_virtual_terminal(void) {
#ifdef _WIN32
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;

    if (output == INVALID_HANDLE_VALUE) {
        return;
    }

    if (!GetConsoleMode(output, &mode)) {
        return;
    }

    SetConsoleMode(output, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
}

void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void set_color(Color color) {
    switch (color) {
        case COLOR_RED:
            printf("\033[31m");
            break;
        case COLOR_GREEN:
            printf("\033[32m");
            break;
        case COLOR_YELLOW:
            printf("\033[33m");
            break;
        case COLOR_BLUE:
            printf("\033[34m");
            break;
        case COLOR_CYAN:
            printf("\033[36m");
            break;
        case COLOR_WHITE:
            printf("\033[97m");
            break;
        case COLOR_DEFAULT:
        default:
            printf("\033[0m");
            break;
    }
}

void reset_color(void) {
    set_color(COLOR_DEFAULT);
}

void print_divider(void) {
    printf("+----------------------------------------------------------+\n");
}

void print_banner(const char *title) {
    clear_screen();
    print_divider();
    printf("| %-56s |\n", title);
    print_divider();
}

void print_section(const char *title) {
    printf("\n");
    print_divider();
    printf("| %-56s |\n", title);
    print_divider();
}

void print_message(const char *label, const char *message, Color color) {
    set_color(color);
    printf("[%s] %s\n", label, message);
    reset_color();
}

void loading_animation(const char *message, unsigned int milliseconds) {
    unsigned int elapsed = 0;
    const unsigned int step = 250;
    int frame = 0;
    const char spinner[] = "|/-\\";

    printf("%s ", message);
    fflush(stdout);

    while (elapsed < milliseconds) {
        printf("\b%c", spinner[frame % 4]);
        fflush(stdout);
        sleep_ms(step);
        elapsed += step;
        frame++;
    }

    printf("\bDone\n");
}

void wait_for_enter(void) {
    char buffer[8];

    printf("\nPress Enter to continue...");
    fgets(buffer, sizeof(buffer), stdin);
}

void ensure_data_directory(void) {
    MKDIR("data");
}

void ensure_data_files(void) {
    FILE *file = NULL;

    ensure_data_directory();

    file = fopen(DATA_FILE, "ab");
    if (file != NULL) {
        fclose(file);
    }

    file = fopen(HISTORY_FILE, "a");
    if (file != NULL) {
        fclose(file);
    }
}

int read_line(const char *prompt, char *buffer, size_t size) {
    if (prompt == NULL || buffer == NULL || size == 0U) {
        return 0;
    }

    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    if (strchr(buffer, '\n') == NULL) {
        discard_remaining_input();
    }

    trim_newline(buffer);

    return 1;
}

int read_non_empty_string(const char *prompt, char *buffer, size_t size) {
    for (;;) {
        if (!read_line(prompt, buffer, size)) {
            print_message("ERROR", "Unable to read input.", COLOR_RED);
            continue;
        }

        if (buffer[0] == '\0') {
            print_message("ERROR", "Input cannot be empty.", COLOR_RED);
            continue;
        }

        return 1;
    }
}

static int parse_int(const char *text, int *value) {
    char *end = NULL;
    long parsed = 0;

    if (text == NULL || text[0] == '\0') {
        return 0;
    }

    parsed = strtol(text, &end, 10);
    if (*end != '\0') {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

static int parse_float(const char *text, float *value) {
    char *end = NULL;
    float parsed = 0.0f;

    if (text == NULL || text[0] == '\0') {
        return 0;
    }

    parsed = strtof(text, &end);
    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int read_int_in_range(const char *prompt, int min, int max, int *value) {
    char buffer[MAX_INPUT_LENGTH];
    int parsed = 0;

    for (;;) {
        if (!read_non_empty_string(prompt, buffer, sizeof(buffer))) {
            continue;
        }

        if (!parse_int(buffer, &parsed)) {
            print_message("ERROR", "Enter numbers only.", COLOR_RED);
            continue;
        }

        if (parsed < min || parsed > max) {
            char error_message[100];
            snprintf(error_message, sizeof(error_message), "Enter a value between %d and %d.", min, max);
            print_message("ERROR", error_message, COLOR_RED);
            continue;
        }

        *value = parsed;
        return 1;
    }
}

int read_float_in_range(const char *prompt, float min, float max, float *value) {
    char buffer[MAX_INPUT_LENGTH];
    float parsed = 0.0f;

    for (;;) {
        if (!read_non_empty_string(prompt, buffer, sizeof(buffer))) {
            continue;
        }

        if (!parse_float(buffer, &parsed)) {
            print_message("ERROR", "Enter a valid number.", COLOR_RED);
            continue;
        }

        if (parsed < min || parsed > max) {
            char error_message[100];
            snprintf(error_message, sizeof(error_message), "Enter a value between %.2f and %.2f.", min, max);
            print_message("ERROR", error_message, COLOR_RED);
            continue;
        }

        *value = parsed;
        return 1;
    }
}

int prompt_yes_no(const char *prompt) {
    char buffer[8];

    for (;;) {
        if (!read_non_empty_string(prompt, buffer, sizeof(buffer))) {
            continue;
        }

        if (strings_equal_case_insensitive(buffer, "y") ||
            strings_equal_case_insensitive(buffer, "yes")) {
            return 1;
        }

        if (strings_equal_case_insensitive(buffer, "n") ||
            strings_equal_case_insensitive(buffer, "no")) {
            return 0;
        }

        print_message("ERROR", "Enter Y or N.", COLOR_RED);
    }
}

void read_password(const char *prompt, char *buffer, size_t size) {
    size_t length = 0;
    int masked = 1;

    if (buffer == NULL || size == 0U) {
        return;
    }

    buffer[0] = '\0';
    printf("%s", prompt);
    printf("(Press Ctrl+T to toggle visibility)\n> ");

    for (;;) {
        int character = read_keypress();

        if (character == '\r' || character == '\n') {
            break;
        }

        if (character == 20) {
            masked = !masked;
            printf("\r> ");
            for (size_t index = 0; index < length; ++index) {
                putchar(masked ? '*' : buffer[index]);
            }
            fflush(stdout);
            continue;
        }

        if ((character == '\b' || character == 127) && length > 0U) {
            length--;
            buffer[length] = '\0';
            printf("\b \b");
            fflush(stdout);
            continue;
        }

        if (isprint(character) && length + 1U < size) {
            buffer[length++] = (char)character;
            buffer[length] = '\0';
            putchar(masked ? '*' : character);
            fflush(stdout);
        }
    }

    putchar('\n');
}

void trim_newline(char *text) {
    size_t length = 0;

    if (text == NULL) {
        return;
    }

    length = strlen(text);
    while (length > 0U &&
           (text[length - 1U] == '\n' || text[length - 1U] == '\r')) {
        text[length - 1U] = '\0';
        length--;
    }
}

void to_lowercase(const char *source, char *destination, size_t size) {
    size_t index = 0;

    if (source == NULL || destination == NULL || size == 0U) {
        return;
    }

    while (source[index] != '\0' && index + 1U < size) {
        destination[index] = (char)tolower((unsigned char)source[index]);
        index++;
    }

    destination[index] = '\0';
}

int contains_case_insensitive(const char *text, const char *pattern) {
    char lowered_text[MAX_INPUT_LENGTH];
    char lowered_pattern[MAX_INPUT_LENGTH];

    if (text == NULL || pattern == NULL) {
        return 0;
    }

    to_lowercase(text, lowered_text, sizeof(lowered_text));
    to_lowercase(pattern, lowered_pattern, sizeof(lowered_pattern));

    return strstr(lowered_text, lowered_pattern) != NULL;
}

int strings_equal_case_insensitive(const char *left, const char *right) {
    char lowered_left[MAX_INPUT_LENGTH];
    char lowered_right[MAX_INPUT_LENGTH];

    if (left == NULL || right == NULL) {
        return 0;
    }

    to_lowercase(left, lowered_left, sizeof(lowered_left));
    to_lowercase(right, lowered_right, sizeof(lowered_right));

    return strcmp(lowered_left, lowered_right) == 0;
}

const char *get_admin_password(void) {
    const char *environment_password = getenv("PRODUCT_INVENTORY_ADMIN_PASSWORD");

    if (environment_password != NULL && environment_password[0] != '\0') {
        return environment_password;
    }

    return ADMIN_PASSWORD;
}
