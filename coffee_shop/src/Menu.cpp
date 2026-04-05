#include "../include/Menu.h"
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

Menu::Menu() : nextId(1) {}

void Menu::addProduct(const string& name, double sellingPrice, double costPrice, ProductType type) {
    for (const auto& p : products) {
        if (p.getName() == name)
            throw InvalidInputException("San pham '" + name + "' da ton tai trong menu");
    }
    products.push_back(Product(nextId++, name, sellingPrice, costPrice, type));
    cout << "=> Da them san pham: " << name << endl;
}

void Menu::removeProduct(const string& name) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getName() == name) {
            products.erase(it);
            cout << "=> Da xoa san pham: " << name << endl;
            return;
        }
    }
    throw ProductNotFoundException(name);
}

void Menu::updatePrice(const string& name, double newSellingPrice, double newCostPrice) {
    if (newSellingPrice <= 0 || newCostPrice < 0)
        throw InvalidInputException("Gia ban hoac gia von khong hop le");

    for (auto& p : products) {
        if (p.getName() == name) {
            p.setSellingPrice(newSellingPrice);
            p.setCostPrice(newCostPrice);
            cout << "=> Da cap nhat gia: " << name << endl;
            return;
        }
    }
    throw ProductNotFoundException(name);
}

Product Menu::findProduct(const string& name) const {
    for (const auto& p : products) {
        if (p.getName() == name)
            return p;
    }
    throw ProductNotFoundException(name);
}

vector<Product> Menu::getByType(ProductType type) const {
    vector<Product> result;
    for (const auto& p : products) {
        if (p.getType() == type)
            result.push_back(p);
    }
    return result;
}

void Menu::display() const {
    cout << "\n====== THUC DON ======\n";
    cout << left << setw(4) << "ID" << setw(20) << "Ten" << setw(12) << "Loai"
         << right << setw(12) << "Gia Von" << right << setw(12) << "Gia Ban" << endl;
    cout << string(60, '-') << endl;

    if (products.empty()) {
        cout << "(Chua co san pham nao)\n";
    } else {
        for (const auto& p : products) {
            p.display();
        }
    }
    cout << "======================\n";
}

void Menu::displayByType(ProductType type) const {
    cout << "\n=== " << productTypeToString(type) << " ===\n";
    bool found = false;
    for (const auto& p : products) {
        if (p.getType() == type) {
            p.display();
            found = true;
        }
    }
    if (!found)
        cout << "(Khong co san pham) \n";
}

void Menu::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open())
        throw FileException(filename);

    for (const auto& p : products) {
        file << p.toFileString() << "\n";
    }
    file.close();
}

void Menu::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open())
        throw FileException(filename);

    products.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, name, sellingPriceStr, costPriceStr, typeStr;
        getline(ss, idStr,   '|');
        getline(ss, name,    '|');
        getline(ss, sellingPriceStr,'|');
        getline(ss, costPriceStr,'|');
        getline(ss, typeStr, '|');

        int    id    = stoi(idStr);
        double sellingPrice = stod(sellingPriceStr);
        double costPrice = stod(costPriceStr);
        ProductType type = stringToProductType(typeStr);

        products.push_back(Product(id, name, sellingPrice, costPrice, type));
        if (id >= nextId) nextId = id + 1;
    }
    file.close();
}
