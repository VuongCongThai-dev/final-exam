#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class Person {
protected:
  string id;
  string name;

public:
  Person() {
    this->id = "";
    this->name = "";
  }

  Person(string id, string name) {
    this->id = id;
    this->name = name;
  }

  virtual ~Person() {}

  string getId() { return id; }
  string getName() { return name; }

  void setId(string id) { this->id = id; }
  void setName(string name) { this->name = name; }

  virtual void showInfo() { cout << "  " << id << "\t" << name << endl; }

  virtual void input() {
    cout << "  Nhap ten: ";
    getline(cin, name);
  }
};

class Drink {
private:
  string id;
  string name;
  long long price;

public:
  Drink() {
    this->id = "";
    this->name = "";
    this->price = 0;
  }

  Drink(string id, string name, long long price) {
    this->id = id;
    this->name = name;
    this->price = price;
  }

  string getId() { return id; }
  string getName() { return name; }
  long long getPrice() { return price; }

  void setId(string id) { this->id = id; }
  void setName(string name) { this->name = name; }
  void setPrice(long long price) { this->price = price; }

  void showInfo() {
    cout << "  " << id << "\t" << name << "\t" << price << endl;
  }

  void input() {
    cout << "  Nhap ten do uong: ";
    getline(cin, name);
    cout << "  Nhap gia: ";
    cin >> price;
    cin.ignore();
  }
};

class Employee : public Person {
private:
  string position;

public:
  Employee() : Person() { this->position = ""; }

  Employee(string id, string name, string position) : Person(id, name) {
    this->position = position;
  }

  string getPosition() { return position; }

  void setPosition(string position) { this->position = position; }

  void showInfo() override {
    cout << "  " << id << "\t" << name << "\t" << position << endl;
  }

  void input() override {
    cout << "  Nhap ten: ";
    getline(cin, name);
    cout << "  Nhap chuc vu: ";
    getline(cin, position);
  }
};

class OrderDetail {
private:
  string drinkId;
  string drinkName;
  long long unitPrice;
  int quantity;

public:
  OrderDetail() {
    this->drinkId = "";
    this->drinkName = "";
    this->unitPrice = 0;
    this->quantity = 0;
  }

  OrderDetail(string drinkId, string drinkName, long long unitPrice,
              int quantity) {
    this->drinkId = drinkId;
    this->drinkName = drinkName;
    this->unitPrice = unitPrice;
    this->quantity = quantity;
  }

  string getDrinkId() { return drinkId; }
  string getDrinkName() { return drinkName; }
  long long getUnitPrice() { return unitPrice; }
  int getQuantity() { return quantity; }
  long long getSubTotal() { return unitPrice * quantity; }

  void setDrinkId(string drinkId) { this->drinkId = drinkId; }
  void setDrinkName(string drinkName) { this->drinkName = drinkName; }
  void setUnitPrice(long long unitPrice) { this->unitPrice = unitPrice; }
  void setQuantity(int quantity) { this->quantity = quantity; }

  void showInfo() {
    cout << "  " << drinkId << "\t" << drinkName << "\t" << unitPrice << "\t"
         << quantity << "\t" << getSubTotal() << endl;
  }
};

class Table {
private:
  string id;
  bool available;

public:
  Table() {
    this->id = "";
    this->available = true;
  }

  Table(string id, bool available) {
    this->id = id;
    this->available = available;
  }

  string getId() { return id; }
  bool isAvailable() { return available; }

  void setId(string id) { this->id = id; }
  void setAvailable(bool available) { this->available = available; }

  void showInfo() {
    string trangThai;
    if (available) {
      trangThai = "Trong";
    } else {
      trangThai = "Co khach";
    }
    cout << "  " << id << "\t" << trangThai << endl;
  }

  void input() {}
};

const int MAX_DETAILS = 20;

class Order {
private:
  string id;
  string employeeName;
  string tableId;
  OrderDetail details[MAX_DETAILS];
  int detailCount;
  string date;
  bool isPaid;

public:
  Order() {
    this->id = "";
    this->employeeName = "";
    this->tableId = "";
    this->detailCount = 0;
    this->date = "";
    this->isPaid = false;
  }

  Order(string id, string employeeName, string tableId, string date) {
    this->id = id;
    this->employeeName = employeeName;
    this->tableId = tableId;
    this->detailCount = 0;
    this->date = date;
    this->isPaid = false;
  }

