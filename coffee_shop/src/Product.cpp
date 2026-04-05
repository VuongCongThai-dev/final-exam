#include "../include/Product.h"
#include <iomanip>
using namespace std;

string productTypeToString(ProductType type) {
    switch (type) {
        case ProductType::COFFEE: return "Ca phe";
        case ProductType::TEA:    return "Tra";
        case ProductType::JUICE:  return "Nuoc ep";
        default:                  return "Khac";
    }
}

ProductType stringToProductType(const string& str) {
    if (str == "Ca phe")  return ProductType::COFFEE;
    if (str == "Tra")     return ProductType::TEA;
    if (str == "Nuoc ep") return ProductType::JUICE;
    return ProductType::OTHER;
}

Product::Product(int id, const string& name, double sellingPrice, double costPrice, ProductType type) {
    if (name.empty())
        throw InvalidInputException("Ten san pham khong duoc de trong");
    if (sellingPrice <= 0)
        throw InvalidInputException("Gia ban san pham phai lon hon 0");
    if (costPrice < 0)
        throw InvalidInputException("Gia von khong duoc am");

    this->id    = id;
    this->name  = name;
    this->sellingPrice = sellingPrice;
    this->costPrice = costPrice;
    this->type  = type;
}

void Product::setName(const string& newName) {
    if (newName.empty())
        throw InvalidInputException("Ten san pham khong duoc de trong");
    name = newName;
}

void Product::setSellingPrice(double newPrice) {
    if (newPrice <= 0)
        throw InvalidInputException("Gia ban san pham phai lon hon 0");
    sellingPrice = newPrice;
}

void Product::setCostPrice(double newCost) {
    if (newCost < 0)
        throw InvalidInputException("Gia von khong duoc am");
    costPrice = newCost;
}

void Product::setType(ProductType newType) {
    type = newType;
}

void Product::display() const {
    cout << left
         << setw(4)  << id
         << setw(20) << name
         << setw(12) << productTypeToString(type)
         << right << setw(10) << fixed << setprecision(0) << costPrice << " VND (VON)"
         << right << setw(10) << fixed << setprecision(0) << sellingPrice << " VND (BAN)"
         << endl;
}

string Product::toFileString() const {
    return to_string(id) + "|" + name + "|" + to_string(sellingPrice) + "|" + to_string(costPrice) + "|" + productTypeToString(type);
}
