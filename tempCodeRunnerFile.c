#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>

#define DATA "products.dat"
#define HISTORY "history.txt"

char currentAdmin[50] = "Unknown";

struct Product {
	 int id;
	 char name[50];
	 char category[50];
	 float price;
	 int stock;
};

void adminMenu();
void userMenu();

void getPasswordWithToggle(char *password);
void getPassword(char *password);
void addProduct();
void displayProducts();
void searchProductLive();
void updateProduct();
void deleteProduct();
void viewHistory();
void clearHistory();
void logAction(const char *action);


int getNextId();

//================= LOGIN SYSTEM =================//

void login() {
	 int choice;
	 char password[50];
	 int attempts = 0;

login_start:

	 printf("============================================================\n");
	 printf("||                                                        ||\n");
	 printf("||                PRODUCT INVENTORY SYSTEM                ||\n");
	 printf("||                         LOGIN                          ||\n");
	 printf("||                                                        ||\n");
	 printf("============================================================\n\n");
	 printf("                      [1] ADMIN LOGIN\n");
	 printf("                      [2] USER LOGIN\n");
	 printf("                      [3] EXIT\n\n");
	 printf("============================================================\n");


        char input[50];
             while (1) {
            printf("Enter choice: ");
            fgets(input, sizeof(input), stdin);

            // remove newline
            input[strcspn(input, "\n")] = 0;

            if (strlen(input) == 0) {
                attempts++;
                printf("\nInvalid choice! Empty input not allowed.\n");
            } else {
                // check if numeric
                int isNumber = 1;
                for (int i = 0; input[i] != '\0'; i++) {
                    if (!isdigit(input[i])) {
                        isNumber = 0;
                        break;
                    }
                }

                if (!isNumber) {
                    attempts++;
                    printf("\nInvalid choice! Must be a number.\n");
                } else {
                    choice = atoi(input);
                    if (choice < 1 || choice > 3) {
                        attempts++;
                        printf("\nInvalid choice! Must be between 1 and 3.\n");
                    } else {
                        break;
                    }
                }
            }

            printf("Attempts: %d/3\n", attempts);
            if (attempts >= 3) {
                printf("\nToo many failed attempts. Exiting system");
                for (int i = 0; i < 3; i++) {
                    printf(".");
                    fflush(stdout);
                    Sleep(200);
                }
                exit(0);
            }
        }

    if (choice == 1) {

    int attempts = 0;

    while (attempts < 3) {
        system("cls");

        printf("=============================================================\n");
        printf("||                       ADMIN LOGIN                       ||\n");
        printf("=============================================================\n\n");


        printf("Enter Admin Name: ");
        fgets(currentAdmin, sizeof(currentAdmin), stdin);
        currentAdmin[strcspn(currentAdmin, "\n")] = 0;


        printf("Enter Password: ");
        getPasswordWithToggle(password);

        if (strcmp(password, "1234") == 0) {

            printf("\nLogging in");
            for (int i = 0; i < 3; i++) {
                printf(".");
                fflush(stdout);
                Sleep(700);
            }

            printf("\n\nACCESS GRANTED\n");
            Sleep(1000);

            adminMenu();
            return;

        } else {
            attempts++;
            printf("\nInvalid password!\n");
            printf("Attempts: %d/3\n", attempts);
            Sleep(1500);

            if (attempts >= 3) {
                printf("\nToo many failed attempts. Exiting system");
                for (int i = 0; i < 3; i++) {
                    printf(".");
                    fflush(stdout);
                    Sleep(200);
                }
                exit(0);
            }
        }
    }
}
	 else if (choice == 2) {

		  system("cls");

		  printf("============================================================\n");
		  printf("||                       USER LOGIN                       ||\n");
		  printf("============================================================\n\n");

		  printf("Welcome User!\n");
		  printf("Limited access granted.\n");

		  Sleep(1500);

		  userMenu();
		  return;

	 }
	 else if (choice == 3) {
		  printf("\nExiting system");
		  for (int i = 0; i < 3; i++) {
				printf(".");
				fflush(stdout);
				Sleep(700);
		  }
		  exit(0);
	 }
	 else {
		  printf("\nInvalid choice!\n");
		  Sleep(1000);
		  goto login_start;
	 }
}

//================= MENUS =================//