  string getId() { return id; }
  string getEmployeeName() { return employeeName; }
  string getTableId() { return tableId; }
  int getDetailCount() { return detailCount; }
  string getDate() { return date; }
  bool getIsPaid() { return isPaid; }

  long long getTotalAmount() {
    long long total = 0;
    for (int i = 0; i < detailCount; i++) {
      total += details[i].getSubTotal();
    }
    return total;
  }

  OrderDetail getDetail(int index) { return details[index]; }

  void setId(string id) { this->id = id; }
  void setEmployeeName(string employeeName) {
    this->employeeName = employeeName;
  }
  void setTableId(string tableId) { this->tableId = tableId; }
  void setDate(string date) { this->date = date; }
  void setIsPaid(bool isPaid) { this->isPaid = isPaid; }

  void addDetail(OrderDetail detail) {
    if (detailCount < MAX_DETAILS) {
      details[detailCount++] = detail;
    }
  }

  void showInfo() {
    cout << endl;
    cout << "  HOA DON: " << id << endl;
    cout << "  Nhan vien  : " << employeeName << endl;
    cout << "  Ban        : " << tableId << endl;
    cout << "  Ngay       : " << date << endl;
    cout << "  Trang thai : " << (isPaid ? "Da thanh toan" : "Chua thanh toan")
         << endl;
    cout << endl;
    cout << "  Chi tiet don hang:" << endl;
    cout << "  " << "Ma" << "\t" << "Ten" << "\t" << "Don gia" << "\t" << "SL"
         << "\t" << "Thanh tien" << endl;
    for (int i = 0; i < detailCount; i++) {
      details[i].showInfo();
    }
    cout << endl;
    cout << "  TONG TIEN: " << getTotalAmount() << " VND" << endl;
  }
};

const int MAX_DRINKS = 1000;

class DrinkManager {
private:
  Drink drinks[MAX_DRINKS];
  int count;

public:
  DrinkManager() { count = 0; }

  int getCount() { return count; }
  Drink getDrink(int index) { return drinks[index]; }

  Drink *findById(string id) {
    for (int i = 0; i < count; i++) {
      if (drinks[i].getId() == id)
        return &drinks[i];
    }
    return nullptr;
  }

  int findIndexById(string id) {
    for (int i = 0; i < count; i++) {
      if (drinks[i].getId() == id)
        return i;
    }
    return -1;
  }

  void add() {
    if (count >= MAX_DRINKS) {
      cout << "  Danh sach do uong da day!" << endl;
      return;
    }

    displayAll();
    string id;
    cout << "  Nhap ma do uong: ";
    getline(cin, id);

    if (findById(id) != nullptr) {
      cout << "  Ma do uong da ton tai!" << endl;
      return;
    }

    drinks[count].setId(id);
    drinks[count].input();
    count++;
    cout << "  Them do uong thanh cong!" << endl;
  }

  void update() {
    displayAll();
    string id;
    cout << "  Nhap ma do uong can sua: ";
    getline(cin, id);

    Drink *d = findById(id);
    if (d == nullptr) {
      cout << "  Khong tim thay do uong!" << endl;
      return;
    }

    cout << "  Thong tin hien tai:" << endl;
    d->showInfo();
    cout << endl;
    cout << "  Nhap thong tin moi:" << endl;
    d->input();
    cout << "  Cap nhat thanh cong!" << endl;
  }

  void remove() {
    displayAll();
    string id;
    cout << "  Nhap ma do uong can xoa: ";
    getline(cin, id);

    int index = findIndexById(id);
    if (index == -1) {
      cout << "  Khong tim thay do uong!" << endl;
      return;
    }

    for (int i = index; i < count - 1; i++) {
      drinks[i] = drinks[i + 1];
    }
    count--;
    cout << "  Xoa do uong thanh cong!" << endl;
  }

  void displayAll() {
    if (count == 0) {
      cout << "  Danh sach do uong trong!" << endl;
      return;
    }
    cout << endl << "  DANH SACH DO UONG" << endl << endl;
    cout << "  " << left << setw(6) << "Ma" << "  " << left << setw(20) << "Ten"
         << "  " << left << setw(12) << "Gia" << endl;
    for (int i = 0; i < count; i++) {
      drinks[i].showInfo();
    }
    cout << "  Tong: " << count << " do uong" << endl;
  }
};

