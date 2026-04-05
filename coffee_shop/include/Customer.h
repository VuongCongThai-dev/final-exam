#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
#include "Exceptions.h"
using namespace std;

class Customer {
private:
    int    id;
    string name;
    string phone;
    int    points; // Diem tich luy

public:
    // Constructor
    Customer(int id, const string& name, const string& phone);

    // Getter
    int    getId()     const { return id; }
    string getName()   const { return name; }
    string getPhone()  const { return phone; }
    int    getPoints() const { return points; }

    // Setter co kiem tra - throw neu sai
    void setName(const string& newName);
    void setPhone(const string& newPhone);

    // Them diem tich luy
    void addPoints(int amount);

    // Hien thi thong tin
    void display() const;

    // Xuat ra string de luu file
    string toFileString() const;
};

#endif
