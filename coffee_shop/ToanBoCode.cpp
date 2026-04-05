#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

// === EXCEPTIONS ===
class CoffeeShopException : public exception {
protected: string message;
public:
    CoffeeShopException(const string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};
class ProductNotFoundException : public CoffeeShopException {
public: ProductNotFoundException(const string& name) : CoffeeShopException("Khong tim thay san pham: " + name) {}
};
class InvalidInputException : public CoffeeShopException {
public: InvalidInputException(const string& field) : CoffeeShopException("Du lieu khong hop le: " + field) {}
};
class EmptyOrderException : public CoffeeShopException {
public: EmptyOrderException() : CoffeeShopException("Don hang trong!") {}
};
class CustomerNotFoundException : public CoffeeShopException {
public: CustomerNotFoundException(const string& name) : CoffeeShopException("Khong tim thay khach: " + name) {}
};
class EmployeeNotFoundException : public CoffeeShopException {
public: EmployeeNotFoundException(const string& name) : CoffeeShopException("Khong tim thay nhan vien: " + name) {}
};
class FileException : public CoffeeShopException {
public: FileException(const string& filename) : CoffeeShopException("Loi file: " + filename) {}
};

// === TABLE ===
class Table {
private: int id; int capacity; int currentOccupancy; bool isShared;
public:
    Table(int id, int cap, bool shared=false) : id(id), capacity(cap), currentOccupancy(0), isShared(shared) {}
    int getId() const { return id; }
    int getCapacity() const { return capacity; }
    int getCurrentOccupancy() const { return currentOccupancy; }
    bool getIsShared() const { return isShared; }
    bool hasSpace(int p) const { return (capacity - currentOccupancy) >= p; }
    bool isEmpty() const { return currentOccupancy == 0; }
    void assignPeople(int p) { currentOccupancy += p; }
    void clearTable() { currentOccupancy = 0; }
};

// === PRODUCT ===
enum class ProductType { COFFEE, TEA, JUICE, OTHER };
string productTypeToString(ProductType type);
ProductType stringToProductType(const string& str);

class Product {
private: int id; string name; double sellingPrice; double costPrice; ProductType type;
public:
    Product(int id, const string& name, double sPrice, double cPrice, ProductType type);
    int getId() const { return id; }
    string getName() const { return name; }
    double getSellingPrice() const { return sellingPrice; }
    double getCostPrice() const { return costPrice; }
    ProductType getType() const { return type; }
    void setName(const string& n);
    void setSellingPrice(double p);
    void setCostPrice(double c);
    void setType(ProductType t);
    void display() const;
    string toFileString() const;
};

// === CUSTOMER ===
class Customer {
private: int id; string name; string phone; int points;
public:
    Customer(int id, const string& name, const string& phone);
    int getId() const { return id; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
    int getPoints() const { return points; }
    void setName(const string& n);
    void setPhone(const string& p);
    void addPoints(int p);
    void display() const;
    string toFileString() const;
};

// === EMPLOYEE ===
enum class EmployeeRole { MANAGER, STAFF };
enum class EmployeeType { FULLTIME, PARTTIME };
string roleToString(EmployeeRole role);
EmployeeRole stringToRole(const string& str);

class Employee {
protected: int id; string name; string phone; EmployeeRole role;
public:
    Employee(int id, const string& name, const string& phone, EmployeeRole role);
    virtual ~Employee() {}
    int getId() const { return id; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
    EmployeeRole getRole() const { return role; }
    void setName(const string& n);
    void setPhone(const string& p);
    void setRole(EmployeeRole r);
    virtual EmployeeType getType() const = 0;
    virtual double calculateSalary() const = 0;
    virtual void display() const;
    virtual string toFileString() const;
};
class FulltimeEmployee : public Employee {
private: double monthlySalary;
public:
    FulltimeEmployee(int id, const string& n, const string& p, EmployeeRole r, double s);
    double getMonthlySalary() const { return monthlySalary; }
    void setMonthlySalary(double s);
    EmployeeType getType() const override { return EmployeeType::FULLTIME; }
    double calculateSalary() const override;
    void display() const override;
    string toFileString() const override;
};
class ParttimeEmployee : public Employee {
private: double hourlyWage; double hoursWorked;
public:
    ParttimeEmployee(int id, const string& n, const string& p, EmployeeRole r, double w, double h = 0);
    double getHourlyWage() const { return hourlyWage; }
    double getHoursWorked() const { return hoursWorked; }
    void setHourlyWage(double w);
    void addHours(double h);
    void resetHours();
    EmployeeType getType() const override { return EmployeeType::PARTTIME; }
    double calculateSalary() const override;
    void display() const override;
    string toFileString() const override;
};

// === MENU ===
class Menu {
private: vector<Product> products; int nextId;
public:
    Menu();
    void addProduct(const string& n, double sp, double cp, ProductType t);
    void removeProduct(const string& n);
    void updatePrice(const string& n, double sp, double cp);
    Product findProduct(const string& n) const;
    vector<Product> getByType(ProductType t) const;
    const vector<Product>& getAllProducts() const { return products; }
    void display() const;
    void displayByType(ProductType t) const;
    void saveToFile(const string& f) const;
    void loadFromFile(const string& f);
};

// === ORDER ===
enum class OrderType { DINE_IN, TAKEAWAY };
struct OrderItem {
    Product product; int quantity;
    OrderItem(const Product& p, int q) : product(p), quantity(q) {}
    double subtotalAmount() const { return product.getSellingPrice() * quantity; }
    double subtotalCost() const { return product.getCostPrice() * quantity; }
};
class Order {
private: int id; vector<OrderItem> items; string note; bool isPaid; OrderType type; int tableId;
public:
    Order(int id, OrderType type = OrderType::TAKEAWAY, int tableId = -1);
    void addItem(const Product& p, int q);
    void removeItem(const string& n);
    double totalAmount() const;
    double totalCost() const;
    double calculateProfit() const;
    void checkout();
    int getId() const { return id; }
    bool getIsPaid() const { return isPaid; }
    const vector<OrderItem>& getItems() const { return items; }
    string getNote() const { return note; }
    OrderType getType() const { return type; }
    int getTableId() const { return tableId; }
    void setNote(const string& n) { note = n; }
    void printInvoice() const;
};

// === COFFEESHOP ===
class CoffeeShop {
private:
    string shopName; Menu menu; vector<Customer> customers; vector<Employee*> employees;
    vector<Order> orders; vector<Table> tables;
    int nextCustomerId; int nextEmployeeId; int nextOrderId; int nextTableId;
public:
    CoffeeShop(const string& n);
    ~CoffeeShop();
    void addProduct(const string& n, double sp, double cp, ProductType t);
    void removeProduct(const string& n);
    void updateProductPrice(const string& n, double sp, double cp);
    void showMenu() const;
    void showMenuByType(ProductType t) const;
    void addTable(int cap, bool shared);
    void showTables() const;
    int assignTable(int p, bool share);
    void freeTable(int map);
    Order& createOrder(OrderType t, int p = 0, bool share = false);
    void addItemToOrder(int id, const string& n, int q);
    void removeItemFromOrder(int id, const string& n);
    void checkoutOrder(int id);
    void showOrder(int id) const;
    void showAllOrders() const;
    void showProfitReport() const;
    void addCustomer(const string& n, const string& p);
    Customer& findCustomer(const string& n);
    void showAllCustomers() const;
    void addFulltimeEmployee(const string& n, const string& p, EmployeeRole r, double s);
    void addParttimeEmployee(const string& n, const string& p, EmployeeRole r, double w);
    Employee* findEmployee(const string& n);
    void showAllEmployees() const;
    void saveAll() const;
    void loadAll();
    const string& getShopName() const { return shopName; }
private:
    Order& findOrder(int id);
    const Order& findOrder(int id) const;
};

// === PRODUCT.CPP ===
string productTypeToString(ProductType t) {
    if(t == ProductType::COFFEE) return "Ca phe"; if(t == ProductType::TEA) return "Tra"; if(t == ProductType::JUICE) return "Nuoc ep"; return "Khac";
}
ProductType stringToProductType(const string& str) {
    if (str == "Ca phe") return ProductType::COFFEE; if (str == "Tra") return ProductType::TEA; if (str == "Nuoc ep") return ProductType::JUICE; return ProductType::OTHER;
}
Product::Product(int id, const string& name, double sPrice, double cPrice, ProductType type) {
    if (name.empty()) throw InvalidInputException("Ten khong de trong");
    if (sPrice <= 0) throw InvalidInputException("Gia ban > 0");
    if (cPrice < 0) throw InvalidInputException("Gia von >= 0");
    this->id = id; this->name = name; this->sellingPrice = sPrice; this->costPrice = cPrice; this->type = type;
}
void Product::setName(const string& n) { if(n.empty()) throw InvalidInputException(""); name = n; }
void Product::setSellingPrice(double p) { if(p<=0) throw InvalidInputException(""); sellingPrice = p; }
void Product::setCostPrice(double c) { if(c<0) throw InvalidInputException(""); costPrice = c; }
void Product::setType(ProductType t) { type = t; }
void Product::display() const {
    cout << left << setw(4) << id << setw(20) << name << setw(12) << productTypeToString(type)
         << right << setw(10) << fixed << setprecision(0) << costPrice << " VON"
         << right << setw(10) << fixed << setprecision(0) << sellingPrice << " BAN\n";
}
string Product::toFileString() const {
    return to_string(id) + "|" + name + "|" + to_string(sellingPrice) + "|" + to_string(costPrice) + "|" + productTypeToString(type);
}

// === CUSTOMER.CPP ===
Customer::Customer(int id, const string& name, const string& phone) {
    if(name.empty() || phone.empty()) throw InvalidInputException("Khong de trong");
    for(char c: phone) if(!isdigit(c)) throw InvalidInputException("SDT chi chua so");
    this->id = id; this->name = name; this->phone = phone; this->points = 0;
}
void Customer::setName(const string& n) { if(n.empty()) throw InvalidInputException(""); name=n; }
void Customer::setPhone(const string& p) {
    if(p.empty()) throw InvalidInputException("");
    for(char c: p) if(!isdigit(c)) throw InvalidInputException("");
    phone = p;
}
void Customer::addPoints(int p) { if(p<0) throw InvalidInputException(""); points += p; }
void Customer::display() const {
    cout << left << setw(4) << id << setw(20) << name << setw(15) << phone << right << setw(8) << points << " diem\n";
}
string Customer::toFileString() const { return to_string(id) + "|" + name + "|" + phone + "|" + to_string(points); }

// === EMPLOYEE.CPP ===
string roleToString(EmployeeRole r) { return r == EmployeeRole::MANAGER ? "Quan ly" : "Nhan vien"; }
EmployeeRole stringToRole(const string& s) { return s == "Quan ly" ? EmployeeRole::MANAGER : EmployeeRole::STAFF; }
Employee::Employee(int id, const string& n, const string& p, EmployeeRole r) : id(id), name(n), phone(p), role(r) {
    if(n.empty() || p.empty()) throw InvalidInputException("");
}
void Employee::setName(const string& n) { if(n.empty()) throw InvalidInputException(""); name=n; }
void Employee::setPhone(const string& p) { if(p.empty()) throw InvalidInputException(""); phone=p; }
void Employee::setRole(EmployeeRole r) { role = r; }
void Employee::display() const {
    cout << left << setw(4) << id << setw(20) << name << setw(15) << phone << setw(12) << roleToString(role);
}
string Employee::toFileString() const { return to_string(id)+"|"+name+"|"+phone+"|"+roleToString(role); }

FulltimeEmployee::FulltimeEmployee(int id, const string& n, const string& p, EmployeeRole r, double s)
    : Employee(id, n, p, r) { if(s<0) throw InvalidInputException(""); monthlySalary=s; }
void FulltimeEmployee::setMonthlySalary(double s) { if(s<0) throw InvalidInputException(""); monthlySalary=s; }
double FulltimeEmployee::calculateSalary() const { return monthlySalary; }
void FulltimeEmployee::display() const {
    Employee::display(); cout << right << setw(12) << "Fulltime" << setw(16) << fixed << setprecision(0) << calculateSalary() << " VND\n";
}
string FulltimeEmployee::toFileString() const { return "FULLTIME|" + Employee::toFileString() + "|" + to_string(monthlySalary); }

ParttimeEmployee::ParttimeEmployee(int id, const string& n, const string& p, EmployeeRole r, double w, double h)
    : Employee(id, n, p, r) { if(w<0||h<0) throw InvalidInputException(""); hourlyWage=w; hoursWorked=h; }
void ParttimeEmployee::setHourlyWage(double w) { if(w<0) throw InvalidInputException(""); hourlyWage=w; }
void ParttimeEmployee::addHours(double h) { if(h<0) throw InvalidInputException(""); hoursWorked+=h; }
void ParttimeEmployee::resetHours() { hoursWorked = 0; }
double ParttimeEmployee::calculateSalary() const {
    if(hoursWorked <= 8) return hoursWorked * hourlyWage;
    return 8*hourlyWage + (hoursWorked-8)*(hourlyWage*1.5);
}
void ParttimeEmployee::display() const {
    Employee::display(); cout << right << setw(12) << "Parttime" << setw(16) << fixed << setprecision(0) << calculateSalary() << " VND (" << hoursWorked << "h)\n";
}
string ParttimeEmployee::toFileString() const { return "PARTTIME|" + Employee::toFileString() + "|" + to_string(hourlyWage) + "|" + to_string(hoursWorked); }

// === MENU.CPP ===
Menu::Menu() : nextId(1) {}
void Menu::addProduct(const string& n, double sp, double cp, ProductType t) {
    for(const auto& p: products) if(p.getName() == n) throw InvalidInputException("San pham da ton tai");
    products.push_back(Product(nextId++, n, sp, cp, t));
    cout << "=> Da them: " << n << endl;
}
void Menu::removeProduct(const string& n) {
    for(auto it=products.begin(); it!=products.end(); ++it)
        if(it->getName() == n) { products.erase(it); cout << "=> Da xoa\n"; return; }
    throw ProductNotFoundException(n);
}
void Menu::updatePrice(const string& n, double sp, double cp) {
    for(auto& p: products) if(p.getName() == n) { p.setSellingPrice(sp); p.setCostPrice(cp); return; }
    throw ProductNotFoundException(n);
}
Product Menu::findProduct(const string& n) const {
    for(const auto& p: products) if(p.getName() == n) return p;
    throw ProductNotFoundException(n);
}
vector<Product> Menu::getByType(ProductType t) const {
    vector<Product> r; for(const auto& p: products) if(p.getType() == t) r.push_back(p); return r;
}
void Menu::display() const {
    cout << "\n====== THUC DON ======\n";
    if(products.empty()) cout << "(Trong)\n";
    else for(const auto& p: products) p.display();
}
void Menu::displayByType(ProductType t) const {
    for(const auto& p: products) if(p.getType() == t) p.display();
}
void Menu::saveToFile(const string& f) const {
    ofstream file(f); if(!file.is_open()) throw FileException(f);
    for(const auto& p: products) file << p.toFileString() << "\n";
    file.close();
}
void Menu::loadFromFile(const string& f) {
    ifstream file(f); if(!file.is_open()) throw FileException(f);
    products.clear(); string line;
    while(getline(file, line)) {
        if(line.empty()) continue;
        stringstream ss(line); string idStr, n, sp, cp, ts;
        getline(ss,idStr,'|'); getline(ss,n,'|'); getline(ss,sp,'|'); getline(ss,cp,'|'); getline(ss,ts,'|');
        int id = stoi(idStr); products.push_back(Product(id, n, stod(sp), stod(cp), stringToProductType(ts)));
        if(id>=nextId) nextId=id+1;
    }
    file.close();
}

// === ORDER.CPP ===
Order::Order(int id, OrderType type, int tableId) : id(id), isPaid(false), type(type), tableId(tableId) {}
void Order::addItem(const Product& p, int q) {
    if(q<=0) throw InvalidInputException("SL > 0");
    for(auto& i: items) if(i.product.getName() == p.getName()) { i.quantity+=q; return; }
    items.push_back(OrderItem(p,q));
}
void Order::removeItem(const string& n) {
    for(auto it=items.begin(); it!=items.end(); ++it) if(it->product.getName() == n) { items.erase(it); return; }
    throw ProductNotFoundException(n);
}
double Order::totalAmount() const { double s=0; for(const auto& i: items) s+=i.subtotalAmount(); return s; }
double Order::totalCost() const { double s=0; for(const auto& i: items) s+=i.subtotalCost(); return s; }
double Order::calculateProfit() const { return totalAmount() - totalCost(); }
void Order::checkout() { if(items.empty()) throw EmptyOrderException(); isPaid=true; cout << "=> Thanh toan: " << fixed << setprecision(0) << totalAmount() << " VND\n"; }
void Order::printInvoice() const {
    cout << "\n========== HOA DON #" << id << " ==========\n";
    for(const auto& i: items) cout << i.product.getName() << " x " << i.quantity << " = " << i.subtotalAmount() << " VND\n";
    cout << "Tong cong: " << totalAmount() << " VND\n================\n";
}

// === COFFEESHOP.CPP ===
CoffeeShop::CoffeeShop(const string& n) : shopName(n), nextCustomerId(1), nextEmployeeId(1), nextOrderId(1), nextTableId(1) {}
CoffeeShop::~CoffeeShop() { for(auto e: employees) delete e; employees.clear(); }
void CoffeeShop::addProduct(const string& n, double sp, double cp, ProductType t) { menu.addProduct(n,sp,cp,t); }
void CoffeeShop::removeProduct(const string& n) { menu.removeProduct(n); }
void CoffeeShop::updateProductPrice(const string& n, double sp, double cp) { menu.updatePrice(n,sp,cp); }
void CoffeeShop::showMenu() const { menu.display(); }
void CoffeeShop::showMenuByType(ProductType t) const { menu.displayByType(t); }
void CoffeeShop::addTable(int cap, bool shared) { tables.push_back(Table(nextTableId++, cap, shared)); cout << "=> Them ban #" << tables.back().getId() << " xong.\n"; }
void CoffeeShop::showTables() const {
    cout << "\n=== DANH SACH BAN ===\n";
    for(const auto& t: tables) cout << "Ban #" << t.getId() << " (Cap: " << t.getCapacity() << ", Ngoi: " << t.getCurrentOccupancy() << ", Ghep: " << t.getIsShared() << ")\n";
}
int CoffeeShop::assignTable(int p, bool share) {
    for(auto& t: tables) if(t.isEmpty() && t.getCapacity()>=p) { t.assignPeople(p); return t.getId(); }
    if(share) for(auto& t: tables) if(t.getIsShared() && t.hasSpace(p)) { t.assignPeople(p); return t.getId(); }
    return -1;
}
void CoffeeShop::freeTable(int id) { for(auto& t: tables) if(t.getId() == id) { t.clearTable(); return; } }
Order& CoffeeShop::createOrder(OrderType t, int p, bool share) {
    int tId = -1;
    if(t == OrderType::DINE_IN) {
        tId = assignTable(p, share);
        if(tId==-1) throw CoffeeShopException("Het ban!");
        cout << "=> Ban #" << tId << endl;
    }
    orders.push_back(Order(nextOrderId++, t, tId)); return orders.back();
}
void CoffeeShop::addItemToOrder(int id, const string& n, int q) { findOrder(id).addItem(menu.findProduct(n), q); }
void CoffeeShop::removeItemFromOrder(int id, const string& n) { findOrder(id).removeItem(n); }
void CoffeeShop::checkoutOrder(int id) {
    Order& o = findOrder(id); o.checkout();
    if(o.getType() == OrderType::DINE_IN && o.getTableId() != -1) freeTable(o.getTableId());
}
void CoffeeShop::showOrder(int id) const { findOrder(id).printInvoice(); }
void CoffeeShop::showAllOrders() const { for(const auto& o: orders) o.printInvoice(); }
void CoffeeShop::showProfitReport() const {
    double rev=0, cost=0, pft=0; int cnt=0;
    for(const auto& o: orders) if(o.getIsPaid()) { rev+=o.totalAmount(); cost+=o.totalCost(); pft+=o.calculateProfit(); cnt++; }
    cout << "\n=== BAO CAO ===\nDon da thu: " << cnt << "\nDoanh thu: " << rev << "\nVon: " << cost << "\nLOI NHUAN: " << pft << " VND\n";
}
void CoffeeShop::addCustomer(const string& n, const string& p) {
    for(const auto& c: customers) if(c.getPhone() == p) throw InvalidInputException("SDT da dk");
    customers.push_back(Customer(nextCustomerId++, n, p));
}
Customer& CoffeeShop::findCustomer(const string& n) {
    for(auto& c: customers) if(c.getName() == n) return c; throw CustomerNotFoundException(n);
}
void CoffeeShop::showAllCustomers() const { for(const auto& c: customers) c.display(); }
void CoffeeShop::addFulltimeEmployee(const string& n, const string& p, EmployeeRole r, double s) { employees.push_back(new FulltimeEmployee(nextEmployeeId++, n, p, r, s)); }
void CoffeeShop::addParttimeEmployee(const string& n, const string& p, EmployeeRole r, double w) { employees.push_back(new ParttimeEmployee(nextEmployeeId++, n, p, r, w)); }
Employee* CoffeeShop::findEmployee(const string& n) {
    for(auto e: employees) if(e->getName() == n) return e; throw EmployeeNotFoundException(n);
}
void CoffeeShop::showAllEmployees() const { for(auto e: employees) e->display(); }
void CoffeeShop::saveAll() const {
    menu.saveToFile("data/products.txt");
    ofstream cF("data/customers.txt"); for(const auto& c: customers) cF << c.toFileString() << "\n"; cF.close();
    ofstream eF("data/employees.txt"); for(const auto e: employees) eF << e->toFileString() << "\n"; eF.close();
    cout << "=> Da luu\n";
}
void CoffeeShop::loadAll() {
    try { menu.loadFromFile("data/products.txt"); } catch(...) {}
    try {
        ifstream cF("data/customers.txt"); if(!cF.is_open()) throw FileException("");
        customers.clear(); string l;
        while(getline(cF,l)) {
            if(l.empty()) continue; stringstream ss(l); string i,n,p,pts;
            getline(ss,i,'|'); getline(ss,n,'|'); getline(ss,p,'|'); getline(ss,pts,'|');
            Customer c(stoi(i),n,p); c.addPoints(stoi(pts)); customers.push_back(c);
            if(stoi(i)>=nextCustomerId) nextCustomerId=stoi(i)+1;
        } cF.close();
    } catch(...) {}
    try {
        ifstream eF("data/employees.txt"); if(!eF.is_open()) throw FileException("");
        for(auto e: employees) delete e; employees.clear(); string l;
        while(getline(eF,l)) {
            if(l.empty()) continue; stringstream ss(l); string typ,id,n,pho,r,p1,p2;
            getline(ss,typ,'|'); getline(ss,id,'|'); getline(ss,n,'|'); getline(ss,pho,'|'); getline(ss,r,'|'); getline(ss,p1,'|');
            if(typ=="FULLTIME") employees.push_back(new FulltimeEmployee(stoi(id),n,pho,stringToRole(r),stod(p1)));
            else if(typ=="PARTTIME") { getline(ss,p2,'|'); employees.push_back(new ParttimeEmployee(stoi(id),n,pho,stringToRole(r),stod(p1),stod(p2))); }
            if(stoi(id)>=nextEmployeeId) nextEmployeeId=stoi(id)+1;
        } eF.close();
    } catch(...) {}
}
Order& CoffeeShop::findOrder(int id) { for(auto& o: orders) if(o.getId() == id) return o; throw CoffeeShopException("Khong tim don"); }
const Order& CoffeeShop::findOrder(int id) const { for(const auto& o: orders) if(o.getId() == id) return o; throw CoffeeShopException("Khong tim don"); }

// === MAIN.CPP ===
int readInt(const string& p) {
    int v; while(true) {
        cout << p; cin >> v;
        if(cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Loi nhap.\n"; }
        else { cin.ignore(); return v; }
    }
}
double readDouble(const string& p) {
    double v; while(true) {
        cout << p; cin >> v;
        if(cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Loi nhap.\n"; }
        else { cin.ignore(); return v; }
    }
}
string readString(const string& p) { string v; cout << p; getline(cin,v); return v; }

void handleMenu(CoffeeShop& shop) {
    int c; do {
        c = readInt("\n1.Xem 2.Them 3.Xoa 4.SuaGia 0.Ve\nChon: ");
        try {
            if(c==1) shop.showMenu();
            else if(c==2) shop.addProduct(readString("Ten: "), readDouble("Gia: "), readDouble("Von: "), ProductType::COFFEE);
            else if(c==3) shop.removeProduct(readString("Ten: "));
            else if(c==4) shop.updateProductPrice(readString("Ten: "), readDouble("Gia: "), readDouble("Von: "));
        } catch(const exception& e) { cout << "[LOI] " << e.what() << endl; }
    } while(c!=0);
}

void handleOrders(CoffeeShop& shop) {
    int c; do {
        c = readInt("\n1.Tao 2.ThemMon 3.XoaMon 4.ThanhToan 5.Xem 6.XemTatCa 7.LoiNhuan 0.Ve\nChon: ");
        try {
            if(c==1) shop.createOrder(OrderType::TAKEAWAY, 0, false);
            else if(c==2) shop.addItemToOrder(readInt("Don ID: "), readString("Ten: "), readInt("SL: "));
            else if(c==3) shop.removeItemFromOrder(readInt("Don ID: "), readString("Ten: "));
            else if(c==4) shop.checkoutOrder(readInt("Don ID: "));
            else if(c==5) shop.showOrder(readInt("Don ID: "));
            else if(c==6) shop.showAllOrders();
            else if(c==7) shop.showProfitReport();
        } catch(const exception& e) { cout << "[LOI] " << e.what() << endl; }
    } while(c!=0);
}

void handleCustomerEmp(CoffeeShop& shop) {
    int c; do {
        c = readInt("\n1.XemKhach 2.ThemKhach 3.XemNV 4.ThemNV 0.Ve\nChon: ");
        try {
            if(c==1) shop.showAllCustomers();
            else if(c==2) shop.addCustomer(readString("Ten: "), readString("SDT: "));
            else if(c==3) shop.showAllEmployees();
            else if(c==4) shop.addFulltimeEmployee(readString("Ten: "), readString("SDT: "), EmployeeRole::STAFF, 5000000);
        } catch(const exception& e) { cout << "[LOI] " << e.what() << endl; }
    } while(c!=0);
}

int main() {
    CoffeeShop shop("The Coffee House - Final");
    shop.loadAll();
    int c; do {
        c = readInt("\n1.ThucDon 2.DonHang 3.Khach&NV 4.Luu 0.Thoat\nChon: ");
        try {
            if(c==1) handleMenu(shop); else if(c==2) handleOrders(shop); else if(c==3) handleCustomerEmp(shop); else if(c==4) shop.saveAll();
        } catch(const exception& e) { cout << "[LOI] " << e.what() << endl; }
    } while(c!=0);
    shop.saveAll();
    return 0;
}
