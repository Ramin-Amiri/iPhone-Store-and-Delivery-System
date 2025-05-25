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

//Function to view the current cart items
void viewCart(CartItem *cart, int cartSize) {
    printf("\n---- Your Cart ----\n");
    if (cartSize == 0) {
        printf("Cart is empty.\n");
        return;
    }

    for (int i = 0; i < cartSize; i++) {
        printf("%d. %s (%dGB) - Color: %s - Quantity: %d - Total: $%.2f\n",
               i + 1,
               cart[i].model,
               cart[i].storage,
               cart[i].color,
               cart[i].quantity,
               cart[i].total);
    }
}



int main() {
    iPhone store[PHONE_COUNT];
    initStore(store);
    showStore(store);

    // Dynamically allocate memory for cart
    int cartCapacity = 5;
    int cartSize = 0;
    CartItem *cart = (CartItem *)malloc(cartCapacity * sizeof(CartItem));
    
    viewCart(cart, cartSize);
    checkout(cart, cartSize);

    free(cart);

    
    return 0;
}

// Function: checkout, delivery, and memory cleanup
// ------------------------------------------------

void checkout(CartItem cart[], int cartSize) {
    char name[50];
    char address[100];
    float total = 0.0;

    getchar(); // clear input buffer

    printf("\nEnter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter your address: ");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = 0;

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

    for (int i = 0; i < cartSize; i++) {
        free(cart[i].product);
    }
}
