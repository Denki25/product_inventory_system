#include "../include/login.h"

#include "../include/history.h"
#include "../include/utils.h"

#include <stdio.h>
#include <string.h>

UserRole login_menu(void) {
    int choice = 0;

    print_banner("Product Inventory System");
    printf("| %-56s |\n", "1. Admin Login");
    printf("| %-56s |\n", "2. User Login");
    printf("| %-56s |\n", "3. Exit");
    print_divider();

    read_int_in_range("Choose an option: ", 1, 3, &choice);

    switch (choice) {
        case 1:
            return admin_login() ? ROLE_ADMIN : ROLE_NONE;
        case 2:
            return user_login() ? ROLE_USER : ROLE_NONE;
        default:
            return ROLE_NONE;
    }
}

int admin_login(void) {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    const char *admin_password = get_admin_password();

    print_banner("Admin Login");
    read_non_empty_string("Username: ", username, sizeof(username));
    read_password("Password ", password, sizeof(password));

    if (strings_equal_case_insensitive(username, "admin") &&
        strcmp(password, admin_password) == 0) {
        loading_animation("Signing in", 800);
        log_history("ADMIN", "Administrator logged in");
        print_message("SUCCESS", "Admin login successful.", COLOR_GREEN);
        sleep_ms(700);
        return 1;
    }

    log_history("ADMIN", "Failed administrator login attempt");
    print_message("ERROR", "Invalid admin credentials.", COLOR_RED);
    wait_for_enter();
    return 0;
}

int user_login(void) {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    print_banner("User Login");
    read_non_empty_string("Username: ", username, sizeof(username));
    read_password("Password ", password, sizeof(password));

    if (username[0] != '\0' && password[0] != '\0') {
        loading_animation("Signing in", 600);
        log_history("USER", "User logged in");
        print_message("SUCCESS", "User login successful.", COLOR_GREEN);
        sleep_ms(700);
        return 1;
    }

    log_history("USER", "Failed user login attempt");
    print_message("ERROR", "Invalid user credentials.", COLOR_RED);
    wait_for_enter();
    return 0;
}
