#include "../include/Employee.h"
#include <iomanip>
using namespace std;

string roleToString(EmployeeRole role) {
    return (role == EmployeeRole::MANAGER) ? "Quan ly" : "Nhan vien";
}

EmployeeRole stringToRole(const string& str) {
    return (str == "Quan ly") ? EmployeeRole::MANAGER : EmployeeRole::STAFF;
}

// ==== EMPLOYEE ====
Employee::Employee(int id, const string& name, const string& phone, EmployeeRole role) {
    if (name.empty())
        throw InvalidInputException("Ten nhan vien khong duoc de trong");
    if (phone.empty())
        throw InvalidInputException("So dien thoai khong duoc de trong");

    this->id     = id;
    this->name   = name;
    this->phone  = phone;
    this->role   = role;
}

void Employee::setName(const string& newName) {
    if (newName.empty()) throw InvalidInputException("Ten nhan vien khong duoc de trong");
    name = newName;
}

void Employee::setPhone(const string& newPhone) {
    if (newPhone.empty()) throw InvalidInputException("So dien thoai khong duoc de trong");
    phone = newPhone;
}

void Employee::setRole(EmployeeRole newRole) { role = newRole; }

void Employee::display() const {
    cout << left << setw(4) << id << setw(20) << name << setw(15) << phone << setw(12) << roleToString(role);
}

string Employee::toFileString() const {
    return to_string(id) + "|" + name + "|" + phone + "|" + roleToString(role);
}


// ==== FULLTIME EMPLOYEE ====
FulltimeEmployee::FulltimeEmployee(int id, const string& name, const string& phone, 
                                   EmployeeRole role, double monthlySalary)
    : Employee(id, name, phone, role) {
    if (monthlySalary < 0) throw InvalidInputException("Luong khong duoc am");
    this->monthlySalary = monthlySalary;
}

void FulltimeEmployee::setMonthlySalary(double newSalary) {
    if (newSalary < 0) throw InvalidInputException("Luong khong duoc am");
    monthlySalary = newSalary;
}

double FulltimeEmployee::calculateSalary() const {
    return monthlySalary;
}

void FulltimeEmployee::display() const {
    Employee::display();
    cout << right << setw(12) << "Fulltime" 
         << setw(16) << fixed << setprecision(0) << calculateSalary() << " VND" << endl;
}

string FulltimeEmployee::toFileString() const {
    return "FULLTIME|" + Employee::toFileString() + "|" + to_string(monthlySalary);
}


// ==== PARTTIME EMPLOYEE ====
ParttimeEmployee::ParttimeEmployee(int id, const string& name, const string& phone, 
                                   EmployeeRole role, double hourlyWage, double hoursWorked)
    : Employee(id, name, phone, role) {
    if (hourlyWage < 0) throw InvalidInputException("Theo gio khong duoc am");
    if (hoursWorked < 0) throw InvalidInputException("So gio lam khong duoc am");
    this->hourlyWage = hourlyWage;
    this->hoursWorked = hoursWorked;
}

void ParttimeEmployee::setHourlyWage(double newWage) {
    if (newWage < 0) throw InvalidInputException("Luong khong duoc am");
    hourlyWage = newWage;
}

void ParttimeEmployee::addHours(double hours) {
    if (hours < 0) throw InvalidInputException("Gio cong them khong duoc am");
    hoursWorked += hours;
}

void ParttimeEmployee::resetHours() {
    hoursWorked = 0;
}

double ParttimeEmployee::calculateSalary() const {
    // 1 ca la 8h binh thuong. Neu lam hon 8h thi so gio duoc nhan 1.5
    if (hoursWorked <= 8.0) {
        return hoursWorked * hourlyWage;
    } else {
        double normalPay = 8.0 * hourlyWage;
        double overtimePay = (hoursWorked - 8.0) * (hourlyWage * 1.5);
        return normalPay + overtimePay;
    }
}

void ParttimeEmployee::display() const {
    Employee::display();
    cout << right << setw(12) << "Parttime" 
         << setw(16) << fixed << setprecision(0) << calculateSalary() << " VND (" << hoursWorked << "h)" << endl;
}

string ParttimeEmployee::toFileString() const {
    return "PARTTIME|" + Employee::toFileString() + "|" + to_string(hourlyWage) + "|" + to_string(hoursWorked);
}
