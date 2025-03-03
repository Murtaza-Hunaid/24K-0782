#include <iostream>
#include <cstring>

using namespace std;

class MenuItem {
public:
    char food_name[50];
    double price;
    
    void setItem(const char* n, double p) {
        strcpy(food_name, n);
        price = p;
    }
};

class Menu {
public:
    MenuItem items[10];
    int itemCount;
    
    Menu() { itemCount = 0; }
    
    void addItem(const char* food_name, double price) {
        if (itemCount < 10) {
            items[itemCount].setItem(food_name, price);
            itemCount++; }
    }
    
    void displayMenu() {
        cout << "Menu:" << endl;
        for (int i = 0; i < itemCount; i++) {
            cout << i + 1 << ". " << items[i].food_name << " - Rs. " << items[i].price << endl; }
    }
};

class Payment {
public:
    double amount;
    
    Payment() { amount = 0; }
    
    void setAmount(double a) {
        amount = a;
    }
    
    void displayAmount() {
        cout << "Total Payment: Rs. " << amount << endl;
    }
};

class Order {
public:
    MenuItem orderedItems[10];
    int orderCount;
    Payment payment;
    
    Order() { orderCount = 0; }
    
    void addItem(MenuItem item) {
        if (orderCount < 10) {
            orderedItems[orderCount] = item;
            orderCount++; }
    }
    
    void calculatePayment() {
        double total = 0;
        for (int i = 0; i < orderCount; i++) {
            total += orderedItems[i].price; }
        payment.setAmount(total);
    }
    
    void displayOrder() {
        cout << "Order Details:" << endl;
        for (int i = 0; i < orderCount; i++) {
            cout << orderedItems[i].food_name << " - Rs. " << orderedItems[i].price << endl; }
        payment.displayAmount();
    }
};

int main() {
    Menu menu;
    menu.addItem("Burger", 500.0);
    menu.addItem("Pizza", 1199.99);
    menu.addItem("Pasta", 350.50);
    menu.displayMenu();  
    Order order;
    order.addItem(menu.items[0]);
    order.addItem(menu.items[2]);   
    order.calculatePayment();
    cout << "\n";
    order.displayOrder();
    return 0;
}