const int MAX_EMPLOYEES = 1000;

class EmployeeManager {
private:
  Employee employees[MAX_EMPLOYEES];
  int count;

public:
  EmployeeManager() { count = 0; }

  int getCount() { return count; }
  Employee getEmployee(int index) { return employees[index]; }

  Employee *findById(string id) {
    for (int i = 0; i < count; i++) {
      if (employees[i].getId() == id)
        return &employees[i];
    }
    return nullptr;
  }

  int findIndexById(string id) {
    for (int i = 0; i < count; i++) {
      if (employees[i].getId() == id)
        return i;
    }
    return -1;
  }

  void add() {
    if (count >= MAX_EMPLOYEES) {
      cout << "  Danh sach nhan vien da day!" << endl;
      return;
    }

    displayAll();
    string id;
    cout << "  Nhap ma nhan vien: ";
    getline(cin, id);

    if (findById(id) != nullptr) {
      cout << "  Ma nhan vien da ton tai!" << endl;
      return;
    }

    employees[count].setId(id);
    employees[count].input();
    count++;
    cout << "  Them nhan vien thanh cong!" << endl;
  }

  void update() {
    displayAll();
    string id;
    cout << "  Nhap ma nhan vien can sua: ";
    getline(cin, id);

    Employee *e = findById(id);
    if (e == nullptr) {
      cout << "  Khong tim thay nhan vien!" << endl;
      return;
    }

    cout << "  Thong tin hien tai:" << endl;
    e->showInfo();
    cout << endl;
    cout << "  Nhap thong tin moi:" << endl;
    e->input();
    cout << "  Cap nhat thanh cong!" << endl;
  }

  void remove() {
    displayAll();
    string id;
    cout << "  Nhap ma nhan vien can xoa: ";
    getline(cin, id);

    int index = findIndexById(id);
    if (index == -1) {
      cout << "  Khong tim thay nhan vien!" << endl;
      return;
    }

    for (int i = index; i < count - 1; i++) {
      employees[i] = employees[i + 1];
    }
    count--;
    cout << "  Xoa nhan vien thanh cong!" << endl;
  }

  void displayAll() {
    if (count == 0) {
      cout << "  Danh sach nhan vien trong!" << endl;
      return;
    }
    cout << endl << "  DANH SACH NHAN VIEN" << endl << endl;
    cout << "  " << left << setw(6) << "Ma" << "  " << left << setw(20) << "Ten"
         << "  " << left << setw(12) << "Chuc vu" << endl;
    for (int i = 0; i < count; i++) {
      employees[i].showInfo();
    }
    cout << "  Tong: " << count << " nhan vien" << endl;
  }
};

const int MAX_TABLES = 1000;

class TableManager {
private:
  Table tables[MAX_TABLES];
  int count;

public:
  TableManager() { count = 0; }

  int getCount() { return count; }
  Table getTable(int index) { return tables[index]; }

  Table *findById(string id) {
    for (int i = 0; i < count; i++) {
      if (tables[i].getId() == id)
        return &tables[i];
    }
    return nullptr;
  }

  int findIndexById(string id) {
    for (int i = 0; i < count; i++) {
      if (tables[i].getId() == id)
        return i;
    }
    return -1;
  }

  void add() {
    if (count >= MAX_TABLES) {
      cout << "  Danh sach ban da day!" << endl;
      return;
    }

    displayAll();
    string id;
    cout << "  Nhap ma ban: ";
    getline(cin, id);

    if (findById(id) != nullptr) {
      cout << "  Ma ban da ton tai!" << endl;
      return;
    }

    tables[count].setId(id);
    tables[count].input();
    count++;
    cout << "  Them ban thanh cong!" << endl;
  }

  void update() {
    string id;
    cout << "  Nhap ma ban can sua: ";
    getline(cin, id);

    Table *t = findById(id);
    if (t == nullptr) {
      cout << "  Khong tim thay ban!" << endl;
      return;
    }

    cout << "  Thong tin hien tai:" << endl;
    t->showInfo();
    cout << endl;
    cout << "  Nhap thong tin moi:" << endl;
    t->input();
    cout << "  Cap nhat thanh cong!" << endl;
  }

  void remove() {
    displayAll();
    string id;
    cout << "  Nhap ma ban can xoa: ";
    getline(cin, id);

    int index = findIndexById(id);
    if (index == -1) {
      cout << "  Khong tim thay ban!" << endl;
      return;
    }

    for (int i = index; i < count - 1; i++) {
      tables[i] = tables[i + 1];
    }
    count--;
    cout << "  Xoa ban thanh cong!" << endl;
  }

