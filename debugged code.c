#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COLORS 5
#define MAX_NAME 50
#define PHONE_COUNT 3

// iPhone structure
typedef struct {
    char model[MAX_NAME];
    int storage;
    float price;
    char colors[MAX_COLORS][20];
    int colorCount;
} iPhone;

// Cart item structure
typedef struct {
    iPhone *product;
    char color[20];
    int quantity;
    float total;
} CartItem;

// --- Function Declarations ---
void initStore(iPhone store[]);
void showStore(iPhone store[]);
void viewCart(CartItem *cart, int cartSize);
void buyiPhone(iPhone store[], CartItem **cart, int *cartSize, int *cartCapacity);
void checkout(CartItem cart[], int cartSize);
void printMenu();


// Initialize store products
void initStore(iPhone store[]) {
    iPhone data[PHONE_COUNT] = {
        {"iPhone 16 Pro Max", 256, 1299.99, {"Silver", "Black", "Blue"}, 3},
        {"iPhone 15",         128,  899.99, {"Pink", "Green"},           2},
        {"iPhone SE",          64,  499.99, {"Red", "White"},            2}
    };

    for (int i = 0; i < PHONE_COUNT; i++) {
        store[i] = data[i];
    }
}

// Display all products
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

// Function to view the current cart items
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

// === BEGIN: Member 3 - Buying Logic ===
void buyiPhone(iPhone store[], CartItem **cart, int *cartSize, int *cartCapacity) {
    int phoneID, colorChoice, quantity;
    showStore(store);

    printf("\nEnter the ID of the iPhone to buy (1-%d): ", PHONE_COUNT);
    scanf("%d", &phoneID);
    getchar();

    if (phoneID < 1 || phoneID > PHONE_COUNT) {
        printf("Invalid ID. Try again.\n");
        return;
    }

    iPhone *selected = &store[phoneID - 1];

    printf("Available colors:\n");
    for (int i = 0; i < selected->colorCount; i++) {
        printf("%d. %s\n", i + 1, selected->colors[i]);
    }
    printf("Choose a color: ");
    scanf("%d", &colorChoice);
    getchar();

    if (colorChoice < 1 || colorChoice > selected->colorCount) {
        printf("Invalid color choice.\n");
        return;
    }

    printf("How many would you like to buy? ");
    scanf("%d", &quantity);
    getchar();

    if (quantity < 1) {
        printf("Invalid quantity.\n");
        return;
    }

    if (*cartSize >= *cartCapacity) {
        *cartCapacity *= 2;
        *cart = realloc(*cart, *cartCapacity * sizeof(CartItem));
    }

    CartItem *newItem = &(*cart)[*cartSize];
    newItem->product = selected;
    strcpy(newItem->color, selected->colors[colorChoice - 1]);
    newItem->quantity = quantity;
    newItem->total = selected->price * quantity;
    (*cartSize)++;

    printf("Added to cart: %s (%s) x%d\n", selected->model, newItem->color, quantity);
}

// === END: Member 3 ===

// Main menu function
void printMenu() {
    printf("\n===== iPhone Store Menu =====\n");
    printf("1. View Available iPhones\n");
    printf("2. Buy an iPhone\n");
    printf("3. View Cart\n");
    printf("4. Checkout\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
}

int main() {
    iPhone store[PHONE_COUNT];
    initStore(store);

    int cartCapacity = 5;
    int cartSize = 0;
    CartItem *cart = (CartItem *)malloc(cartCapacity * sizeof(CartItem));

    int choice;
    while (1) {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (choice) {
            case 1:
                showStore(store);
                break;
            case 2:
                buyiPhone(store, &cart, &cartSize, &cartCapacity);
                break;
            case 3:
                viewCart(cart, cartSize);
                break;
            case 4:
                checkout(cart, cartSize);
                return 0;
            case 5:
                printf("Thank you! Exiting...\n");
                free(cart);
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// Function: checkout, delivery, and memory cleanup
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
    
    // ... rest of function


    printf("\n----- Final Order Summary -----\n");
    for (int i = 0; i < cartSize; i++) {
        printf("Model: %s | Storage: %dGB | Color: %s | Quantity: %d | Price: %.2f\n",
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

