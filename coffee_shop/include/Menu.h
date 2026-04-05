#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include "Product.h"
#include "Exceptions.h"
using namespace std;

class Menu {
private:
    vector<Product> products;
    int             nextId;

public:
    Menu();

    void addProduct(const string& name, double sellingPrice, double costPrice, ProductType type);
    void removeProduct(const string& name);
    void updatePrice(const string& name, double newSellingPrice, double newCostPrice);
    Product findProduct(const string& name) const;
    vector<Product> getByType(ProductType type) const;
    const vector<Product>& getAllProducts() const { return products; }

    void display() const;
    void displayByType(ProductType type) const;

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
};

#endif
