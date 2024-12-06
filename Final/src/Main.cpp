#include <iostream>
#include "RestaurantSystem.cpp"
using namespace std;

int main() {
    RestaurantSystem system;
    int choice;
    do {
        cout << "\n===== Restaurant Management System =====\n";
        cout << "1. Menu Management\n";
        cout << "2. Order Management\n";
        cout << "3. Billing System\n";
        cout << "4. Reservation Management\n";
        cout << "5. Inventory Management\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int menuChoice;
            cout << "1. Add Menu Item\n2. View Menu\n3. Delete Menu Item\n4. Update Menu Item\nEnter your choice: ";
            cin >> menuChoice;
            switch (menuChoice) {
            case 1: system.addMenuItem(); break;
            case 2: system.viewMenu(); break;
            case 3: system.deleteMenuItem(); break;
            case 4: system.updateMenuItem(); break;
            default: cout << "Invalid choice.\n";
            }
            break;
        }
        case 2: {
            int orderChoice;
            cout << "1. Place Order\n2. View Orders\n3. Delete Order\nEnter your choice: ";
            cin >> orderChoice;
            switch (orderChoice) {
            case 1: system.placeOrder(); break;
            case 2: system.viewOrders(); break;
            case 3: system.deleteOrder(); break;
            default: cout << "Invalid choice.\n";
            }
            break;
        }
        case 3: system.generateBill(); break;
        case 4: {
            int resChoice;
            cout << "1. Add Reservation\n2. View Reservations\nEnter your choice: ";
            cin >> resChoice;
            switch (resChoice) {
            case 1: system.addReservation(); break;
            case 2: system.viewReservations(); break;
            default: cout << "Invalid choice.\n";
            }
            break;
        }
        case 5: {
            int invChoice;
            cout << "1. Add Inventory Item\n2. View Inventory\n3. Update Inventory Item\nEnter your choice: ";
            cin >> invChoice;
            switch (invChoice) {
            case 1: system.addInventoryItem(); break;
            case 2: system.viewInventory(); break;
            case 3: system.updateInventoryItem(); break;
            default: cout << "Invalid choice.\n";
            }
            break;
        }
        case 0: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
