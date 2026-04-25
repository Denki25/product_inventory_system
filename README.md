# Product Inventory System

A refactored, modular, console-based Product Inventory System written in C. This project keeps the original file-based workflow while improving structure, portability, validation, and overall code quality for a GitHub-ready portfolio project.

## Features

- Admin login
- User login
- Password masking with visibility toggle (`Ctrl+T`)
- Add product
- Display products
- Search products with case-insensitive partial matching
- Update product
- Delete product
- View history logs
- Clear history logs
- Binary product storage using `data/products.dat`
- Text log storage using `data/history.txt`
- Cross-platform console support for Windows and Linux/macOS
- Sorted product display
- Search by product name or category

## Project Structure

```text
ProductInventory/
|-- src/
|   |-- main.c
|   |-- login.c
|   |-- product.c
|   |-- history.c
|   `-- utils.c
|-- include/
|   |-- login.h
|   |-- product.h
|   |-- history.h
|   `-- utils.h
|-- data/
|   |-- products.dat
|   `-- history.txt
|-- README.md
|-- Makefile
|-- .gitignore
`-- LICENSE
```

## Build

### Using GCC directly

```bash
gcc -Wall -Wextra -Wpedantic -std=c11 -Iinclude src/*.c -o inventory
```

### Using Make

```bash
make
```

On Windows with MSYS2/MinGW, run `mingw32-make` if `make` is not available.

## Run

```bash
./inventory
```

## Default Credentials

- Admin username: 1234
- Admin password: 1234

You can override the admin password with an environment variable:

```bash
PRODUCT_INVENTORY_ADMIN_PASSWORD=mysecurepassword
```

## Notes

- Product data is stored in binary format inside `data/products.dat`.
- Activity logs are stored in plain text inside `data/history.txt`.
- The application auto-creates the `data/` directory and missing data files on startup.

## Portability

The project uses conditional compilation with `#ifdef _WIN32` for:

- screen clearing
- sleeping/loading delay
- password input behavior
- directory creation

ANSI colors are enabled on modern Windows terminals and work natively on Linux/macOS terminals.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
