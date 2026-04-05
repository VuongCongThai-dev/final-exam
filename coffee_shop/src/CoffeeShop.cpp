#include "../include/CoffeeShop.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;

CoffeeShop::CoffeeShop(const string& name)
    : shopName(name), nextCustomerId(1), nextEmployeeId(1), nextOrderId(1), nextTableId(1) {}

CoffeeShop::~CoffeeShop() {
    for (auto emp : employees) {
        delete emp;
    }
    employees.clear();
}

// ============================
//       QUAN LY MENU
// ============================

void CoffeeShop::addProduct(const string& name, double sellingPrice, double costPrice, ProductType type) {
    menu.addProduct(name, sellingPrice, costPrice, type);  
}

void CoffeeShop::removeProduct(const string& name) {
    menu.removeProduct(name);
}

void CoffeeShop::updateProductPrice(const string& name, double newSellingPrice, double newCostPrice) {
    menu.updatePrice(name, newSellingPrice, newCostPrice);
}

void CoffeeShop::showMenu() const { menu.display(); }

void CoffeeShop::showMenuByType(ProductType type) const { menu.displayByType(type); }

// ============================
//       QUAN LY BAN
// ============================

void CoffeeShop::addTable(int capacity, bool isShared) {
    tables.push_back(Table(nextTableId++, capacity, isShared));
    cout << "=> Da them Ban #" << tables.back().getId() 
         << " (Cho ngoi: " << capacity << ", Ghep: " << (isShared ? "Co" : "Khong") << ")\n";
}

void CoffeeShop::showTables() const {
    cout << "\n====== DANH SACH BAN ======\n";
    cout << left << setw(8) << "Ban ID" << setw(15) << "Suc Chua" << setw(20) << "Dang Ngoi" << "Cho Ghep\n";
    cout << string(60, '-') << endl;
    for (const auto& t : tables) {
        cout << left << setw(8) << t.getId() 
             << setw(15) << t.getCapacity() 
             << setw(20) << t.getCurrentOccupancy() 
             << (t.getIsShared() ? "Co" : "Khong") << endl;
    }
}

int CoffeeShop::assignTable(int people, bool agreeToShare) {
    // Thu tim ban trong truoc (va vuot suc chua 1 chut vao ban to cho chac)
    for (auto& t : tables) {
        if (t.isEmpty() && t.getCapacity() >= people) {
            t.assignPeople(people);
            return t.getId();
        }
    }
    // Neu khong co ban trong nao du hoac chi con ban chi de ghep
    if (agreeToShare) {
        for (auto& t : tables) {
            if (t.getIsShared() && t.hasSpace(people)) {
                t.assignPeople(people);
                return t.getId();
            }
        }
    }
    return -1; // KHong co ban hoac k ghep dc
}

void CoffeeShop::freeTable(int tableId) {
    for (auto& t : tables) {
        if (t.getId() == tableId) {
            t.clearTable();
            return;
        }
    }
}


// ============================
//      QUAN LY DON HANG
// ============================

Order& CoffeeShop::createOrder(OrderType type, int peopleCount, bool agreeToShare) {
    int tId = -1;
    if (type == OrderType::DINE_IN) {
        tId = assignTable(peopleCount, agreeToShare);
        if (tId == -1) {
            cout << "=> Xin loi, hien tai quan da het ban phu hop cho " << peopleCount << " nguoi.\n";
            // Tao 1 exception tam de bat ra trong main
            throw CoffeeShopException("Khong du ban de xep cho khach an tai cho!");
        }
        cout << "=> Khach duoc xep vao Ban #" << tId << endl;
    }
    orders.push_back(Order(nextOrderId++, type, tId));
    cout << "=> Da tao don hang #" << orders.back().getId() << endl;
    return orders.back();
}

void CoffeeShop::addItemToOrder(int orderId, const string& productName, int qty) {
    Product product = menu.findProduct(productName);
    Order& order = findOrder(orderId);
    order.addItem(product, qty);  
}

void CoffeeShop::removeItemFromOrder(int orderId, const string& productName) {
    Order& order = findOrder(orderId);
    order.removeItem(productName);
}

void CoffeeShop::checkoutOrder(int orderId) {
    Order& order = findOrder(orderId);
    order.checkout();  
    if (order.getType() == OrderType::DINE_IN && order.getTableId() != -1) {
        freeTable(order.getTableId()); // Giai phong ban khi khach ve
        cout << "=> Ban #" << order.getTableId() << " da duoc don dep.\n";
    }
}

void CoffeeShop::showOrder(int orderId) const {
    const Order& order = findOrder(orderId);
    order.printInvoice();
}

void CoffeeShop::showAllOrders() const {
    if (orders.empty()) { cout << "(Chua co don hang nao)\n"; return; }
    for (const auto& o : orders) o.printInvoice();
}

void CoffeeShop::showProfitReport() const {
    double totalRev = 0, totalCost = 0, totalProfit = 0;
    int paidOrders = 0;

    for (const auto& o : orders) {
        if (o.getIsPaid()) {
            totalRev += o.totalAmount();
            totalCost += o.totalCost();
            totalProfit += o.calculateProfit();
            paidOrders++;
        }
    }

    cout << "\n========== BAO CAO LOI NHUAN ==========\n";
    cout << "So don hang da thanh toan: " << paidOrders << endl;
    cout << "Tong Doanh Thu: " << fixed << setprecision(0) << totalRev << " VND\n";
    cout << "Tong Tien Von : " << fixed << setprecision(0) << totalCost << " VND\n";
    cout << "---------------------------------------\n";
    cout << "TONG LOI NHUAN: " << fixed << setprecision(0) << totalProfit << " VND\n";
    cout << "=======================================\n";
}

