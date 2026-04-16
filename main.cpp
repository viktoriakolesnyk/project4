#include "Shop.h"

int main() {
    Shop shop;
    int choice;

    do {
        cout << "\nVictoria's shop\n";
        cout << "1. Add product\n";
        cout << "2. Remove product\n";
        cout << "3. Show order\n";
        cout << "4. Enter promo code\n";
        cout << "5. Checkout\n";
        cout << "6. Change status\n";
        cout << "7. Save receipt to JSON\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";

        cin >> choice;

        switch (choice) {
        case 1:
            shop.addProduct();
            break;

        case 2:
            shop.removeProduct();
            break;

        case 3:
            shop.showOrder();
            break;

        case 4: {
            string code;
            cout << "Enter promo code: ";
            cin >> code;
            shop.applyPromo(code);
            break;
        }

        case 5:
            shop.checkout();
            break;

        case 6:
            shop.changeStatus();
            break;

        case 7:
            shop.saveToJSON();
            break;

        case 0:
            cout << "Thank you, bye!\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}