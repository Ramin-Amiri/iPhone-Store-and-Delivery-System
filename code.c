#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COLORS 5
#define MAX_NAME 50
#define PHONE_COUNT 3

// Converts a string to lowercase for case-insensitive comparison
void toLower(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
}

// Structure to represent an iPhone
typedef struct {
    char model[MAX_NAME];     // Model name
    int storage;              // Storage capacity in GB
    float price;              // Price in USD
    char colors[MAX_COLORS][20]; // Available color options
    int colorCount;           // Number of colors available
} iPhone;

// Structure to represent an item in the cart
typedef struct {
    iPhone *product;          // Pointer to the iPhone selected
    char color[20];           // Chosen color
    int quantity;             // Number of units
    float total;              // Total price
} CartItem;

// Initialize store with pre-defined iPhones
void initStore(iPhone store[]) {
    iPhone data[PHONE_COUNT] = {
        {"iPhone 16 Pro Max", 256, 1299.99, {"Silver", "Black", "Blue"}, 3},
        {"iPhone 15", 128, 899.99, {"Pink", "Green"}, 2},
        {"iPhone SE", 64, 499.99, {"Red", "White"}, 2}
    };
    for (int i = 0; i < PHONE_COUNT; i++) {
        store[i] = data[i];
    }
}

// Display all available iPhones
void showStore(iPhone store[]) {
    printf("---- iPhone Store ----\n");
    for (int i = 0; i < PHONE_COUNT; i++) {
        printf("%d. %s - %dGB - $%.2f\n", i + 1, store[i].model, store[i].storage, store[i].price);
        printf("   Colors: ");
        for (int j = 0; j < store[i].colorCount; j++) {
            printf("%s%s", store[i].colors[j], (j < store[i].colorCount - 1) ? ", " : "");
        }
        printf("\n");
    }
}

// Display all items currently in the cart
void viewCart(CartItem *cart, int cartSize) {
    printf("\n---- Your Cart ----\n");
    if (cartSize == 0) {
        printf("Cart is empty.\n");
        return;
    }
    for (int i = 0; i < cartSize; i++) {
        printf("%d. %s (%dGB) - Color: %s - Quantity: %d - Total: $%.2f\n",
               i + 1,
               cart[i].product->model,
               cart[i].product->storage,
               cart[i].color,
               cart[i].quantity,
               cart[i].total);
    }
}

// Display main menu
void printMenu() {
    printf("\n===== iPhone Store Menu =====\n");
    printf("1. View Available iPhones\n");
    printf("2. Buy an iPhone\n");
    printf("3. View Cart\n");
    printf("4. Checkout\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
}

// Buy iPhone: asks user for model, quantity, and color, then adds to cart
void buyIphone(iPhone *store, CartItem *cart, int *cartSize) {
    int choice, quantity;
    char color[20];
    char userColor[20];

    printf("---- Available iPhones ----\n");
    showStore(store); // Show all phones before input

    printf("\nEnter the number of the iPhone you want to buy: ");
    scanf("%d", &choice);
    while (getchar() != '\n');

    if (choice < 1 || choice > PHONE_COUNT) {
        printf("Invalid choice. Please try again.\n");
        return;
    }

    printf("Enter the quantity: ");
    scanf("%d", &quantity);
    while (getchar() != '\n');
    if (quantity <= 0) {
        printf("Invalid quantity. Please try again.\n");
        return;
    }

    printf("Available colors: ");
    for (int i = 0; i < store[choice - 1].colorCount; i++) {
        printf("%s%s", store[choice - 1].colors[i], (i < store[choice - 1].colorCount - 1) ? ", " : "");
    }

    printf("\nSelect a color: ");
    scanf("%s", color);
    while (getchar() != '\n');

    strcpy(userColor, color);
    toLower(userColor); // Compare using lowercase

    int validColor = 0;
    for (int i = 0; i < store[choice - 1].colorCount; i++) {
        char storeColor[20];
        strcpy(storeColor, store[choice - 1].colors[i]);
        toLower(storeColor);
        if (strcmp(userColor, storeColor) == 0) {
            validColor = 1;
            break;
        }
    }

    if (!validColor) {
        printf("Invalid color selected. Please try again.\n");
        return;
    }

    cart[*cartSize].product = &store[choice - 1];
    strcpy(cart[*cartSize].color, color);
    cart[*cartSize].quantity = quantity;
    cart[*cartSize].total = store[choice - 1].price * quantity;
    (*cartSize)++;

    printf("Added %d x %s (%s) to your cart. Total: $%.2f\n",
           quantity, store[choice - 1].model, color, cart[*cartSize - 1].total);
}

// Checkout: collects customer info and displays receipt
void checkout(CartItem cart[], int cartSize) {
    char name[50];
    char address[100];
    float total = 0.0;

    printf("\nEnter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter your address: ");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = 0;

    system("cls");
    printf("\n----- Final Order Summary -----\n");
    for (int i = 0; i < cartSize; i++) {
        printf("Model: %s | Storage: %dGB | Color: %s | Quantity: %d | Price: $%.2f\n",
               cart[i].product->model,
               cart[i].product->storage,
               cart[i].color,
               cart[i].quantity,
               cart[i].total);
        total += cart[i].total;
    }

    printf("Total Amount: %.2f\n", total);
    printf("\nThank you, %s!\nYour order will be delivered to:\n%s\n", name, address);
    printf("We appreciate your purchase!\n");
}

// Main program: handles menu navigation and cart allocation
int main() {
    iPhone store[PHONE_COUNT];
    initStore(store); // Load store data

    int cartCapacity = 5;
    int cartSize = 0;
    CartItem *cart = (CartItem *)malloc(cartCapacity * sizeof(CartItem));

    int choice;
    while (1) {
        system("cls");
        printMenu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                system("cls");
                showStore(store);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 2:
                if (cartSize >= cartCapacity) {
                    cartCapacity *= 2;
                    cart = realloc(cart, cartCapacity * sizeof(CartItem));
                    if (!cart) {
                        printf("Memory allocation failed!\n");
                        return 1;
                    }
                }
                // Do NOT clear screen here so phones stay visible
                buyIphone(store, cart, &cartSize);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 3:
                system("cls");
                viewCart(cart, cartSize);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 4:
                if (cartSize == 0) {
                    printf("Your cart is empty. Please add items before checking out.\n");
                    printf("\nPress Enter to continue...");
                    getchar();
                } else {
                    checkout(cart, cartSize);
                    free(cart);
                    return 0;
                }
                break;
            case 5:
                printf("Thank you! Exiting...\n");
                free(cart);
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
                printf("\nPress Enter to continue...");
                getchar();
        }
    }

    return 0;
}
