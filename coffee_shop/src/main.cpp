#include <iostream>
#include <limits>
#include "../include/CoffeeShop.h"
using namespace std;

// Ham doc so nguyen an toan (khong bi loi neu nhap chu)
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw InvalidInputException("Vui long nhap so nguyen hop le");
        }
        cin.ignore();
        return value;
    }
}

double readDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw InvalidInputException("Vui long nhap so hop le");
        }
        cin.ignore();
        return value;
    }
}

string readString(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    if (value.empty())
        throw InvalidInputException("Khong duoc de trong");
    return value;
}

// ============================
//     MENU THUC DON
// ============================
void handleMenu(CoffeeShop& shop) {
    int choice;
    do {
        cout << "\n--- QUAN LY THUC DON ---\n";
        cout << "1. Xem toan bo thuc don\n";
        cout << "2. Them san pham\n";
        cout << "3. Xoa san pham\n";
        cout << "4. Cap nhat gia\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        choice = readInt("");

        try {
            if (choice == 1) {
                shop.showMenu();
            } else if (choice == 2) {
                string name = readString("Ten san pham: ");
                double sellingPrice = readDouble("Gia Ban (VND): ");
                double costPrice = readDouble("Gia Von (VND): ");

                cout << "Loai (1=Ca phe, 2=Tra, 3=Nuoc ep, 4=Khac): ";
                int typeChoice = readInt("");
                ProductType type;
                switch (typeChoice) {
                    case 1: type = ProductType::COFFEE; break;
                    case 2: type = ProductType::TEA;    break;
                    case 3: type = ProductType::JUICE;  break;
                    default: type = ProductType::OTHER; break;
                }
                shop.addProduct(name, sellingPrice, costPrice, type);

            } else if (choice == 3) {
                string name = readString("Ten san pham can xoa: ");
                shop.removeProduct(name);

            } else if (choice == 4) {
                string name  = readString("Ten san pham: ");
                double sellingPrice = readDouble("Gia Ban moi (VND): ");
                double costPrice = readDouble("Gia Von moi (VND): ");
                shop.updateProductPrice(name, sellingPrice, costPrice);
            }

        } catch (const CoffeeShopException& e) {
            cout << "[LOI] " << e.what() << endl;
        }

    } while (choice != 0);
}

// ============================
//     MENU DON HANG
// ============================
void handleOrders(CoffeeShop& shop) {
    int choice;
    do {
        cout << "\n--- QUAN LY DON HANG ---\n";
        cout << "1. Tao don hang moi\n";
        cout << "2. Them mon vao don\n";
        cout << "3. Xoa mon khoi don\n";
        cout << "4. Thanh toan don hang\n";
        cout << "5. Xem hoa don\n";
        cout << "6. Xem tat ca don hang\n";
        cout << "7. Xem tong loi nhuan\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        choice = readInt("");

        try {
            if (choice == 1) {
                int typeChoice = readInt("Loai don (1: Tai cho, 2: Mang ve): ");
                OrderType type = (typeChoice == 1) ? OrderType::DINE_IN : OrderType::TAKEAWAY;
                int people = 0;
                bool share = false;
                if (type == OrderType::DINE_IN) {
                    people = readInt("So luong khach: ");
                    int shareChoice = readInt("Khach co dong y ghep ban khong? (1: Co, 0: Khong): ");
                    share = (shareChoice == 1);
                }
                shop.createOrder(type, people, share);

            } else if (choice == 2) {
                int orderId = readInt("Ma don hang: ");
                string name = readString("Ten san pham: ");
                int qty     = readInt("So luong: ");
                shop.addItemToOrder(orderId, name, qty);
                cout << "=> Da them vao don hang #" << orderId << endl;

            } else if (choice == 3) {
                int orderId = readInt("Ma don hang: ");
                string name = readString("Ten san pham can xoa: ");
                shop.removeItemFromOrder(orderId, name);
                cout << "=> Da xoa khoi don hang #" << orderId << endl;

            } else if (choice == 4) {
                int orderId = readInt("Ma don hang: ");
                shop.checkoutOrder(orderId);

            } else if (choice == 5) {
                int orderId = readInt("Ma don hang: ");
                shop.showOrder(orderId);

            } else if (choice == 6) {
                shop.showAllOrders();
            } else if (choice == 7) {
                shop.showProfitReport();
            }

        } catch (const CoffeeShopException& e) {
            cout << "[LOI] " << e.what() << endl;
        }

    } while (choice != 0);
}

// ============================
//     MENU KHACH HANG
// ============================
void handleCustomers(CoffeeShop& shop) {
    int choice;
    do {
        cout << "\n--- QUAN LY KHACH HANG ---\n";
        cout << "1. Xem danh sach khach hang\n";
        cout << "2. Them khach hang\n";
        cout << "3. Them diem tich luy\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        choice = readInt("");

        try {
            if (choice == 1) {
                shop.showAllCustomers();

            } else if (choice == 2) {
                string name  = readString("Ten khach hang: ");
                string phone = readString("So dien thoai: ");
                shop.addCustomer(name, phone);

            } else if (choice == 3) {
                string name = readString("Ten khach hang: ");
                int pts     = readInt("So diem them: ");
                Customer& c = shop.findCustomer(name);
                c.addPoints(pts);
                cout << "=> Da them " << pts << " diem cho " << name << endl;
            }

        } catch (const CoffeeShopException& e) {
            cout << "[LOI] " << e.what() << endl;
        }

    } while (choice != 0);
}

