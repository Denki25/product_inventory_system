#include "../include/product.h"

#include "../include/history.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_products_by_name(const void *left, const void *right) {
    const Product *first = (const Product *)left;
    const Product *second = (const Product *)right;
    char name_a[MAX_NAME_LENGTH];
    char name_b[MAX_NAME_LENGTH];

    to_lowercase(first->name, name_a, sizeof(name_a));
    to_lowercase(second->name, name_b, sizeof(name_b));

    return strcmp(name_a, name_b);
}

size_t load_all_products(Product **products) {
    FILE *file = fopen(DATA_FILE, "rb");
    Product item;
    Product *loaded = NULL;
    size_t count = 0;

    if (products == NULL) {
        return 0;
    }

    *products = NULL;

    if (file == NULL) {
        return 0;
    }

    while (fread(&item, sizeof(Product), 1, file) == 1) {
        Product *resized = realloc(loaded, (count + 1U) * sizeof(Product));
        if (resized == NULL) {
            free(loaded);
            fclose(file);
            return 0;
        }

        loaded = resized;
        loaded[count] = item;
        count++;
    }

    fclose(file);
    *products = loaded;
    return count;
}

static int product_exists(int id, Product *found_product) {
    FILE *file = fopen(DATA_FILE, "rb");
    Product product;

    if (file == NULL) {
        return 0;
    }

    while (fread(&product, sizeof(Product), 1, file) == 1) {
        if (product.id == id) {
            if (found_product != NULL) {
                *found_product = product;
            }
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

static void print_product_table_header(void) {
    printf("+------+------------------------------+----------------------+----------+------------+\n");
    printf("| ID   | Name                         | Category             | Quantity | Price      |\n");
    printf("+------+------------------------------+----------------------+----------+------------+\n");
}

static void print_product_row(const Product *product) {
    printf("| %-4d | %-28s | %-20s | %-8d | %-10.2f |\n",
           product->id,
           product->name,
           product->category,
           product->quantity,
           product->price);
}

static void print_product_table_footer(void) {
    printf("+------+------------------------------+----------------------+----------+------------+\n");
}

void add_product(void) {
    FILE *file = fopen(DATA_FILE, "ab");
    Product product;
    char action[160];

    print_banner("Add Product");

    if (file == NULL) {
        print_message("ERROR", "Unable to open product data file.", COLOR_RED);
        wait_for_enter();
        return;
    }

    read_int_in_range("Enter product ID: ", 1, 999999, &product.id);
    if (product_exists(product.id, NULL)) {
        fclose(file);
        print_message("ERROR", "A product with that ID already exists.", COLOR_RED);
        wait_for_enter();
        return;
    }

    read_non_empty_string("Enter product name: ", product.name, sizeof(product.name));
    read_non_empty_string("Enter category: ", product.category, sizeof(product.category));
    read_int_in_range("Enter quantity: ", 0, 1000000, &product.quantity);
    read_float_in_range("Enter price: ", 0.0f, 100000000.0f, &product.price);

    fwrite(&product, sizeof(Product), 1, file);
    fclose(file);

    snprintf(action, sizeof(action), "Added product ID %d (%s)", product.id, product.name);
    log_history("ADMIN", action);
    print_message("SUCCESS", "Product added successfully.", COLOR_GREEN);
    wait_for_enter();
}

void display_products(void) {
    Product *products = NULL;
    size_t count = load_all_products(&products);

    print_banner("Product List");

    if (count == 0U || products == NULL) {
        print_message("INFO", "No products found.", COLOR_YELLOW);
        wait_for_enter();
        return;
    }

    qsort(products, count, sizeof(Product), compare_products_by_name);
    print_product_table_header();
    for (size_t index = 0; index < count; ++index) {
        print_product_row(&products[index]);
    }
    print_product_table_footer();
    printf("Total products: %zu\n", count);

    free(products);
    wait_for_enter();
}

void search_products(void) {
    Product *products = NULL;
    size_t count = 0;
    char query[MAX_INPUT_LENGTH];
    int found = 0;

    print_banner("Search Products");
    read_non_empty_string("Search by name or category: ", query, sizeof(query));

    count = load_all_products(&products);
    if (count == 0U || products == NULL) {
        print_message("INFO", "No products available to search.", COLOR_YELLOW);
        wait_for_enter();
        return;
    }

    print_product_table_header();
    for (size_t index = 0; index < count; ++index) {
        if (contains_case_insensitive(products[index].name, query) ||
            contains_case_insensitive(products[index].category, query)) {
            print_product_row(&products[index]);
            found = 1;
        }
    }
    print_product_table_footer();

    if (!found) {
        print_message("INFO", "No matching products found.", COLOR_YELLOW);
    }

    free(products);
    wait_for_enter();
}

void update_product(void) {
    FILE *source = fopen(DATA_FILE, "rb");
    FILE *temporary = NULL;
    Product product;
    int target_id = 0;
    int updated = 0;
    char action[160];

    print_banner("Update Product");

    if (source == NULL) {
        print_message("ERROR", "Unable to open product data file.", COLOR_RED);
        wait_for_enter();
        return;
    }

    temporary = fopen("data/products.tmp", "wb");
    if (temporary == NULL) {
        fclose(source);
        print_message("ERROR", "Unable to create temporary file.", COLOR_RED);
        wait_for_enter();
        return;
    }

    read_int_in_range("Enter product ID to update: ", 1, 999999, &target_id);

    while (fread(&product, sizeof(Product), 1, source) == 1) {
        if (product.id == target_id) {
            Product updated_product = product;
            char prompt[80];

            print_section("Current Product Details");
            print_product_table_header();
            print_product_row(&product);
            print_product_table_footer();

            read_non_empty_string("Enter new product name: ", updated_product.name, sizeof(updated_product.name));
            read_non_empty_string("Enter new category: ", updated_product.category, sizeof(updated_product.category));
            read_int_in_range("Enter new quantity: ", 0, 1000000, &updated_product.quantity);
            read_float_in_range("Enter new price: ", 0.0f, 100000000.0f, &updated_product.price);

            fwrite(&updated_product, sizeof(Product), 1, temporary);
            updated = 1;

            snprintf(prompt, sizeof(prompt), "Updated product ID %d (%s)", updated_product.id, updated_product.name);
            snprintf(action, sizeof(action), "%s", prompt);
        } else {
            fwrite(&product, sizeof(Product), 1, temporary);
        }
    }

    fclose(source);
    fclose(temporary);

    if (!updated) {
        remove("data/products.tmp");
        print_message("INFO", "Product ID not found.", COLOR_YELLOW);
        wait_for_enter();
        return;
    }

    remove(DATA_FILE);
    rename("data/products.tmp", DATA_FILE);
    log_history("ADMIN", action);
    print_message("SUCCESS", "Product updated successfully.", COLOR_GREEN);
    wait_for_enter();
}

void delete_product(void) {
    FILE *source = fopen(DATA_FILE, "rb");
    FILE *temporary = NULL;
    Product product;
    int target_id = 0;
    int deleted = 0;
    char action[160];

    print_banner("Delete Product");

    if (source == NULL) {
        print_message("ERROR", "Unable to open product data file.", COLOR_RED);
        wait_for_enter();
        return;
    }

    temporary = fopen("data/products.tmp", "wb");
    if (temporary == NULL) {
        fclose(source);
        print_message("ERROR", "Unable to create temporary file.", COLOR_RED);
        wait_for_enter();
        return;
    }

    read_int_in_range("Enter product ID to delete: ", 1, 999999, &target_id);

    while (fread(&product, sizeof(Product), 1, source) == 1) {
        if (product.id == target_id) {
            deleted = 1;
            snprintf(action, sizeof(action), "Deleted product ID %d (%s)", product.id, product.name);
            continue;
        }
        fwrite(&product, sizeof(Product), 1, temporary);
    }

    fclose(source);
    fclose(temporary);

    if (!deleted) {
        remove("data/products.tmp");
        print_message("INFO", "Product ID not found.", COLOR_YELLOW);
        wait_for_enter();
        return;
    }

    if (!prompt_yes_no("Confirm delete? (Y/N): ")) {
        remove("data/products.tmp");
        print_message("INFO", "Delete operation cancelled.", COLOR_YELLOW);
        wait_for_enter();
        return;
    }

    remove(DATA_FILE);
    rename("data/products.tmp", DATA_FILE);
    log_history("ADMIN", action);
    print_message("SUCCESS", "Product deleted successfully.", COLOR_GREEN);
    wait_for_enter();
}