  void displayAll() {
    if (count == 0) {
      cout << "  Danh sach ban trong!" << endl;
      return;
    }
    cout << endl << "  DANH SACH BAN" << endl << endl;
    cout << "  " << left << setw(6) << "Ma" << "  " << left << setw(12)
         << "Trang thai" << endl;
    for (int i = 0; i < count; i++) {
      tables[i].showInfo();
    }
    cout << "  Tong: " << count << " ban" << endl;
  }
};

const int MAX_ORDERS = 1000;

class OrderManager {
private:
  Order orders[MAX_ORDERS];
  int count;

public:
  OrderManager() { count = 0; }

  int getCount() { return count; }

  Order *findById(string id) {
    for (int i = 0; i < count; i++) {
      if (orders[i].getId() == id)
        return &orders[i];
    }
    return nullptr;
  }

  int findIndexById(string id) {
    for (int i = 0; i < count; i++) {
      if (orders[i].getId() == id)
        return i;
    }
    return -1;
  }

  void add(DrinkManager &dm, EmployeeManager &em, TableManager &tm) {
    if (count >= MAX_ORDERS) {
      cout << "  Danh sach hoa don da day!" << endl;
      return;
    }

    displayAll();
    string orderId;
    cout << "  Nhap ma hoa don: ";
    getline(cin, orderId);

    if (findById(orderId) != nullptr) {
      cout << "  Ma hoa don da ton tai!" << endl;
      return;
    }

    em.displayAll();
    string empId;
    cout << "  Nhap ma nhan vien phuc vu: ";
    getline(cin, empId);
    Employee *emp = em.findById(empId);
    if (emp == nullptr) {
      cout << "  Khong tim thay nhan vien!" << endl;
      return;
    }

    tm.displayAll();
    string tableId;
    cout << "  Nhap ma ban: ";
    getline(cin, tableId);
    Table *table = tm.findById(tableId);
    if (table == nullptr) {
      cout << "  Khong tim thay ban!" << endl;
      return;
    }
    if (!table->isAvailable()) {
      cout << "  Ban nay hien dang co khach, khong the them hoa don moi!"
           << endl;
      return;
    }

    string date;
    cout << "  Nhap ngay (dd/mm/yyyy): ";
    getline(cin, date);

    Order order(orderId, emp->getName(), tableId, date);

    int choice = 1;
    while (choice == 1) {
      dm.displayAll();
      string drinkId;
      cout << "  Nhap ma do uong: ";
      getline(cin, drinkId);

      Drink *drink = dm.findById(drinkId);
      if (drink == nullptr) {
        cout << "  Khong tim thay do uong!" << endl;
      } else {
        int qty;
        cout << "  Nhap so luong: ";
        cin >> qty;
        cin.ignore();

        OrderDetail detail(drink->getId(), drink->getName(), drink->getPrice(),
                           qty);
        order.addDetail(detail);
        cout << "  Da them do uong vao hoa don!" << endl;
      }

      cout << "  Tiep tuc them do uong? (1: Co, 0: Khong): ";
      cin >> choice;
      cin.ignore();
    }

    table->setAvailable(false);

    orders[count++] = order;
    cout << "  Tao hoa don thanh cong!" << endl;
    order.showInfo();
  }

  void pay(TableManager &tm) {
    displayAll();
    string id;
    cout << "  Nhap ma hoa don can thanh toan: ";
    getline(cin, id);

    Order *o = findById(id);
    if (o == nullptr) {
      cout << "  Khong tim thay hoa don!" << endl;
      return;
    }

    if (o->getIsPaid()) {
      cout << "  Hoa don nay da duoc thanh toan truoc do!" << endl;
      return;
    }

    cout << "  Tong tien phai thanh toan: " << o->getTotalAmount() << " VND"
         << endl;
    o->setIsPaid(true);

    Table *table = tm.findById(o->getTableId());
    if (table != nullptr) {
      table->setAvailable(true);
    }

    cout << "  Thanh toan thanh cong! Ban da duoc giai phong." << endl;
  }