void adminMenu() {              /////ADMIN MENU//////
	 int choice;
	 system("cls");

	 while (1) {

		  printf("\n");
		  printf("        ------------------------------------------\n");
		  printf("        |          MENU OPTIONS (ADMIN)          |\n");
		  printf("        |----------------------------------------|\n");
		  printf("        |  [1] Add Product                       |\n");
		  printf("        |  [2] Display Products                  |\n");
		  printf("        |  [3] Search Product                    |\n");
		  printf("        |  [4] Update Stock                      |\n");
		  printf("        |  [5] Delete Product                    |\n");
		  printf("        |  [6] View History                      |\n");
          printf("        |  [7] Clear History                     |\n");
		  printf("        |  [8] Logout                            |\n");
		  printf("        ------------------------------------------\n");

		  printf("\n");
		  printf("==========================================================\n");

          char input[50];
          int attempts = 0;

             while (1) {
    printf("Enter your choice: ");
    fgets(input, sizeof(input), stdin);

    // remove newline
    input[strcspn(input, "\n")] = 0;

    if (strlen(input) == 0) {
        attempts++;
        printf("\nInvalid choice! Empty input not allowed.\n");
        printf("Attempts: %d/3\n", attempts);
    } else {
        // check if numeric
        int isNumber = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                isNumber = 0;
                break;
            }
        }

        if (!isNumber) {
            attempts++;
            printf("\nInvalid choice! Must be a number.\n");
            printf("Attempts: %d/3\n", attempts);
        } else {
            choice = atoi(input);
            if (choice < 1 || choice > 8) {   // ✅ fixed range
                attempts++;
                printf("\nInvalid choice! Must be between 1 and 8.\n");
                printf("Attempts: %d/3\n", attempts);
            } else {
                break; // ✅ valid input
            }
        }
    }

    if (attempts >= 3) {
        printf("\nToo many failed attempts. Exiting system");
        for (int i = 0; i < 3; i++) {
            printf(".");
            fflush(stdout);
            Sleep(200);
        }
        exit(0);
    }
}

printf("\nLoading");
for (int i = 0; i < 3; i++) {
    printf(".");
    fflush(stdout);
    Sleep(500);
}


	switch (choice) {
	    case 1: addProduct(); break;
	    case 2: displayProducts(); break;
	    case 3: searchProductLive(); break;
	    case 4: updateProduct(); break;
	    case 5: deleteProduct(); break;
	    case 6: viewHistory(); break;
	    case 7: clearHistory(); break;
	    case 8: return;
	    default:
		printf("\nInvalid choice!\n");
		Sleep(1000);
	}
    }
}

void userMenu() {               //////USER MENU////////
    int choice;

    while (1) {
		printf("\n");
	printf("        ------------------------------------------\n");
	printf("        |          MENU OPTIONS (USER)           |\n");
	printf("        |----------------------------------------|\n");
	printf("        |  [1] Display Products                  |\n");
	printf("        |  [2] Search Products                   |\n");
	printf("        |  [3] Logout                            |\n");
	printf("        ------------------------------------------\n");

	printf("\n");
	printf("==========================================================\n");

    char input[50];
    int attempts = 0;
             while (1) {
            printf("Enter choice: ");
            fgets(input, sizeof(input), stdin);

            // remove newline
            input[strcspn(input, "\n")] = 0;

            if (strlen(input) == 0) {
                attempts++;
                printf("\nInvalid choice! Empty input not allowed.\n");
            } else {
                // check if numeric
                int isNumber = 1;
                for (int i = 0; input[i] != '\0'; i++) {
                    if (!isdigit(input[i])) {
                        isNumber = 0;
                        break;
                    }
                }

                if (!isNumber) {
                    attempts++;
                    printf("\nInvalid choice! Must be a number.\n");
                } else {
                    choice = atoi(input);
                    if (choice < 1 || choice > 3) {
                        attempts++;
                        printf("\nInvalid choice! Must be between 1 and 3.\n");
                    } else {
                        break;
                    }
                }
            }

            printf("Attempts: %d/3\n", attempts);
            if (attempts >= 3) {
                printf("\nToo many failed attempts. Exiting system");
                for (int i = 0; i < 3; i++) {
                    printf(".");
                    fflush(stdout);
                    Sleep(200);
                }
                exit(0);
            }
        }

	switch (choice) {
	    case 1: displayProducts(); break;
	    case 2: searchProductLive(); break;
	    case 3: return;
	    default: printf("Invalid choice!\n");
	}
    }
}


