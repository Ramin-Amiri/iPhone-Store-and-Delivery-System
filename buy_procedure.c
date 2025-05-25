/* Changes I have made : I added more comments for better understanding of the code ,
    I created the buyIphone function to handle the buying process,
    There was some small issues with the code and namings I tried to fix them,
    In the main fucntion I added a loop to allow the user to continue buying or checking out( Basically a menu)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COLORS 5
#define MAX_NAME 50
#define PHONE_COUNT 3

// iPhone structure
typedef struct {
    char model[MAX_NAME]; // Stores the model name of the iPhone
    int storage; // Stores the storage capacity of the iPhone
    float price; // Stores the price of the iPhone
    char color[MAX_COLORS][20]; // Stores the available colors for the iPhone
    int colorCount; // Stores the number of available colors
} iPhone;

// Cart item structure
typedef struct {
    iPhone *product; // Pointer to the iPhone product
    char color[20]; // Selected color of the iPhone
    int quantity; // Quantity of the iPhone in the cart
    float total; // Total price for the item
} CartItem;

// Initialize store products
void initStore(iPhone store[]) {
    iPhone data[PHONE_COUNT] = {
        {"iPhone 16 Pro Max", 256, 1299.99, {"Silver", "Black", "Blue"}, 3}, // Initialize iPhone 16 Pro Max
        {"iPhone 15", 128, 899.99, {"Pink", "Green"}, 2}, // Initialize iPhone 15
        {"iPhone SE", 64, 499.99, {"Red", "White"}, 2} // Initialize iPhone SE
    };

    for (int i = 0; i < PHONE_COUNT; i++) {
        store[i] = data[i]; // Copy data to store array
    }
}

// Display all products
void showStore(iPhone store[]) {
    printf("---- iPhone Store ----\n");
    for (int i = 0; i < PHONE_COUNT; i++) {
        printf("%d. %s - %dGB - $%.2f\n", i + 1, store[i].model, store[i].storage, store[i].price); // Print iPhone model, storage, and price
        printf("   Color: ");
        for (int j = 0; j < store[i].colorCount; j++) {
            printf("%s%s", store[i].color[j], (j < store[i].colorCount - 1) ? ", " : ""); // Print available colors
        }
        printf("\n");
    }
}

// Function to view the current cart items
void viewCart(CartItem *cart, int cartSize) {
    printf("\n---- Your Cart ----\n");
    if (cartSize == 0) {
        printf("Cart is empty.\n"); // Print if cart is empty
        return;
    }

    for (int i = 0; i < cartSize; i++) {
        printf("%d. %s (%dGB) - Color: %s - Quantity: %d - Total: $%.2f\n",
               i + 1,
               cart[i].product->model,
               cart[i].product->storage,
               cart[i].color,
               cart[i].quantity,
               cart[i].total); // Print cart item details
    }
}

int main() {
    iPhone store[PHONE_COUNT];
    initStore(store); // Initialize store with products
    showStore(store); // Display store products
    int quit = 0; // Variable to control the loop
    // Dynamically allocate memory for cart
    int cartCapacity = 5;
    int cartSize = 0;
    CartItem *cart = (CartItem *)malloc(cartCapacity * sizeof(CartItem)); // Allocate memory for cart

    while (quit != 1) // Loop until user decides to quit
    {
        int choice;
        printf("\nEnter 1 to buy an iPhone, 2 to view cart, 3 to view available products, 4 to Check Out or 0 to quit: ");
        scanf("%d", &choice); // Get user choice

        switch (choice) {
            case 1:
                if (cartSize >= cartCapacity) { // Check if cart is full
                    printf("Cart is full. Cannot add more items.\n"); // Print message if cart is full
                    continue; // Skip to next iteration
                }
                buyIphone(store, cart, &cartSize); // Call function to buy iPhone
                break;
            case 2:
                viewCart(cart, cartSize); // Call function to view cart
                break;
            case 3:
                showStore(store); // Call function to show available products
                break;
            case 4:
                if (cartSize == 0) { // Check if cart is empty
                    printf("Your cart is empty. Please add items before checking out.\n"); // Print message if cart is empty
                } else {
                    checkout(cart, cartSize); // Call function to checkout
                    quit = 1; // Set quit flag to exit loop after checkout
                }
                break;
            case 0:
                quit = 1; // Set quit flag to exit loop
                break;
            default:
                printf("Invalid choice. Please try again.\n"); // Handle invalid input
        }
    }
    
    //buyIphone(store, cart, &cartSize); // Buy iPhone and add to cart
    //viewCart(cart, cartSize); // Display cart
    //checkout(cart, cartSize); // Checkout

    free(cart); // Free allocated memory

    return 0;
}

// Function: checkout, delivery, and memory cleanup
// ------------------------------------------------
void checkout(CartItem cart[], int cartSize) {
    char name[50];
    char address[100];
    float total = 0.0;

    getchar(); // Clear input buffer

    printf("\nEnter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline character from name

    printf("Enter your address: ");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\\n")] = 0; // Remove newline character from address

    printf("\n----- Final Order Summary -----\n");
    for (int i = 0; i < cartSize; i++) {
        printf("Model: %s | Storage: %dGB | Color: %s | Quantity: %d | Price: $%.2f\n",
               cart[i].product->model,
               cart[i].product->storage,
               cart[i].color,
               cart[i].quantity,
               cart[i].total); // Print order summary
        total += cart[i].total; // Calculate total price
    }

    printf("Total Amount: $%.2f\n", total); // Print total amount
    printf("\nThank you, %s!\nYour order will be delivered to:\n%s\n", name, address); // Print thank you message
    printf("We appreciate your purchase!\n");

    for (int i = 0; i < cartSize; i++) {
        free(cart[i].product); // Free memory for each product in the cart
    }
}

void buyIphone(iPhone *store, CartItem *cart, int *cartSize) {
    int choice, quantity;
    char color[20];

    printf("\nEnter the number of the iPhone you want to buy: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > PHONE_COUNT) {
        printf("Invalid choice. Please try again.\n");
        return; // Exit if choice is invalid
    }
    printf("Enter the quantity: ");
    scanf("%d", &quantity);
    if (quantity <= 0) {
        printf("Invalid quantity. Please try again.\n");
        return; // Exit if quantity is invalid
    }
    printf("Available colors: ");
    for (int i = 0; i < store[choice - 1].colorCount; i++) {
        printf("%s%s", store[choice - 1].color[i], (i < store[choice - 1].colorCount - 1) ? ", " : ""); // Print available colors
    }
    printf("\nSelect a color: ");
    scanf("%s", color);
    // Check if selected color is valid
    int validColor = 0; //basically a flag to check if the color is valid
    // Loop through available colors to validate the selected color
    for (int i = 0; i < store[choice - 1].colorCount; i++) {
        if (strcmp(store[choice - 1].color[i], color) == 0)// Compare selected color with available colors
        {
            validColor = 1;
            break;
        }
    }   
    if (!validColor) {
        printf("Invalid color selected. Please try again.\n");
        return; // Exit if color is invalid
    }

    // Add item to cart
    cart[*cartSize].product = &store[choice - 1]; // Point to the selected product
    strcpy(cart[*cartSize].color, color); // Copy selected color
    cart[*cartSize].quantity = quantity; // Set quantity
    cart[*cartSize].total = store[choice - 1].price * quantity; // Calculate total price

    (*cartSize)++; // Increment cart size

    printf("Added %d x %s (%s) to your cart. Total: $%.2f\n",
           quantity, store[choice - 1].model, color, cart[*cartSize - 1].total); // Print confirmation message
}