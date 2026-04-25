#ifndef PRODUCT_H
#define PRODUCT_H

#include <stddef.h>

#include "utils.h"

typedef struct Product {
    int id;
    char name[MAX_NAME_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    int quantity;
    float price;
} Product;

void add_product(void);
void display_products(void);
void search_products(void);
void update_product(void);
void delete_product(void);
size_t load_all_products(Product **products);

#endif
