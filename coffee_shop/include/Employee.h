#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>
#include "Exceptions.h"
using namespace std;

enum class EmployeeRole {
    MANAGER,
    STAFF
};

enum class EmployeeType {
    FULLTIME,
    PARTTIME
};

string roleToString(EmployeeRole role);
EmployeeRole stringToRole(const string& str);

class Employee {
protected:
    int          id;
    string       name;
    string       phone;
    EmployeeRole role;

public:
    Employee(int id, const string& name, const string& phone, EmployeeRole role);
    virtual ~Employee() {}

    int          getId()     const { return id; }
    string       getName()   const { return name; }
    string       getPhone()  const { return phone; }
    EmployeeRole getRole()   const { return role; }

    void setName(const string& newName);
    void setPhone(const string& newPhone);
    void setRole(EmployeeRole newRole);

    virtual EmployeeType getType() const = 0;
    virtual double calculateSalary() const = 0;
    virtual void display() const;
    virtual string toFileString() const;
};

class FulltimeEmployee : public Employee {
private:
    double monthlySalary;

public:
    FulltimeEmployee(int id, const string& name, const string& phone, 
                     EmployeeRole role, double monthlySalary);

    double getMonthlySalary() const { return monthlySalary; }
    void setMonthlySalary(double newSalary);

    EmployeeType getType() const override { return EmployeeType::FULLTIME; }
    double calculateSalary() const override;
    void display() const override;
    string toFileString() const override;
};

class ParttimeEmployee : public Employee {
private:
    double hourlyWage;
    double hoursWorked;

public:
    ParttimeEmployee(int id, const string& name, const string& phone, 
                     EmployeeRole role, double hourlyWage, double hoursWorked = 0);

    double getHourlyWage() const { return hourlyWage; }
    double getHoursWorked() const { return hoursWorked; }

    void setHourlyWage(double newWage);
    void addHours(double hours);
    void resetHours();

    EmployeeType getType() const override { return EmployeeType::PARTTIME; }
    double calculateSalary() const override;
    void display() const override;
    string toFileString() const override;
};

#endif
