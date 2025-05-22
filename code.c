#include <stdio.h>
#include <string.h>

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

int main() {
    iPhone store[PHONE_COUNT];
    initStore(store);
    showStore(store);
    return 0;
}