  void changeTable(TableManager &tm) {
    displayAll();
    string orderId;
    cout << "  Nhap ma hoa don can doi ban: ";
    getline(cin, orderId);

    Order *o = findById(orderId);
    if (o == nullptr) {
      cout << "  Khong tim thay hoa don!" << endl;
      return;
    }

    if (o->getIsPaid()) {
      cout << "  Hoa don nay da thanh toan, khong the doi ban!" << endl;
      return;
    }

    string oldTableId = o->getTableId();
    cout << "  Ban hien tai: " << oldTableId << endl;

    tm.displayAll();
    string newTableId;
    cout << "  Nhap ma ban moi muon chuyen den: ";
    getline(cin, newTableId);

    if (newTableId == oldTableId) {
      cout << "  Ban moi trung voi ban cu!" << endl;
      return;
    }

    Table *newTable = tm.findById(newTableId);
    if (newTable == nullptr) {
      cout << "  Khong tim thay ban moi!" << endl;
      return;
    }

    if (!newTable->isAvailable()) {
      cout << "  Ban moi hien dang co khach, khong the doi sang!" << endl;
      return;
    }

    Table *oldTable = tm.findById(oldTableId);
    if (oldTable != nullptr) {
      oldTable->setAvailable(true);
    }

    newTable->setAvailable(false);

    o->setTableId(newTableId);

    cout << "  Da doi ban thanh cong tu " << oldTableId << " sang "
         << newTableId << "!" << endl;
  }

  void remove() {
    displayAll();
    string id;
    cout << "  Nhap ma hoa don can xoa: ";
    getline(cin, id);

    int index = findIndexById(id);
    if (index == -1) {
      cout << "  Khong tim thay hoa don!" << endl;
      return;
    }

    for (int i = index; i < count - 1; i++) {
      orders[i] = orders[i + 1];
    }
    count--;
    cout << "  Xoa hoa don thanh cong!" << endl;
  }

  void displayAll() {
    if (count == 0) {
      cout << "  Danh sach hoa don trong!" << endl;
      return;
    }
    cout << endl << "  DANH SACH HOA DON" << endl << endl;
    for (int i = 0; i < count; i++) {
      orders[i].showInfo();
    }
    cout << "  Tong: " << count << " hoa don" << endl;
  }

  void revenueByDay() {
    string date;
    cout << "  Nhap ngay can xem (dd/mm/yyyy): ";
    getline(cin, date);

    long long totalRevenue = 0;
    int soHoaDon = 0;

    cout << endl << "  DOANH THU NGAY " << date << endl << endl;
    cout << "  " << "Ma HD" << "\t" << "Nhan vien"
         << "\t" << "Tong tien" << endl;

    for (int i = 0; i < count; i++) {
      if (orders[i].getDate() == date && orders[i].getIsPaid()) {
        cout << "  " << orders[i].getId() << "\t" << orders[i].getEmployeeName()
             << "\t" << orders[i].getTotalAmount() << endl;
        totalRevenue = totalRevenue + orders[i].getTotalAmount();
        soHoaDon++;
      }
    }

    if (soHoaDon == 0) {
      cout << "  Khong co hoa don nao da thanh toan trong ngay nay!" << endl;
    } else {
      cout << endl;
      cout << "  So hoa don  : " << soHoaDon << endl;
      cout << "  TONG DOANH THU: " << totalRevenue << " VND" << endl;
    }
  }
};

class Menu {
private:
  DrinkManager drinkManager;
  EmployeeManager employeeManager;
  TableManager tableManager;
  OrderManager orderManager;

  void drinkMenu() {
    int choice;
    do {
      system("cls");
      cout << endl << "  QUAN LY DO UONG" << endl << endl;
      cout << "  1. Them do uong" << endl;
      cout << "  2. Sua do uong" << endl;
      cout << "  3. Xoa do uong" << endl;
      cout << "  4. Hien thi danh sach" << endl;
      cout << "  0. Quay lai" << endl;
      cout << "  Lua chon: ";
      cin >> choice;
      cin.ignore();

      if (choice >= 1 && choice <= 4)
        system("cls");
      switch (choice) {
      case 1:
        drinkManager.add();
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 2:
        drinkManager.update();
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 3:
        drinkManager.remove();
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 4:
        drinkManager.displayAll();
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 0:
        break;
      default:
        cout << "  Lua chon khong hop le!" << endl;
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
      }
    } while (choice != 0);
  }

