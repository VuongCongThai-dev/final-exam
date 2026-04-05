#include "../include/Order.h"
#include <iomanip>
using namespace std;

Order::Order(int id, OrderType type, int tableId) : id(id), isPaid(false), type(type), tableId(tableId) {}

// Them mon vao don hang
void Order::addItem(const Product& product, int quantity) {
    if (quantity <= 0)
        throw InvalidInputException("So luong phai lon hon 0");

    for (auto& item : items) {
        if (item.product.getName() == product.getName()) {
            item.quantity += quantity;
            return;
        }
    }
    items.push_back(OrderItem(product, quantity));
}

// Xoa mon khoi don hang theo ten san pham
void Order::removeItem(const string& productName) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->product.getName() == productName) {
            items.erase(it);
            return;
        }
    }
    throw ProductNotFoundException(productName);
}

// Tinh tong tien don hang
double Order::totalAmount() const {
    double total = 0;
    for (const auto& item : items) {
        total += item.subtotalAmount();
    }
    return total;
}

// Tinh tong chi phi don hang
double Order::totalCost() const {
    double total = 0;
    for (const auto& item : items) {
        total += item.subtotalCost();
    }
    return total;
}

// Tinh loi nhuan don hang
double Order::calculateProfit() const {
    return totalAmount() - totalCost();
}

// Thanh toan don hang
void Order::checkout() {
    if (items.empty())
        throw EmptyOrderException();

    isPaid = true;
    cout << "=> Thanh toan thanh cong! Tong tien: "
         << fixed << setprecision(0) << totalAmount() << " VND" << endl;
}

// In hoa don ra man hinh
void Order::printInvoice() const {
    cout << "\n========== HOA DON #" << id << " ==========\n";
    cout << "Loai don: " << (type == OrderType::DINE_IN ? "Uong tai cho (Ban " + to_string(tableId) + ")" : "Mang ve") << endl;
    cout << left << setw(20) << "San pham"
         << setw(10) << "Don gia"
         << setw(8)  << "SL"
         << setw(12) << "Thanh tien" << endl;
    cout << string(50, '-') << endl;

    for (const auto& item : items) {
        cout << left
             << setw(20) << item.product.getName()
             << setw(10) << fixed << setprecision(0) << item.product.getSellingPrice()
             << setw(8)  << item.quantity
             << setw(12) << item.subtotalAmount()
             << endl;
    }

    cout << string(50, '-') << endl;
    cout << "TONG CONG: " << fixed << setprecision(0) << totalAmount() << " VND" << endl;
    cout << "Trang thai: " << (isPaid ? "Da thanh toan" : "Chua thanh toan") << endl;
    if (!note.empty())
        cout << "Ghi chu: " << note << endl;
    cout << "==========================================\n";
}
