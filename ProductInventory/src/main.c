#include "../include/history.h"
#include "../include/login.h"
#include "../include/product.h"
#include "../include/utils.h"

#include <stdio.h>

static void admin_dashboard(void) {
    int choice = 0;

    for (;;) {
        print_banner("Admin Dashboard");
        printf("| %-56s |\n", "1. Add Product");
        printf("| %-56s |\n", "2. Display Products");
        printf("| %-56s |\n", "3. Search Product");
        printf("| %-56s |\n", "4. Update Product");
        printf("| %-56s |\n", "5. Delete Product");
        printf("| %-56s |\n", "6. View History Logs");
        printf("| %-56s |\n", "7. Clear History");
        printf("| %-56s |\n", "8. Logout");
        print_divider();

        read_int_in_range("Choose an option: ", 1, 8, &choice);

        switch (choice) {
            case 1:
                add_product();
                break;
            case 2:
                display_products();
                break;
            case 3:
                search_products();
                break;
            case 4:
                update_product();
                break;
            case 5:
                delete_product();
                break;
            case 6:
                view_history();
                break;
            case 7:
                clear_history();
                break;
            case 8:
                log_history("ADMIN", "Administrator logged out");
                return;
            default:
                break;
        }
    }
}

static void user_dashboard(void) {
    int choice = 0;

    for (;;) {
        print_banner("User Dashboard");
        printf("| %-56s |\n", "1. Display Products");
        printf("| %-56s |\n", "2. Search Product");
        printf("| %-56s |\n", "3. Logout");
        print_divider();

        read_int_in_range("Choose an option: ", 1, 3, &choice);

        switch (choice) {
            case 1:
                display_products();
                break;
            case 2:
                search_products();
                break;
            case 3:
                log_history("USER", "User logged out");
                return;
            default:
                break;
        }
    }
}

int main(void) {
    UserRole role = ROLE_NONE;

    enable_virtual_terminal();
    ensure_data_files();

    for (;;) {
        role = login_menu();

        if (role == ROLE_ADMIN) {
            admin_dashboard();
            continue;
        }

        if (role == ROLE_USER) {
            user_dashboard();
            continue;
        }

        print_banner("Exit");
        print_message("INFO", "Thank you for using Product Inventory System.", COLOR_CYAN);
        break;
    }

    return 0;
}
