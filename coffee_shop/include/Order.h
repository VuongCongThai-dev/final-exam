#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include <iostream>
#include "Product.h"
#include "Exceptions.h"
using namespace std;

enum class OrderType {
    DINE_IN,
    TAKEAWAY
};

// Mot dong trong don hang (san pham + so luong)
struct OrderItem {
    Product product;
    int     quantity;

    OrderItem(const Product& p, int qty) : product(p), quantity(qty) {}

    double subtotalAmount() const {
        return product.getSellingPrice() * quantity;
    }
    double subtotalCost() const {
        return product.getCostPrice() * quantity;
    }
};

class Order {
private:
    int              id;
    vector<OrderItem> items;   // Danh sach mon trong don
    string           note;     // Ghi chu
    bool             isPaid;   // Da thanh toan chua
    OrderType        type;     // Loai: tai cho hay mang ve
    int              tableId;  // ID ban (neu an tai cho), -1 neu mang ve

public:
    // Constructor
    Order(int id, OrderType type = OrderType::TAKEAWAY, int tableId = -1);

    // Them mon vao don - throw neu so luong <= 0
    void addItem(const Product& product, int quantity);

    // Xoa mon khoi don theo ten - throw neu khong tim thay
    void removeItem(const string& productName);

    // Tinh tong tien
    double totalAmount() const;
    
    // Tinh tong tien von
    double totalCost() const;
    
    // Tinh loi nhuan = Amount - Cost
    double calculateProfit() const;

    // Thanh toan - throw neu don trong
    void checkout();

    // Getter
    int  getId()    const { return id; }
    bool getIsPaid() const { return isPaid; }
    const vector<OrderItem>& getItems() const { return items; }
    string getNote() const { return note; }
    OrderType getType() const { return type; }
    int getTableId() const { return tableId; }

    void setNote(const string& n) { note = n; }

    // In hoa don
    void printInvoice() const;
};

#endif
