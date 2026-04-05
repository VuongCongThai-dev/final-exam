#ifndef COFFEE_SHOP_H
#define COFFEE_SHOP_H

#include <vector>
#include <string>
#include "Menu.h"
#include "Order.h"
#include "Customer.h"
#include "Employee.h"
#include "Table.h"
#include "Exceptions.h"
using namespace std;

// Class chinh quan ly toan bo quan ca phe
class CoffeeShop {
private:
    string           shopName;
    Menu             menu;
    vector<Customer> customers;
    vector<Employee*> employees; // Polymorphic, so use pointer
    vector<Order>    orders;
    vector<Table>    tables;

    int              nextCustomerId;
    int              nextEmployeeId;
    int              nextOrderId;
    int              nextTableId;

public:
    CoffeeShop(const string& name);
    ~CoffeeShop(); // Giai phong vung nho cho employees

    // ====== QUAN LY MENU ======
    void addProduct(const string& name, double sellingPrice, double costPrice, ProductType type);
    void removeProduct(const string& name);
    void updateProductPrice(const string& name, double newSellingPrice, double newCostPrice);
    void showMenu() const;
    void showMenuByType(ProductType type) const;

    // ====== QUAN LY BAN ======
    void addTable(int capacity, bool isShared);
    void showTables() const;
    int  assignTable(int people, bool agreeToShare); // Tra ve tableId, -1 neu khong tim thay
    void freeTable(int tableId);

    // ====== QUAN LY DON HANG ======
    Order& createOrder(OrderType type, int peopleCount = 0, bool agreeToShare = false); 
    void   addItemToOrder(int orderId, const string& productName, int qty);
    void   removeItemFromOrder(int orderId, const string& productName);
    void   checkoutOrder(int orderId);                 
    void   showOrder(int orderId) const;
    void   showAllOrders() const;

    // ====== LOI NHUAN ======
    void showProfitReport() const;

    // ====== QUAN LY KHACH HANG ======
    void addCustomer(const string& name, const string& phone);
    Customer& findCustomer(const string& name);
    void showAllCustomers() const;

    // ====== QUAN LY NHAN VIEN ======
    void addFulltimeEmployee(const string& name, const string& phone, EmployeeRole role, double monthlySalary);
    void addParttimeEmployee(const string& name, const string& phone, EmployeeRole role, double hourlyWage);
    Employee* findEmployee(const string& name);
    void showAllEmployees() const;

    // ====== LUU / DOC FILE ======
    void saveAll() const;
    void loadAll();

    // Getter
    const string& getShopName() const { return shopName; }

private:
    // Ham noi bo: tim don hang theo id
    Order& findOrder(int orderId);
    const Order& findOrder(int orderId) const;
};

#endif
