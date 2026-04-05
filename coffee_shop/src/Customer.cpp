#include "../include/Customer.h"
#include <iomanip>
using namespace std;

// Constructor - kiem tra ngay khi khoi tao
Customer::Customer(int id, const string& name, const string& phone) {
    if (name.empty())
        throw InvalidInputException("Ten khach hang khong duoc de trong");
    if (phone.empty())
        throw InvalidInputException("So dien thoai khong duoc de trong");

    // Kiem tra so dien thoai chi chua so
    for (char c : phone) {
        if (!isdigit(c))
            throw InvalidInputException("So dien thoai chi duoc chua so");
    }

    this->id     = id;
    this->name   = name;
    this->phone  = phone;
    this->points = 0;
}

void Customer::setName(const string& newName) {
    if (newName.empty())
        throw InvalidInputException("Ten khach hang khong duoc de trong");
    name = newName;
}

void Customer::setPhone(const string& newPhone) {
    if (newPhone.empty())
        throw InvalidInputException("So dien thoai khong duoc de trong");
    for (char c : newPhone) {
        if (!isdigit(c))
            throw InvalidInputException("So dien thoai chi duoc chua so");
    }
    phone = newPhone;
}

// Them diem - throw neu so am
void Customer::addPoints(int amount) {
    if (amount < 0)
        throw InvalidInputException("Diem tich luy khong duoc am");
    points += amount;
}

void Customer::display() const {
    cout << left
         << setw(4)  << id
         << setw(20) << name
         << setw(15) << phone
         << right << setw(8) << points << " diem"
         << endl;
}

string Customer::toFileString() const {
    return to_string(id) + "|" + name + "|" + phone + "|" + to_string(points);
}
