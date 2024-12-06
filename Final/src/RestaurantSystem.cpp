#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

#include "MenuItem.cpp"
#include "Order.cpp"
#include "Reservation.cpp"
#include "InventoryItem.cpp"
#include "Customer.cpp"

class RestaurantSystem {
private:
    vector<MenuItem> menu;
    vector<Order> orders;
    vector<Reservation> reservations;
    vector<InventoryItem> inventory;
    vector<Customer> customers;
    int orderIDCounter = 1;
    int customerIDCounter = 1;

    vector<MenuItem>::iterator findMenuItemById(int id) {
        return find_if(menu.begin(), menu.end(),
            [id](const MenuItem& item) { return item.id == id; });
    }


    vector<Order>::iterator findOrderById(int orderID) {
        return find_if(orders.begin(), orders.end(),
            [orderID](const Order& order) { return order.orderID == orderID; });
    }

    vector<InventoryItem>::iterator findInventoryItemByName(const string& name) {
        return find_if(inventory.begin(), inventory.end(),
            [&name](const InventoryItem& item) { return item.name == name; });
    }

public:
    void addCustomer() {
        string name, phone;
        cout << "Enter Customer Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Customer Phone Number: ";
        getline(cin, phone);

        customers.push_back(Customer(customerIDCounter++, name, phone));
        cout << "Customer Added Successfully! Customer ID: " << customerIDCounter - 1 << endl;
    }

    void viewCustomers() {
        cout << "\n===== Customers =====\n";
        if (customers.empty()) {
            cout << "No customers found.\n";
            return;
        }
        for (const auto& customer : customers) {
            cout << "ID: " << customer.id
                << ", Name: " << customer.name
                << ", Phone: " << customer.phone << endl;
        }
    }
    void addMenuItem() {
        int id;
        string name;
        double price;

        while (true) {
            cout << "Enter Menu Item ID: ";
            cin >> id;
            if (findMenuItemById(id) == menu.end()) break;
            cout << "ID already exists. Please choose a unique ID.\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Menu Item Name: ";
        getline(cin, name);
        cout << "Enter Menu Item Price: ";
        cin >> price;

        menu.push_back(MenuItem(id, name, price));
        cout << "Menu Item Added Successfully!\n";
    }

    void viewMenu() {
        cout << "\n===== Menu =====\n";
        if (menu.empty()) {
            cout << "No menu items available.\n";
            return;
        }
        cout << fixed << setprecision(2);

        for (const auto& item : menu) {
            cout << "ID: " << item.id
                << ", Name: " << item.name
                << ", Price: $" << item.price << endl;
        }
    }

    void deleteMenuItem() {
        if (menu.empty()) {
            cout << "Menu is empty. Nothing to delete.\n";
            return;
        }

        int id;
        cout << "Enter Menu Item ID to Delete: ";
        cin >> id;

        auto it = findMenuItemById(id);
        if (it != menu.end()) {
            menu.erase(it);
            cout << "Menu Item Deleted Successfully!\n";
        } else {
            cout << "Menu Item Not Found.\n";
        }
    }

    void updateMenuItem() {
        if (menu.empty()) {
            cout << "Menu is empty. Nothing to update.\n";
            return;
        }

        int id;
        cout << "Enter Menu Item ID to Update: ";
        cin >> id;

        auto it = findMenuItemById(id);
        if (it != menu.end()) {
            string newName;
            double newPrice;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter New Name (current: " << it->name << "): ";
            getline(cin, newName);

            cout << "Enter New Price (current: $" << it->price << "): ";
            cin >> newPrice;

            if (!newName.empty()) it->name = newName;
            if (newPrice > 0) it->price = newPrice;

            cout << "Menu Item Updated Successfully!\n";
        } else {
            cout << "Menu Item Not Found.\n";
        }
    }
    void placeOrder() {
        if (menu.empty()) {
            cout << "Menu is empty. Cannot place order.\n";
            return;
        }

        string customerName;
        cout << "Enter Customer Name: ";
        cin.ignore();
        getline(cin, customerName);

        Order newOrder(orderIDCounter++, customerName);

        while (true) {
            viewMenu();
            int itemID, quantity;

            cout << "\nEnter Menu Item ID to Add (or 0 to Finish Order): ";
            cin >> itemID;

            if (itemID == 0) break;

            auto menuItem = find_if(menu.begin(), menu.end(),
                [itemID](const MenuItem& item) { return item.id == itemID; });

            if (menuItem != menu.end()) {
                cout << "Enter Quantity: ";
                cin >> quantity;

                for (int i = 0; i < quantity; ++i) {
                    newOrder.items.push_back(*menuItem);
                    newOrder.totalAmount += menuItem->price;
                }
            }
            else {
                cout << "Invalid Item ID.\n";
            }
        }

        if (!newOrder.items.empty()) {
            orders.push_back(newOrder);
            cout << "Order Placed Successfully! Order ID: "
                << newOrder.orderID
                << ", Total Amount: $" << newOrder.totalAmount << endl;
        }
        else {
            cout << "Order Canceled. No items selected.\n";
            orderIDCounter--; 
        }
    }
    void viewOrders() {
        cout << "\n===== Orders =====\n";
        if (orders.empty()) {
            cout << "No orders placed yet.\n";
            return;
        }

        cout << fixed << setprecision(2);
        for (const auto& order : orders) {
            cout << "Order ID: " << order.orderID
                << ", Customer: " << order.customerName
                << ", Total: $" << order.totalAmount << endl;

            cout << "Items:\n";
            for (const auto& item : order.items) {
                cout << " - " << item.name << " ($" << item.price << ")\n";
            }
            cout << endl;
        }
    }

    void deleteOrder() {
        if (orders.empty()) {
            cout << "No orders to delete.\n";
            return;
        }

        int orderID;
        cout << "Enter Order ID to Delete: ";
        cin >> orderID;

        auto it = findOrderById(orderID);
        if (it != orders.end()) {
            orders.erase(it);
            cout << "Order Deleted Successfully!\n";
        } else {
            cout << "Order Not Found.\n";
        }
    }
    void generateBill() {
        if (orders.empty()) {
            cout << "No orders to generate bill for.\n";
            return;
        }

        int orderID;
        cout << "Enter Order ID to Generate Bill: ";
        cin >> orderID;

        auto it = find_if(orders.begin(), orders.end(),
            [orderID](const Order& order) { return order.orderID == orderID; });

        if (it != orders.end()) {
            cout << "\n===== Bill =====\n";
            cout << "Order ID: " << it->orderID
                << ", Customer: " << it->customerName << endl;

            cout << "Items:\n";
            for (const auto& item : it->items) {
                cout << " - " << item.name << " ($" << item.price << ")\n";
            }

            cout << "\nTotal Amount: $" << it->totalAmount << endl;
            double payment;
            cout << "Enter Payment Amount: ";
            cin >> payment;

            if (payment >= it->totalAmount) {
                double change = payment - it->totalAmount;
                cout << "Payment Successful. Change: $" << change << endl;
            }
            else {
                cout << "Insufficient Payment.\n";
            }
        }
        else {
            cout << "Order Not Found.\n";
        }
    }
    void addReservation() {
        int tableID;
        string customerName, time;

        cout << "Enter Table ID: ";
        cin >> tableID;
        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, customerName);

        cout << "Enter Reservation Time (HH:MM): ";
        getline(cin, time);
        auto conflict = find_if(reservations.begin(), reservations.end(),
            [tableID, time](const Reservation& res) {
                return res.tableID == tableID && res.time == time;
            });

        if (conflict != reservations.end()) {
            cout << "Table " << tableID << " is already reserved at " << time << endl;
            return;
        }

        reservations.push_back(Reservation(tableID, customerName, time));
        cout << "Reservation Added Successfully!\n";
    }

