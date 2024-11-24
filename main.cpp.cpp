#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_VEHICLES 30
#define MAX_CUSTOMERS 80

// Vehicle structure
struct Vehicle{
    int id;
    char make[20];
    char model[20];
    float price_per_day;
    int status;  // 0 - available, 1 - booked, 2 - under maintenance
};

// Customer structure
struct Customer{
    int id;
    char name[30];
    char phone[15];
};

// Vehicle and Customer arrays
Vehicle vehicles[MAX_VEHICLES];
Customer customers[MAX_CUSTOMERS];
int vehicle_count = 0;
int customer_count = 0;

// Function prototypes (Function declearation)
void add_vehicle();
void display_vehicles();
void update_vehicle_status();
void add_customer();
void display_customers();
void book_vehicle();
void save_customers_to_file();
void load_customers_from_file();
void delete_customer();
void delete_vehicle();
void addition_sound();
void deletion_sound();


int main() {
    int choice;
    load_customers_from_file(); // Load customer data on startup

    while (1) {
        printf("\n      --- RENT A CAR ---\n\n");
        printf("1. Add Vehicle\n");
        printf("2. Display Vehicles\n");
        printf("3. Update Vehicle Status\n");
        printf("4. Delete Vehicle\n");
        printf("5. Add Customer\n");
        printf("6. Display Customers\n");
        printf("7. Delete Customer\n");
        printf("8. Book Vehicle\n");
        printf("9. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_vehicle(); break;
            case 2: display_vehicles(); break;
            case 3: update_vehicle_status(); break;
            case 4: delete_vehicle(); break;
            case 5: add_customer(); break;
            case 6: display_customers(); break;
            case 7: delete_customer(); break;
            case 8: book_vehicle(); break;
            case 9: save_customers_to_file(); exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Add new vehicle
void add_vehicle() {
    if (vehicle_count >= MAX_VEHICLES) {
        printf("Vehicle database is full.\n");
        return;
    }
    vehicles[vehicle_count].id = vehicle_count + 1;
    printf("Enter make: ");
    scanf(" %[^\n]", vehicles[vehicle_count].make);  // Reads a full line (allows spaces)

    printf("Enter model: ");
    scanf(" %[^\n]", vehicles[vehicle_count].model); // Reads a full line (allows spaces)

    printf("Enter price per day: ");
    scanf("%f", &vehicles[vehicle_count].price_per_day);
    
    vehicles[vehicle_count].status = 0; // Set vehicle to available by default
    vehicle_count++;
    printf("Vehicle added successfully.\n");
    addition_sound(); // Play sound for addition

}

// Delete Vehicle
void delete_vehicle() {
    int id, found = 0;
    printf("Enter vehicle ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < vehicle_count; i++) {
        if (vehicles[i].id == id) {
            found = 1;
            for (int j = i; j < vehicle_count - 1; j++) {
                vehicles[j] = vehicles[j + 1]; // Shift remaining entries
            }
            vehicle_count--;
            // Update IDs for all remaining vehicles
            for (int k = 0; k < vehicle_count; k++) {
                vehicles[k].id = k + 1;
            }
            printf("Vehicle with ID %d deleted successfully.\n", id);
			deletion_sound(); // Play sound for deletion

            break;
        }
    }

    if (!found) {
        printf("Vehicle with ID %d not found.\n", id);
    }
}


// Display all vehicles
void display_vehicles() {
    printf("\n%-5s %-20s %-20s %-15s %-10s\n", "ID", "Make", "Model", "Price/Day", "Status");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < vehicle_count; i++) {
        printf("%-5d %-20s %-20s %-15.2f %-10s\n", 
               vehicles[i].id, 
               vehicles[i].make, 
               vehicles[i].model, 
               vehicles[i].price_per_day, 
               vehicles[i].status == 0 ? "Available" : 
               (vehicles[i].status == 1 ? "Booked" : "Maintenance"));
    }
}

// Update vehicle status
void update_vehicle_status() {
    int id, status;
    printf("Enter vehicle ID to update: ");
    scanf("%d", &id);
    if (id <= 0 || id > vehicle_count) {
        printf("Invalid vehicle ID.\n");
        return;
    }
    printf("Enter new status (0 - Available, 1 - Booked): ");
    scanf("%d", &status);
    if (status < 0 || status > 1) {
        printf("Invalid status.\n");
        return;
    }
    vehicles[id - 1].status = status;
    printf("Vehicle status updated successfully.\n");
    addition_sound(); // Play sound for addition

}

// Add new customer
void add_customer() {
    if (customer_count >= MAX_CUSTOMERS) {
        printf("Customer database is full.\n");
        return;
    }
    customers[customer_count].id = customer_count + 1;
    printf("Enter name: ");
    scanf(" %[^\n]", customers[customer_count].name);
    printf("Enter phone: ");
    scanf(" %[^\n]", customers[customer_count].phone);
    customer_count++;
    printf("Customer added successfully.\n");
    addition_sound(); // Play sound for addition

}

// Display all customers
void display_customers() {
    printf("\n%-5s %-30s %-15s\n", "ID", "Name", "Phone");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < customer_count; i++) {
        printf("%-5d %-30s %-15s\n", 
               customers[i].id, 
               customers[i].name, 
               customers[i].phone);
    }
}

// Delete Customer
void delete_customer() {
    int id, found = 0;
    printf("Enter customer ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < customer_count; i++) {
        if (customers[i].id == id) {
            found = 1;
            for (int j = i; j < customer_count - 1; j++) {
                customers[j] = customers[j + 1]; // Shift remaining entries
            }
            customer_count--;
            // Update IDs for all remaining customers
            for (int k = 0; k < customer_count; k++) {
                customers[k].id = k + 1;
            }
            printf("Customer with ID %d deleted successfully.\n", id);
            deletion_sound(); // Play sound for deletion
            break;
        }
    }

    if (!found) {
        printf("Customer with ID %d not found.\n", id);
    }
}


// Book a vehicle
void book_vehicle() {
    int vehicle_id, customer_id;
    printf("Enter vehicle ID to book: ");
    scanf("%d", &vehicle_id);
    if (vehicle_id <= 0 || vehicle_id > vehicle_count || vehicles[vehicle_id - 1].status != 0) {
        printf("Vehicle is not available for booking.\n");
        return;
    }
    printf("Enter customer ID: ");
    scanf("%d", &customer_id);
    if (customer_id <= 0 || customer_id > customer_count) {
        printf("Invalid customer ID.\n");
        return;
    }
    vehicles[vehicle_id - 1].status = 1; // Mark vehicle as booked
    printf("Vehicle booked successfully for customer %d.\n", customer_id);
}

// Save customer data to file
void save_customers_to_file() {
    FILE *file = fopen("customers.txt", "w");
    if (file == NULL) {
        printf("Error saving customers.\n");
        return;
    }
    for (int i = 0; i < customer_count; i++) {
        fprintf(file, "%d %s %s\n", customers[i].id, customers[i].name, customers[i].phone);
    }
    fclose(file);
}

// Load customer data from file
void load_customers_from_file() {
    FILE *file = fopen("customers.txt", "r");
    if (file == NULL) {
        printf("No existing customer data found.\n");
        return;
    }
    while (fscanf(file, "%d %s %s", &customers[customer_count].id,
                  customers[customer_count].name,
                  customers[customer_count].phone) != EOF) {
        customer_count++;
    }
    fclose(file);
}

void addition_sound() {
	Beep(1000, 300); // High-pitched beep for addition

}

void deletion_sound() {
    Beep(500, 300); // Low-pitched beep for deletion
}


