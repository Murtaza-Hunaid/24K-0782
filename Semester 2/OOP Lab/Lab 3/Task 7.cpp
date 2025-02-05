#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class StationaryShop {
private:
    string items[100]; 
    float prices[100]; 
    int item_count;    

public:
    StationaryShop() : item_count(0) {}

    void addItem(const string& item, float price) {
        if (item_count >= 100) {
            cout << "Item list is full. Cannot add more items.\n";
            return; }
        items[item_count] = item;
        prices[item_count] = price;
        item_count++;
        cout << "Item added: " << item << " with price Rs." << fixed << setprecision(2) << price << "\n";
    }

    void fetchItems() const {
        if (item_count == 0) {
            cout << "No items available.\n";
            return; }
        cout << "Items available:\n";
        for (int i = 0; i < item_count; i++) {
            cout << i + 1 << ". " << items[i] << "\n"; }
    }

    void editPrice(int index, float new_price) {
        if (index < 1 || index > item_count) {
            cout << "Invalid item index.\n";
            return;
        }
        prices[index - 1] = new_price;
        cout << "Price updated for " << items[index - 1] << " to Rs." << fixed << setprecision(2) << new_price << "\n";
    }

    void viewItems() const {
        if (item_count == 0) {
            cout << "No items available.\n";
            return;
        }
        cout << left << setw(20) << "Item" << right << setw(10) << "Price\n";
        cout << string(30, '-') << "\n";
        for (int i = 0; i < item_count; i++) {
            cout << left << setw(20) << items[i] << right << setw(10) << fixed << setprecision(2) << prices[i] << "\n";
        }
    }

    void createReceipt() {
        if (item_count == 0) {
            cout << "No items available to create a receipt.\n";
            return; }
        string item;
        int quantity;
        float total = 0.0;
        cout << "Enter items purchased by the customer (type 'done' to finish):\n";
        while (true) {
            cout << "Enter item name: ";
            cin >> item;
            if (item == "done") {
                break; }
            bool found = false;
            for (int i = 0; i < item_count; i++) {
                if (items[i] == item) {
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    total += prices[i] * quantity;
                    cout << "Added " << quantity << " x " << items[i] << " at Rs." << prices[i] << " each.\n";
                    found = true;
                    break; } }
            if (!found) {
                cout << "Item not found.\n"; } }
        cout << "\n--- Receipt ---\n";
        cout << "Total: Rs." << fixed << setprecision(2) << total << "\n";
        cout << "Thank you for your purchase!\n";
    }
};

int main() {
    StationaryShop shop;
    int choice;
    do {
        cout << "\nStationary Shop Menu:\n";
        cout << "1. Add item\n";
        cout << "2. Fetch list of items\n";
        cout << "3. Edit item price\n";
        cout << "4. View all items and prices\n";
        cout << "5. Create receipt\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            string item;
            float price;
            cout << "Enter item name: ";
            cin >> item;
            cout << "Enter price: ";
            cin >> price;
            shop.addItem(item, price); } 
		else if (choice == 2) {
            shop.fetchItems(); } 
		else if (choice == 3) {
            int index;
            float new_price;
            cout << "Enter item index to edit: ";
            cin >> index;
            cout << "Enter new price: ";
            cin >> new_price;
            shop.editPrice(index, new_price); } 
		else if (choice == 4) {
            shop.viewItems(); } 
		else if (choice == 5) {
            shop.createReceipt(); } 
		else if (choice == 6) {
            cout << "Exiting program.\n"; } 
		else {
            cout << "Invalid choice. Try again.\n"; } } 
	while (choice != 6);
    return 0;
}