    void viewReservations() {
        cout << "\n===== Reservations =====\n";
        if (reservations.empty()) {
            cout << "No reservations made yet.\n";
            return;
        }

        for (const auto& res : reservations) {
            cout << "Table: " << res.tableID
                << ", Customer: " << res.customerName
                << ", Time: " << res.time << endl;
        }
    }
    void addInventoryItem() {
        string name;
        int quantity;
        
        cout << "Enter Item Name: ";
        cin.ignore();
        getline(cin, name);
        
        do {
            cout << "Enter Quantity: ";
            if (!(cin >> quantity) || quantity < 0) {
                cout << "Invalid input. Please enter a positive number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            break;
        } while (true);
        
        auto it = find_if(inventory.begin(), inventory.end(),
            [&name](const InventoryItem& item) { return item.name == name; });
        
        if (it != inventory.end()) {
            it->quantity += quantity;
            cout << "Updated existing inventory item. New quantity: " << it->quantity << "\n";
        } else {
            inventory.push_back(InventoryItem(name, quantity));
            cout << "New Inventory Item Added Successfully!\n";
        }
    }

    void viewInventory() {
        cout << "\n===== Inventory =====\n";
        if (inventory.empty()) {
            cout << "No inventory items available.\n";
            return;
        }

        for (const auto& item : inventory) {
            cout << "Item: " << item.name
                << ", Quantity: " << item.quantity << endl;
        }
    }

    void updateInventoryItem() {
        if (inventory.empty()) {
            cout << "Inventory is empty. Nothing to update.\n";
            return;
        }

        string name;
        cout << "Enter Item Name to Update: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);

        auto it = findInventoryItemByName(name);
        if (it != inventory.end()) {
            cout << "Current quantity: " << it->quantity << endl;
            cout << "1. Add to quantity\n";
            cout << "2. Subtract from quantity\n";
            cout << "3. Set new quantity\n";
            cout << "Choose operation (1-3): ";

            int choice, quantity;
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter quantity to add: ";
                    cin >> quantity;
                    if (quantity > 0) {
                        it->quantity += quantity;
                        cout << "Updated quantity: " << it->quantity << endl;
                    }
                    break;
                case 2:
                    cout << "Enter quantity to subtract: ";
                    cin >> quantity;
                    if (quantity > 0 && it->quantity >= quantity) {
                        it->quantity -= quantity;
                        cout << "Updated quantity: " << it->quantity << endl;
                    } else {
                        cout << "Error: Cannot subtract more than available quantity.\n";
                    }
                    break;
                case 3:
                    cout << "Enter new quantity: ";
                    cin >> quantity;
                    if (quantity >= 0) {
                        it->quantity = quantity;
                        cout << "Updated quantity: " << it->quantity << endl;
                    }
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } else {
            cout << "Item not found in inventory.\n";
        }
    }
};