// ============================
//     QUAN LY KHACH HANG
// ============================
void CoffeeShop::addCustomer(const string& name, const string& phone) {
    for (const auto& c : customers) {
        if (c.getPhone() == phone) throw InvalidInputException("So dien thoai da duoc dang ky");
    }
    customers.push_back(Customer(nextCustomerId++, name, phone));
}

Customer& CoffeeShop::findCustomer(const string& name) {
    for (auto& c : customers) {
        if (c.getName() == name) return c;
    }
    throw CustomerNotFoundException(name);
}

void CoffeeShop::showAllCustomers() const {
    if (customers.empty()) { cout << "(Chua co khach hang nao)\n"; return; }
    for (const auto& c : customers) c.display();
}

// ============================
//     QUAN LY NHAN VIEN
// ============================
void CoffeeShop::addFulltimeEmployee(const string& name, const string& phone, EmployeeRole role, double monthlySalary) {
    employees.push_back(new FulltimeEmployee(nextEmployeeId++, name, phone, role, monthlySalary));
    cout << "=> Da them nhan vien Fulltime: " << name << endl;
}

void CoffeeShop::addParttimeEmployee(const string& name, const string& phone, EmployeeRole role, double hourlyWage) {
    employees.push_back(new ParttimeEmployee(nextEmployeeId++, name, phone, role, hourlyWage));
    cout << "=> Da them nhan vien Parttime: " << name << endl;
}

Employee* CoffeeShop::findEmployee(const string& name) {
    for (auto emp : employees) {
        if (emp->getName() == name) return emp;
    }
    throw EmployeeNotFoundException(name);
}

void CoffeeShop::showAllEmployees() const {
    cout << "\n====== DANH SACH NHAN VIEN ======\n";
    cout << left << setw(4) << "ID" << setw(20) << "Ten"
         << setw(15) << "SDT" << setw(12) << "Chuc vu"
         << right << setw(12) << "Loai" << setw(16) << "Luong" << endl;
    cout << string(80, '-') << endl;

    if (employees.empty()) {
        cout << "(Chua co nhan vien nao)\n";
    } else {
        for (const auto emp : employees) {
            emp->display();
        }
    }
}

// ============================
//      LUU / DOC FILE
// ============================
void CoffeeShop::saveAll() const {
    menu.saveToFile("data/products.txt");

    ofstream custFile("data/customers.txt");
    for (const auto& c : customers) custFile << c.toFileString() << "\n";
    custFile.close();

    ofstream empFile("data/employees.txt");
    for (const auto emp : employees) empFile << emp->toFileString() << "\n";
    empFile.close();

    cout << "=> Da luu du lieu thay doi xong!\n";
}

void CoffeeShop::loadAll() {
    try {
        menu.loadFromFile("data/products.txt");
    } catch (const FileException&) { cout << "(Tao file san pham moi)\n"; }

    try {
        ifstream custFile("data/customers.txt");
        if (!custFile.is_open()) throw FileException("data/customers.txt");

        customers.clear();
        string line;
        while (getline(custFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string idStr, name, phone, pointsStr;
            getline(ss, idStr, '|'); getline(ss, name, '|'); getline(ss, phone, '|'); getline(ss, pointsStr, '|');
            Customer c(stoi(idStr), name, phone);
            c.addPoints(stoi(pointsStr));
            customers.push_back(c);
            if (stoi(idStr) >= nextCustomerId) nextCustomerId = stoi(idStr) + 1;
        }
        custFile.close();
    } catch (const FileException&) { }

    try {
        ifstream empFile("data/employees.txt");
        if (!empFile.is_open()) throw FileException("data/employees.txt");

        for (auto emp : employees) delete emp;
        employees.clear();

        string line;
        while (getline(empFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string typeStr, idStr, name, phone, roleStr, param1, param2;
            getline(ss, typeStr, '|');
            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, phone, '|');
            getline(ss, roleStr, '|');
            getline(ss, param1, '|'); // luong (thang/gio)
            
            if (typeStr == "FULLTIME") {
                employees.push_back(new FulltimeEmployee(stoi(idStr), name, phone, stringToRole(roleStr), stod(param1)));
            } else if (typeStr == "PARTTIME") {
                getline(ss, param2, '|'); // gio lam
                employees.push_back(new ParttimeEmployee(stoi(idStr), name, phone, stringToRole(roleStr), stod(param1), stod(param2)));
            }
            if (stoi(idStr) >= nextEmployeeId) nextEmployeeId = stoi(idStr) + 1;
        }
        empFile.close();
    } catch (const FileException&) { }
}

Order& CoffeeShop::findOrder(int orderId) {
    for (auto& o : orders) { if (o.getId() == orderId) return o; }
    throw CoffeeShopException("Khong tim thay don hang");
}

const Order& CoffeeShop::findOrder(int orderId) const {
    for (const auto& o : orders) { if (o.getId() == orderId) return o; }
    throw CoffeeShopException("Khong tim thay don hang");
}