  void employeeMenu() {
    int choice;
    do {
      system("cls");
      cout << endl << "  QUAN LY NHAN VIEN" << endl << endl;
      cout << "  1. Them nhan vien" << endl;
      cout << "  2. Sua nhan vien" << endl;
      cout << "  3. Xoa nhan vien" << endl;
      cout << "  4. Hien thi danh sach" << endl;
      cout << "  0. Quay lai" << endl;
      cout << "  Lua chon: ";
      cin >> choice;
      cin.ignore();

      if (choice >= 1 && choice <= 4)
        system("cls");
      switch (choice) {
      case 1:
        employeeManager.add();
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 2:
        employeeManager.update();
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 3:
        employeeManager.remove();
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 4:
        employeeManager.displayAll();
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 0:
        break;
      default:
        cout << "  Lua chon khong hop le!" << endl;
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
      }
    } while (choice != 0);
  }

  void tableMenu() {
    int choice;
    do {
      system("cls");
      cout << endl << "  QUAN LY BAN" << endl << endl;
      cout << "  1. Them ban" << endl;
      cout << "  2. Doi ban" << endl;
      cout << "  3. Xoa ban" << endl;
      cout << "  4. Hien thi danh sach" << endl;
      cout << "  0. Quay lai" << endl;
      cout << "  Lua chon: ";
      cin >> choice;
      cin.ignore();

      if (choice >= 1 && choice <= 4)
        system("cls");
      switch (choice) {
      case 1:
        tableManager.add();
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 2:
        orderManager.changeTable(tableManager);
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 3:
        tableManager.remove();
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 4:
        tableManager.displayAll();
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 0:
        break;
      default:
        cout << "  Lua chon khong hop le!" << endl;
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
      }
    } while (choice != 0);
  }

  void orderMenu() {
    int choice;
    do {
      system("cls");
      cout << endl << "  QUAN LY HOA DON" << endl << endl;
      cout << "  1. Tao hoa don" << endl;
      cout << "  2. Thanh toan hoa don" << endl;
      cout << "  3. Xoa hoa don" << endl;
      cout << "  4. Hien thi danh sach" << endl;
      cout << "  0. Quay lai" << endl;
      cout << "  Lua chon: ";
      cin >> choice;
      cin.ignore();

      if (choice >= 1 && choice <= 4)
        system("cls");
      switch (choice) {
      case 1:
        orderManager.add(drinkManager, employeeManager, tableManager);
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 2:
        orderManager.pay(tableManager);
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 3:
        orderManager.remove();
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 4:
        orderManager.displayAll();
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 0:
        break;
      default:
        cout << "  Lua chon khong hop le!" << endl;
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
      }
    } while (choice != 0);
  }

  void revenueMenu() {
    int choice;
    do {
      system("cls");
      cout << endl << "  QUAN LY DOANH THU" << endl << endl;
      cout << "  1. Doanh thu theo ngay" << endl;
      cout << "  0. Quay lai" << endl;
      cout << "  Lua chon: ";
      cin >> choice;
      cin.ignore();

      if (choice == 1)
        system("cls");
      switch (choice) {
      case 1:
        orderManager.revenueByDay();
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
        break;
      case 0:
        break;
      default:
        cout << "  Lua chon khong hop le!" << endl;
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
      }
    } while (choice != 0);
  }

public:
  void run() {
    int choice;
    do {
      system("cls");
      cout << endl << "  QUAN LY QUAN COFFEE" << endl << endl;
      cout << "  1. Quan ly do uong" << endl;
      cout << "  2. Quan ly nhan vien" << endl;
      cout << "  3. Quan ly ban" << endl;
      cout << "  4. Quan ly hoa don" << endl;
      cout << "  5. Quan ly doanh thu" << endl;
      cout << "  0. Thoat" << endl;
      cout << "  Lua chon: ";
      cin >> choice;
      cin.ignore();

      switch (choice) {
      case 1:
        drinkMenu();
        break;
      case 2:
        employeeMenu();
        break;
      case 3:
        tableMenu();
        break;
      case 4:
        orderMenu();
        break;
      case 5:
        revenueMenu();
        break;
      case 0:
        break;
      default:
        cout << "  Lua chon khong hop le!" << endl;
        cout << endl << "  Nhan Enter de tiep tuc...";
        cin.get();
      }
    } while (choice != 0);
  }
};

int main() {
  Menu *menu = new Menu();
  menu->run();
  delete menu;
  return 0;
}