// ============================
//     MENU NHAN VIEN
// ============================
void handleEmployees(CoffeeShop& shop) {
    int choice;
    do {
        cout << "\n--- QUAN LY NHAN VIEN ---\n";
        cout << "1. Xem danh sach nhan vien\n";
        cout << "2. Them nhan vien\n";
        cout << "3. Ghi nhan them gio lam (cho Parttime)\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        choice = readInt("");

        try {
            if (choice == 1) {
                shop.showAllEmployees();

            } else if (choice == 2) {
                string name  = readString("Ten nhan vien: ");
                string phone = readString("So dien thoai: ");
                
                int roleChoice = readInt("Chuc vu (1=Quan ly, 2=Nhan vien): ");
                EmployeeRole role = (roleChoice == 1) ? EmployeeRole::MANAGER : EmployeeRole::STAFF;
                
                int typeChoice = readInt("Loai (1=Fulltime, 2=Parttime): ");
                if (typeChoice == 1) {
                    double sal = readDouble("Luong thang (VND): ");
                    shop.addFulltimeEmployee(name, phone, role, sal);
                } else {
                    double wage = readDouble("Luong 1 gio (VND): ");
                    shop.addParttimeEmployee(name, phone, role, wage);
                }
            } else if (choice == 3) {
                string name = readString("Ten nhan vien Parttime: ");
                double hours = readDouble("So gio lam can cong them: ");
                Employee* emp = shop.findEmployee(name);
                if (emp->getType() == EmployeeType::PARTTIME) {
                    ParttimeEmployee* pEmp = dynamic_cast<ParttimeEmployee*>(emp);
                    if (pEmp) {
                        pEmp->addHours(hours);
                        cout << "=> Da cong " << hours << "h vao the cua " << name << ". (Tong: " << pEmp->getHoursWorked() << "h)\n";
                    }
                } else {
                    cout << "[LOI] Nhan vien nay khong phai Parttime!\n";
                }
            }

        } catch (const CoffeeShopException& e) {
            cout << "[LOI] " << e.what() << endl;
        }

    } while (choice != 0);
}

// ============================
//     MENU QUAN LY BAN
// ============================
void handleTables(CoffeeShop& shop) {
    int choice;
    do {
        cout << "\n--- QUAN LY BAN ---\n";
        cout << "1. Xem danh sach ban\n";
        cout << "2. Them ban moi\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        choice = readInt("");

        try {
            if (choice == 1) {
                shop.showTables();
            } else if (choice == 2) {
                int capacity = readInt("Suc chua cua ban (so khach): ");
                int shareOpt = readInt("Ban co the ghep khong? (1: Co, 0: Khong): ");
                shop.addTable(capacity, shareOpt == 1);
            }
        } catch (const CoffeeShopException& e) {
            cout << "[LOI] " << e.what() << endl;
        }

    } while (choice != 0);
}

// ============================
//         MAIN
// ============================
void printMainMenu() {
    cout << "\n========================================\n";
    cout << "    QUAN LY QUAN CA PHE\n";
    cout << "========================================\n";
    cout << "1. Quan ly thuc don (Menu)\n";
    cout << "2. Quan ly don hang\n";
    cout << "3. Quan ly khach hang\n";
    cout << "4. Quan ly nhan vien\n";
    cout << "5. Quan ly ban\n";
    cout << "6. Luu du lieu\n";
    cout << "0. Thoat\n";
    cout << "----------------------------------------\n";
    cout << "Chon: ";
}

int main() {
    CoffeeShop shop("The Coffee House");

    cout << "Chao mung den " << shop.getShopName() << "!\n";

    // Inject vai ban de demo
    shop.addTable(2, false); // Ban so 1 (2 nguoi, k ghep)
    shop.addTable(4, true);  // Ban so 2 (4 nguoi, co ghep)
    shop.addTable(4, true);  // Ban so 3 (4 nguoi, co ghep)
    shop.addTable(6, true);  // Ban so 4 (6 nguoi, co ghep)

    try {
        shop.loadAll();
    } catch (const exception& e) {
        cout << "[CANH BAO] Khong the tai du lieu: " << e.what() << endl;
    }

    int choice;
    do {
        printMainMenu();
        choice = readInt("");

        try {
            switch (choice) {
                case 1: handleMenu(shop);      break;
                case 2: handleOrders(shop);    break;
                case 3: handleCustomers(shop); break;
                case 4: handleEmployees(shop); break;
                case 5: handleTables(shop);    break;
                case 6:
                    shop.saveAll();
                    break;
                case 0:
                    cout << "=> Tu dong luu du lieu truoc khi thoat...\n";
                    shop.saveAll();
                    cout << "Tam biet!\n";
                    break;
                default:
                    cout << "[LOI] Lua chon khong hop le!\n";
            }
        } catch (const CoffeeShopException& e) {
            cout << "[LOI] " << e.what() << endl;
        } catch (const exception& e) {
            cout << "[LOI HE THONG] " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}
