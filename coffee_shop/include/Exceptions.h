#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
using namespace std;

// Exception co ban cho toan bo he thong
class CoffeeShopException : public exception {
protected:
    string message;
public:
    CoffeeShopException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Exception khi khong tim thay san pham
class ProductNotFoundException : public CoffeeShopException {
public:
    ProductNotFoundException(const string& name)
        : CoffeeShopException("Khong tim thay san pham: " + name) {}
};

// Exception khi gia tri nhap vao khong hop le
class InvalidInputException : public CoffeeShopException {
public:
    InvalidInputException(const string& field)
        : CoffeeShopException("Du lieu khong hop le: " + field) {}
};

// Exception khi don hang trong
class EmptyOrderException : public CoffeeShopException {
public:
    EmptyOrderException()
        : CoffeeShopException("Don hang trong, vui long them san pham truoc!") {}
};

// Exception khi khong tim thay khach hang
class CustomerNotFoundException : public CoffeeShopException {
public:
    CustomerNotFoundException(const string& name)
        : CoffeeShopException("Khong tim thay khach hang: " + name) {}
};

// Exception khi khong tim thay nhan vien
class EmployeeNotFoundException : public CoffeeShopException {
public:
    EmployeeNotFoundException(const string& name)
        : CoffeeShopException("Khong tim thay nhan vien: " + name) {}
};

// Exception loi doc/ghi file
class FileException : public CoffeeShopException {
public:
    FileException(const string& filename)
        : CoffeeShopException("Loi mo file: " + filename) {}
};

#endif