void getPasswordWithToggle(char *password) {    /////TOGGLE
    int i = 0;
    char ch;
    int show = 0;

    while (1) {
        ch = getch();

        if (ch == 13) {
            password[i] = '\0';
            break;
        }
        else if (ch == 9) {
        show = !show;

        printf("\r");                 // return to start
        printf("Enter Password: ");   // rewrite prompt
        printf("%-*s", 50, "");       // clear line

        printf("\rEnter Password: "); // go back again

        for (int j = 0; j < i; j++) {
            if (show)
                printf("%c", password[j]);
            else
                printf("*");
        }
    }
        else if (ch == 8) {
            if (i > 0) {
                i--;
                password[i] = '\0';

                printf("\rEnter Password: ");
                printf("%-*s", 50, "");
                printf("\rEnter Password: ");

                for (int j = 0; j < i; j++) {
                    if (show)
                        printf("%c", password[j]);
                    else
                        printf("*");
                }
            }
        }
        else if (ch != 0 && ch != 224) {
            password[i++] = ch;
            password[i] = '\0';

            if (show)
                printf("%c", ch);
            else
                printf("*");
        }
    }
}
void getPassword(char *password) {      ////////password masking
    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        // ENTER key
        if (ch == 13) {
            password[i] = '\0';
            break;
        }
        // BACKSPACE
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        // Normal characters
        else if (ch != 0 && ch != 224) {
            password[i++] = ch;
            printf("*");
        }
    }
}

/* ================= PRODUCT FUNCTIONS ================= */

int getNextId() {
    FILE *fp = fopen(DATA, "rb");
    struct Product p;
    int id = 1;

    if (fp == NULL) return id;

    while (fread(&p, sizeof(p), 1, fp)) {
	if (p.id >= id)
	    id = p.id + 1;
    }

    fclose(fp);
    return id;
}

