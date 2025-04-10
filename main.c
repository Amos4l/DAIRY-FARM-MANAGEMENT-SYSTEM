#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 20
#define MAX_COWS 100
#define MAX_ORDERS 50
#define MAX_OTHER 50

// Structure for cow production
typedef struct {
    char name[MAX_NAME];
    float am;
    float pm;
    float total;
} Cow;

// Structure for orders
typedef struct {
    char description[MAX_NAME];
    int quantity;
} Order;

// Structure for other data (dairy, shop, home)
typedef struct {
    char category[MAX_NAME];
    int quantity;
} Other;

// Function prototypes
void addCow();
void viewCows();
void addOrder();
void viewOrders();
void addOther();
void viewOther();
void saveCows(Cow cows[], int count);
void loadCows(Cow cows[], int *count);
void saveOrders(Order orders[], int count);
void loadOrders(Order orders[], int *count);
void saveOther(Other others[], int count);
void loadOther(Other others[], int *count);

int main() {
    int choice;
    do {
        printf("\nDairy Farm Production System\n");
        printf("1. Add Cow Production\n");
        printf("2. View Cow Production\n");
        printf("3. Add Order\n");
        printf("4. View Orders\n");
        printf("5. Add Other Data (Dairy/Shop/Home)\n");
        printf("6. View Other Data\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCow();
                break;
            case 2:
                viewCows();
                break;
            case 3:
                addOrder();
                break;
            case 4:
                viewOrders();
                break;
            case 5:
                addOther();
                break;
            case 6:
                viewOther();
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 7);

    return 0;
}

// Function to add a cow's production data
void addCow() {
    Cow cows[MAX_COWS];
    int count = 0;
    loadCows(cows, &count);

    if (count >= MAX_COWS) {
        printf("Cannot add more cows. Storage full!\n");
        return;
    }

    Cow newCow;
    printf("Enter cow name: ");
    scanf("%s", newCow.name);
    printf("Enter AM production (liters): ");
    scanf("%f", &newCow.am);
    printf("Enter PM production (liters): ");
    scanf("%f", &newCow.pm);
    newCow.total = newCow.am + newCow.pm;

    cows[count] = newCow;
    count++;
    saveCows(cows, count);
    printf("Cow added successfully!\n");
}

// Function to view all cows' production data
void viewCows() {
    Cow cows[MAX_COWS];
    int count = 0;
    loadCows(cows, &count);

    if (count == 0) {
        printf("No cows found.\n");
        return;
    }

    printf("\nCow Production Data:\n");
    printf("Name\tAM\tPM\tTotal\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t%.1f\t%.1f\t%.1f\n", cows[i].name, cows[i].am, cows[i].pm, cows[i].total);
    }
}

// Function to add an order
void addOrder() {
    Order orders[MAX_ORDERS];
    int count = 0;
    loadOrders(orders, &count);

    if (count >= MAX_ORDERS) {
        printf("Cannot add more orders. Storage full!\n");
        return;
    }

    Order newOrder;
    printf("Enter order description (A.M MILK): ");
    scanf("%s", newOrder.description);
    printf("Enter quantity: ");
    scanf("%d", &newOrder.quantity);

    orders[count] = newOrder;
    count++;
    saveOrders(orders, count);
    printf("Order added successfully!\n");
}

// Function to view all orders
void viewOrders() {
    Order orders[MAX_ORDERS];
    int count = 0;
    loadOrders(orders, &count);

    if (count == 0) {
        printf("No orders found.\n");
        return;
    }

    printf("\nOrders:\n");
    printf("Description\tQuantity\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t\t%d\n", orders[i].description, orders[i].quantity);
    }
}

// Function to add other data (dairy, shop, home)
void addOther() {
    Other others[MAX_OTHER];
    int count = 0;
    loadOther(others, &count);

    if (count >= MAX_OTHER) {
        printf("Cannot add more data. Storage full!\n");
        return;
    }

    Other newOther;
    printf("Enter category (Dairy/Shop/Home): ");
    scanf("%s", newOther.category);
    printf("Enter quantity: ");
    scanf("%d", &newOther.quantity);

    others[count] = newOther;
    count++;
    saveOther(others, count);
    printf("Data added successfully!\n");
}

// Function to view other data
void viewOther() {
    Other others[MAX_OTHER];
    int count = 0;
    loadOther(others, &count);

    if (count == 0) {
        printf("No data found.\n");
        return;
    }

    printf("\nOther Data:\n");
    printf("Category\tQuantity\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t\t%d\n", others[i].category, others[i].quantity);
    }
}

// Function to save cows to file
void saveCows(Cow cows[], int count) {
    FILE *file = fopen("cows.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %.1f %.1f %.1f\n", cows[i].name, cows[i].am, cows[i].pm, cows[i].total);
    }
    fclose(file);
}

// Function to load cows from file
void loadCows(Cow cows[], int *count) {
    FILE *file = fopen("cows.txt", "r");
    if (file == NULL) {
        *count = 0;
        return;
    }

    *count = 0;
    while (*count < MAX_COWS && fscanf(file, "%s %f %f %f", cows[*count].name, &cows[*count].am, &cows[*count].pm, &cows[*count].total) == 4) {
        (*count)++;
    }
    fclose(file);
}

// Function to save orders to file
void saveOrders(Order orders[], int count) {
    FILE *file = fopen("orders.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", orders[i].description, orders[i].quantity);
    }
    fclose(file);
}

// Function to load orders from file
void loadOrders(Order orders[], int *count) {
    FILE *file = fopen("orders.txt", "r");
    if (file == NULL) {
        *count = 0;
        return;
    }

    *count = 0;
    while (*count < MAX_ORDERS && fscanf(file, "%s %d", orders[*count].description, &orders[*count].quantity) == 2) {
        (*count)++;
    }
    fclose(file);
}

// Function to save other data to file
void saveOther(Other others[], int count) {
    FILE *file = fopen("other.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", others[i].category, others[i].quantity);
    }
    fclose(file);
}

// Function to load other data from file
void loadOther(Other others[], int *count) {
    FILE *file = fopen("other.txt", "r");
    if (file == NULL) {
        *count = 0;
        return;
    }

    *count = 0;
    while (*count < MAX_OTHER && fscanf(file, "%s %d", others[*count].category, &others[*count].quantity) == 2) {
        (*count)++;
    }
    fclose(file);
}