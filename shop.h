#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Product {
public:
    string name;
    double price;
    int quantity;

    Product(string n, double p, int q);
};

class Order {
public:
    vector<Product> products;
    bool isPaid;
    string status;

    Order();
};

class Shop {
private:
    Order order;
    double discount;
    string promo;

public:
    Shop();

    void addProduct();
    void removeProduct();
    void showOrder();

    void applyPromo(const string& code);

    double calculateTotal() const;
    double calculateTotalWithoutDiscount() const;

    void checkout();
    void changeStatus();

    void saveToJSON() const;
};