void addProduct() {
    FILE *fp = fopen(DATA, "ab");
    struct Product p;
    int n, categoryChoice;
    char input[50];
    int attempts;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // ===== NUMBER OF PRODUCTS VALIDATION =====
    attempts = 0;
    while (1) {
        printf("\nEnter number of products to add: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            attempts++;
            printf("\nInvalid choice! Empty input not allowed.\n");
            printf("Attempts: %d/3\n", attempts);
        } else {
            int isNumber = 1;
            for (int i = 0; input[i] != '\0'; i++) {
                if (!isdigit(input[i])) { isNumber = 0; break; }
            }
            if (!isNumber) {
                attempts++;
                printf("\nInvalid choice! Must be a number.\n");
                printf("Attempts: %d/3\n", attempts);
            } else {
                n = atoi(input);
                if (n <= 0) {
                    attempts++;
                    printf("\nInvalid choice! Must be greater than 0.\n");
                    printf("Attempts: %d/3\n", attempts);
                } else break;
            }
        }
        if (attempts >= 3) { printf("\nToo many failed attempts. Exiting system...\n"); exit(0); }
    }

    // ===== LOOP FOR EACH PRODUCT =====
    for (int i = 1; i <= n; i++) {
        system("cls");
        printf("=============================================\n");
        printf("               ADD NEW PRODUCT               \n");
        printf("=============================================\n\n");
        printf("[ Product #%d ]\n\n", i);

        p.id = getNextId();

        // ===== NAME VALIDATION =====
        while (1) {
            printf("Name     : ");
            fgets(p.name, sizeof(p.name), stdin);
            p.name[strcspn(p.name, "\n")] = 0;
            if (strlen(p.name) == 0) {
                printf("\nInvalid choice! Empty input not allowed.\n");
                printf("Attempts: N/A (no limit for name)\n");
                continue;
            }
            int onlySpaces = 1;
            for (int j = 0; p.name[j] != '\0'; j++) {
                if (!isspace(p.name[j])) { onlySpaces = 0; break; }
            }
            if (onlySpaces) {
                printf("\nInvalid choice! Name cannot be just spaces.\n");
                printf("Attempts: N/A (no limit for name)\n");
                continue;
            }
            break;
        }

        // ===== CATEGORY VALIDATION =====
attempts = 0;
while (1) {
    printf("\nSelect Category:\n");
    printf("1. Food\n");
    printf("2. Electronics\n");
    printf("3. School Supplies\n");
    printf("4. Others (Specify)\n");
    printf("Choice   : ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    if (strlen(input) == 0) {
        attempts++;
        printf("\nInvalid choice! Empty input not allowed.\n");
        printf("Attempts: %d/3\n", attempts);
    } else {
        int isNumber = 1;
        for (int j = 0; input[j] != '\0'; j++) {
            if (!isdigit(input[j])) { isNumber = 0; break; }
        }
        if (!isNumber) {
            attempts++;
            printf("\nInvalid choice! Must be a number.\n");
            printf("Attempts: %d/3\n", attempts);
        } else {
            categoryChoice = atoi(input);
            if (categoryChoice < 1 || categoryChoice > 4) {
                attempts++;
                printf("\nInvalid choice! Must be between 1 and 4.\n");
                printf("Attempts: %d/3\n", attempts);
            } else {
                switch (categoryChoice) {
                    case 1: strcpy(p.category, "Food"); break;
                    case 2: strcpy(p.category, "Electronics"); break;
                    case 3: strcpy(p.category, "School Supplies"); break;
                    case 4:
                        // Ask for specific category name
                        while (1) {
                            printf("Enter specific category name: ");
                            fgets(p.category, sizeof(p.category), stdin);
                            p.category[strcspn(p.category, "\n")] = 0;

                            if (strlen(p.category) == 0) {
                                printf("\nInvalid choice! Empty input not allowed.\n");
                                printf("Attempts: N/A (no limit for category name)\n");
                                continue;
                            }
                            int onlySpaces = 1;
                            for (int k = 0; p.category[k] != '\0'; k++) {
                                if (!isspace(p.category[k])) { onlySpaces = 0; break; }
                            }
                            if (onlySpaces) {
                                printf("\nInvalid choice! Category cannot be just spaces.\n");
                                printf("Attempts: N/A (no limit for category name)\n");
                                continue;
                            }
                            break;
                        }
                        break;
                }
                break; // exit category loop
            }
        }
    }
            if (attempts >= 3) {
                printf("\nToo many failed attempts. Exiting system...\n");
                exit(0);
            }
        }

        // ===== PRICE VALIDATION =====
        attempts = 0;
        while (1) {
            printf("Price    : ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;
            if (strlen(input) == 0) {
                attempts++;
                printf("\nInvalid choice! Empty input not allowed.\n");
                printf("Attempts: %d/3\n", attempts);
            } else {
                char *endptr;
                p.price = strtof(input, &endptr);
                if (*endptr != '\0' || p.price <= 0) {
                    attempts++;
                    printf("\nInvalid choice! Must be greater than 0.\n");
                    printf("Attempts: %d/3\n", attempts);
                } else break;
            }
            if (attempts >= 3) { printf("\nToo many failed attempts. Exiting system...\n"); exit(0); }
        }

        // ===== STOCK VALIDATION =====
        attempts = 0;
        while (1) {
            printf("Stock    : ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;
            if (strlen(input) == 0) {
                attempts++;
                printf("\nInvalid choice! Empty input not allowed.\n");
                printf("Attempts: %d/3\n", attempts);
            } else {
                int isNumber = 1;
                for (int j = 0; input[j] != '\0'; j++) {
                    if (!isdigit(input[j])) { isNumber = 0; break; }
                }
                if (!isNumber) {
                    attempts++;
                    printf("\nInvalid choice! Must be a number.\n");
                    printf("Attempts: %d/3\n", attempts);
                } else {
                    p.stock = atoi(input);
                    if (p.stock < 0) {
                        attempts++;
                        printf("\nInvalid choice! Must be zero or greater.\n");
                        printf("Attempts: %d/3\n", attempts);
                    } else break;
                }
            }
            if (attempts >= 3) { printf("\nToo many failed attempts. Exiting system...\n"); exit(0); }
        }

        ///////CONFIRMATION////
attempts = 0;
while (1) {
    system("cls");
    printf("=============================================\n");
    printf("           CONFIRM PRODUCT DETAILS           \n");
    printf("=============================================\n\n");

    // Table preview of product
    printf("-------------------------------------------------------------------------\n");
    printf("| %-4s | %-20s | %-15s | %-10s | %-8s |\n",
           "ID", "NAME", "CATEGORY", "PRICE(₱)", "STOCK");
    printf("-------------------------------------------------------------------------\n");
    printf("| %-4d | %-20s | %-15s | %-10.2f | %-8d |\n",
           p.id, p.name, p.category, p.price, p.stock);
    printf("-------------------------------------------------------------------------\n");

    // Ask for confirmation
    printf("\nIs this correct? Save this product? (Y/N): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    if (strlen(input) == 0) {
        attempts++;
        printf("\nInvalid choice! Empty input not allowed.\n");
        printf("Attempts: %d/3\n", attempts);
    } else if (strlen(input) > 1) {
        attempts++;
        printf("\nInvalid choice! Must be a single character (Y/N).\n");
        printf("Attempts: %d/3\n", attempts);
    } else {
        char confirm = toupper(input[0]);
        if (confirm == 'Y') {
            fwrite(&p, sizeof(p), 1, fp);
            printf("\nProduct saved successfully!\n");
            logAction("Added Product");
            break;
        } else if (confirm == 'N') {
            printf("\nProduct discarded.\n");
            break;
        } else {
            attempts++;
            printf("\nInvalid choice! Must be Y or N.\n");
            printf("Attempts: %d/3\n", attempts);
        }
    }

    if (attempts >= 3) {
        printf("\nToo many failed attempts. Exiting system");
        for (int i = 0; i < 3; i++) {
            printf(".");
            fflush(stdout);
            Sleep(200);
        }
        exit(0);
    }

}

}

fclose(fp);
printf("\nAll entries processed!\n");
Sleep(1000);
system("cls");

}

void displayProducts() {            //////display product
    system("cls");
    FILE *fp = fopen(DATA, "rb");
    struct Product p;

    if (fp == NULL) {
	printf("No records found.\n");
	return;
    }

    printf("\n");
    printf("=========================================================================\n");
    printf("||                       PRODUCT INVENTORY LIST                        ||\n");
    printf("=========================================================================\n");

    printf("-------------------------------------------------------------------------\n");
    printf("| %-4s | %-20s | %-15s | %-10s | %-8s |\n",
	   "ID", "NAME", "CATEGORY", "PRICE(₱)", "STOCK");
    printf("-------------------------------------------------------------------------\n");

    while (fread(&p, sizeof(p), 1, fp)) {
	printf("| %-4d | %-20s | %-15s | %-10.2f | %-8d |\n",
	       p.id,
	       p.name,
	       p.category,
	       p.price,
	       p.stock);
    }

    printf("-------------------------------------------------------------------------\n\n");

    fclose(fp);

}


void updateProduct() {
    FILE *fp = fopen(DATA, "rb+");
    struct Product p;
    int id, choice, found = 0;
    char input[50];
    int attempts = 0;

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    displayProducts();

    printf("\nEnter product ID to update: ");
    fgets(input, sizeof(input), stdin);
    id = atoi(input);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            found = 1;

            printf("\nWhat do you want to update?\n");
            printf("[1] Name\n[2] Category\n[3] Price\n[4] Stock\n");

            // validate choice
            attempts = 0;
            while (1) {
                printf("Enter choice: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;

                if (strlen(input) == 0) {
                    attempts++;
                    printf("\nInvalid choice! Empty input not allowed.\n");
                    printf("Attempts: %d/3\n", attempts);
                } else if (!isdigit(input[0])) {
                    attempts++;
                    printf("\nInvalid choice! Must be a number.\n");
                    printf("Attempts: %d/3\n", attempts);
                } else {
                    choice = atoi(input);
                    if (choice < 1 || choice > 4) {
                        attempts++;
                        printf("\nInvalid choice! Must be between 1 and 4.\n");
                        printf("Attempts: %d/3\n", attempts);
                    } else break;
                }
                if (attempts >= 3) { printf("\nToo many failed attempts. Exiting...\n"); exit(0); }
            }

            // perform update
            if (choice == 1) {
                printf("Enter new name: ");
                fgets(p.name, sizeof(p.name), stdin);
                p.name[strcspn(p.name, "\n")] = 0;
            } else if (choice == 2) {
                printf("Enter new category: ");
                fgets(p.category, sizeof(p.category), stdin);
                p.category[strcspn(p.category, "\n")] = 0;
            } else if (choice == 3) {
                printf("Enter new price: ");
                fgets(input, sizeof(input), stdin);
                p.price = atof(input);
            } else if (choice == 4) {
                printf("Enter new stock: ");
                fgets(input, sizeof(input), stdin);
                p.stock = atoi(input);
            }

            fseek(fp, -(long)sizeof(p), SEEK_CUR);
            fwrite(&p, sizeof(p), 1, fp);

            system("cls");
            printf("\nProduct updated successfully!\n");
            logAction("Updated Product");
            break;
        }
    }

    if (!found) printf("Product not found.\n");
    fclose(fp);
}


void deleteProduct() {
    FILE *fp = fopen(DATA, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Product p;
    int id, found = 0;
    char input[50];
    int attempts = 0;

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    displayProducts();

    // ===== ID VALIDATION =====
    attempts = 0;
    while (1) {
        printf("\nEnter product ID to delete: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            attempts++;
            printf("\nInvalid choice! Empty input not allowed.\n");
            printf("Attempts: %d/3\n", attempts);
        } else {
            int isNumber = 1;
            for (int i = 0; input[i] != '\0'; i++) {
                if (!isdigit(input[i])) { isNumber = 0; break; }
            }
            if (!isNumber) {
                attempts++;
                printf("\nInvalid choice! Must be a number.\n");
                printf("Attempts: %d/3\n", attempts);
            } else {
                id = atoi(input);
                if (id <= 0) {
                    attempts++;
                    printf("\nInvalid choice! Must be greater than 0.\n");
                    printf("Attempts: %d/3\n", attempts);
                } else break;
            }
        }
        if (attempts >= 3) { printf("\nToo many failed attempts. Exiting system...\n"); exit(0); }
    }

    // ===== CONFIRMATION =====
    char confirmInput[10];
    attempts = 0;
    while (1) {
        printf("Are you sure you want to delete product ID %d? (Y/N): ", id);
        fgets(confirmInput, sizeof(confirmInput), stdin);
        confirmInput[strcspn(confirmInput, "\n")] = 0;

        if (strlen(confirmInput) == 0) {
            attempts++;
            printf("\nInvalid choice! Empty input not allowed.\n");
            printf("Attempts: %d/3\n", attempts);
        } else if (strlen(confirmInput) > 1) {
            attempts++;
            printf("\nInvalid choice! Must be a single character (Y/N).\n");
            printf("Attempts: %d/3\n", attempts);
        } else {
            char confirm = toupper(confirmInput[0]);
            if (confirm == 'Y') break;
            else if (confirm == 'N') {
                printf("Deletion cancelled.\n");
                fclose(fp); fclose(temp);
                remove("temp.dat");
                return;
            } else {
                attempts++;
                printf("\nInvalid choice! Must be Y or N.\n");
                printf("Attempts: %d/3\n", attempts);
            }
        }
        if (attempts >= 3) { printf("\nToo many failed attempts. Exiting system...\n"); exit(0); }
    }

    // ===== PERFORM DELETION =====
    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id != id) {
            fwrite(&p, sizeof(p), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(DATA);
    rename("temp.dat", DATA);

    if (found) {
        system("cls");
        printf("Product deleted successfully.\n");
        logAction("Deleted Product");
    } else {
        printf("Product not found.\n");
    }
}

void viewHistory() {
    FILE *fp = fopen(HISTORY, "r");
    char line[200];
    int count = 0;

    system("cls");

    printf("=============================================================\n");
    printf("                       SYSTEM HISTORY                        \n");
    printf("=============================================================\n\n");

    if (fp == NULL) {
        printf("No history found.\n");
        return;
    }

    // Print history with pagination
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
        count++;

        // Pause every 20 lines
        if (count % 20 == 0) {
            printf("\n-- Press any key to continue --");
            getch();
            system("cls");

            printf("=============================================================\n");
            printf("                       SYSTEM HISTORY                        \n");
            printf("=============================================================\n\n");
        }
    }

    fclose(fp);

    printf("\n=============================================================\n");
    printf("End of history log.\n");
    printf("Total entries displayed: %d\n", count);
}


void logAction(const char *action) {
	 FILE *fp = fopen(HISTORY, "a");
	 if (fp == NULL) return;

	 time_t now = time(NULL);
	 char *dt = ctime(&now);

	 dt[strcspn(dt, "\n")] = 0; // remove newline

	 fprintf(fp, "[%s] Admin: %s | Action: %s\n", dt, currentAdmin, action);

	 printf("==========================================================\n");
	 fclose(fp);
}

void searchProductLive() {
    FILE *fp;
    struct Product p;

    char input[50] = "";
    int i = 0;
    int ch;

    while (1) {
        system("cls");

        printf("Search Product: %s\n\n", input);

        fp = fopen(DATA, "rb");
        if (fp == NULL) {
            printf("No records found.\n");
            return;
        }

        // ================= SUGGESTIONS =================
        if (strlen(input) > 0) {
            printf("Suggestions:\n");

            int found = 0;

            while (fread(&p, sizeof(p), 1, fp)) {
                if (strstr(p.name, input)) {
                    printf(" - %s\n", p.name);
                    found = 1;
                }
            }

            if (!found) {
                printf(" No matches found.\n");
            }
        } else {
            printf("Type to search products...\n");
        }

        fclose(fp);

        // ================= INPUT =================
        ch = getch();

        // ENTER → SHOW TABLE
        if (ch == 13) {
            system("cls");

            fp = fopen(DATA, "rb");
            if (fp == NULL) {
                printf("No records found.\n");
                return;
            }

            printf("=========================================================================\n");
            printf("||                       SEARCH RESULTS                         ||\n");
            printf("=========================================================================\n");

            printf("-------------------------------------------------------------------------\n");
            printf("| %-4s | %-20s | %-15s | %-10s | %-8s |\n",
                   "ID", "NAME", "CATEGORY", "PRICE(₱)", "STOCK");
            printf("-------------------------------------------------------------------------\n");

            int hasResult = 0;

            while (fread(&p, sizeof(p), 1, fp)) {
                if (strstr(p.name, input)) {
                    printf("| %-4d | %-20s | %-15s | %-10.2f | %-8d |\n",
                           p.id,
                           p.name,
                           p.category,
                           p.price,
                           p.stock);
                    hasResult = 1;
                }
            }

            if (!hasResult) {
                printf("| %-70s |\n", "No matching products found.");
            }

            printf("-------------------------------------------------------------------------\n\n");

            fclose(fp);

            printf("Press any key to continue...");
            getch();
            return;
        }

        // BACKSPACE
        else if (ch == 8 && i > 0) {
            i--;
            input[i] = '\0';
        }

        // NORMAL CHAR
        else if (isprint(ch) && i < 49) {
            input[i++] = ch;
            input[i] = '\0';
        }
    }
}

void clearHistory() {
    char input[10];
    char confirm;
    int attempts = 0;

    while (1) {
        printf("Are you sure you want to clear history? (Y/N): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            attempts++;
            printf("\nInvalid choice! Empty input not allowed.\n");
            printf("Attempts: %d/3\n", attempts);
        } else if (strlen(input) > 1) {
            attempts++;
            printf("\nInvalid choice! Must be a single character (Y/N).\n");
            printf("Attempts: %d/3\n", attempts);
        } else {
            confirm = toupper(input[0]);
            if (confirm == 'Y') {
                FILE *fp = fopen(HISTORY, "w");
                if (fp == NULL) {
                    printf("Error clearing history!\n");
                    return;
                }
                fclose(fp);

                system("cls");
                printf("History cleared successfully.\n");
                break;
            } else if (confirm == 'N') {
                printf("Clear history cancelled.\n");
                break;
            } else {
                attempts++;
                printf("\nInvalid choice! Must be Y or N.\n");
                printf("Attempts: %d/3\n", attempts);
            }
        }

        if (attempts >= 3) {
            printf("\nToo many failed attempts. Exiting system");
            for (int i = 0; i < 3; i++) {
                printf(".");
                fflush(stdout);
                Sleep(200);
            }
            exit(0);
        }
    }
}

//================= MAIN =================//

int main() {
	 system("cls");
	 login();
	 return 0;
}
