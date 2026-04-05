#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
#include "Exceptions.h"
using namespace std;

// Enum loai san pham
enum class ProductType {
    COFFEE,   // Ca phe
    TEA,      // Tra
    JUICE,    // Nuoc ep
    OTHER     // Khac
};

string productTypeToString(ProductType type);
ProductType stringToProductType(const string& str);

class Product {
private:
    int     id;
    string  name;
    double  sellingPrice;
    double  costPrice;
    ProductType type;

public:
    // Constructor
    Product(int id, const string& name, double sellingPrice, double costPrice, ProductType type);

    // Getter
    int         getId()           const { return id; }
    string      getName()         const { return name; }
    double      getSellingPrice() const { return sellingPrice; }
    double      getCostPrice()    const { return costPrice; }
    ProductType getType()         const { return type; }

    // Setter co kiem tra du lieu - throw neu sai
    void setName(const string& newName);
    void setSellingPrice(double newPrice);
    void setCostPrice(double newCost);
    void setType(ProductType newType);

    // Hien thi thong tin san pham
    void display() const;

    // Xuat ra string de luu file
    string toFileString() const;
};

#endif
