#include "Shop.h"
#include <fstream>

Product::Product(string n, double p, int q) {
    name = n;
    price = p;
    quantity = q;
}

Order::Order() {
    isPaid = false;
    status = "collecting";
}

Shop::Shop() {
    discount = 0.0;
    promo = "";
}

void Shop::addProduct() {
    string name;
    double price;
    int quantity;

    cin.ignore();

    cout << "Enter product name: ";
    getline(cin, name);

    cout << "Enter price (UAH): ";
    cin >> price;

    cout << "Enter quantity: ";
    cin >> quantity;

    order.products.push_back(Product(name, price, quantity));

    cout << "Product added!\n";
}

void Shop::removeProduct() {
    if (order.products.empty()) {
        cout << "Cart is empty!\n";
        return;
    }

    int index;
    cout << "Enter product number: ";
    cin >> index;

    if (index < 1 || index > order.products.size()) {
        cout << "Invalid number!\n";
        return;
    }

    order.products.erase(order.products.begin() + index - 1);

    cout << "Product removed!\n";
}

void Shop::showOrder() {
    if (order.products.empty()) {
        cout << "Order is empty!\n";
        return;
    }

    cout << "\n========== ORDER ==========\n";

    for (int i = 0; i < order.products.size(); i++) {
        cout << i + 1 << ". "
            << order.products[i].name
            << " | " << order.products[i].price << " UAH"
            << " | x" << order.products[i].quantity << "\n";
    }

    cout << "---------------------------\n";

    double total = calculateTotalWithoutDiscount();

    if (discount == 0) {
        cout << "Total: " << total << " UAH\n";
    }
    else {
        cout << "Total without promo: " << total << " UAH\n";
        cout << "Discount: -" << discount * 100 << "%\n";
        cout << "Total with promo: " << calculateTotal() << " UAH\n";
    }
}

// promo code
void Shop::applyPromo(const string& code) {
    if (code == "SALE10") {
        discount = 0.10;
        promo = code;
        cout << "Promo applied (-10%)!\n";
    }
    else {
        cout << "Invalid promo code!\n";
    }
}

double Shop::calculateTotalWithoutDiscount() const {
    double total = 0.0;

    for (int i = 0; i < order.products.size(); i++) {
        total += order.products[i].price * order.products[i].quantity;
    }

    return total;
}

double Shop::calculateTotal() const {
    return calculateTotalWithoutDiscount() * (1 - discount);
}

void Shop::checkout() {
    if (order.products.empty()) {
        cout << "No products in order!\n";
        return;
    }

    int choice;
    cout << "\nChoose payment:\n1 - Cash\n2 - Card\nYour choice: ";
    cin >> choice;

    order.isPaid = (choice == 2);

    cout << "\n========== RECEIPT ==========\n";

    double total = calculateTotalWithoutDiscount();

    cout << "Total: " << total << " UAH\n";

    if (discount > 0) {
        cout << "Discount: -" << discount * 100 << "%\n";
        cout << "Total with promo: " << calculateTotal() << " UAH\n";
    }

    cout << "Status: " << order.status << "\n";
    cout << "Payment: " << (order.isPaid ? "paid" : "not paid") << "\n";
}

void Shop::changeStatus() {
    if (order.status == "collecting")
        order.status = "ready";
    else
        order.status = "collecting";

    cout << "Status: " << order.status << "\n";
}

// SAVE JSON (ONE FILE)
void Shop::saveToJSON() const {
    if (order.products.empty()) {
        cout << "Nothing to save!\n";
        return;
    }

    ofstream file("order.json"); 

    file << "{\n";
    file << "  \"status\": \"" << order.status << "\",\n";
    file << "  \"paid\": " << (order.isPaid ? "true" : "false") << ",\n";

    file << "  \"items\": [\n";

    for (int i = 0; i < order.products.size(); i++) {
        file << "    {\n";
        file << "      \"name\": \"" << order.products[i].name << "\",\n";
        file << "      \"price\": " << order.products[i].price << ",\n";
        file << "      \"quantity\": " << order.products[i].quantity << "\n";
        file << "    }";

        if (i != order.products.size() - 1)
            file << ",";

        file << "\n";
    }

    file << "  ],\n";
    file << "  \"total\": " << calculateTotalWithoutDiscount() << "\n";
    file << "}\n";

    file.close();

    cout << "Saved to order.json \n";
}
