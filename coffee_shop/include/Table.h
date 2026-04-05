#ifndef TABLE_H
#define TABLE_H

#include <iostream>

class Table {
private:
    int id;
    int capacity;
    int currentOccupancy;
    bool isShared;

public:
    Table(int id, int capacity, bool isShared = false) 
        : id(id), capacity(capacity), currentOccupancy(0), isShared(isShared) {}

    int getId() const { return id; }
    int getCapacity() const { return capacity; }
    int getCurrentOccupancy() const { return currentOccupancy; }
    bool getIsShared() const { return isShared; }

    bool hasSpace(int people) const {
        return (capacity - currentOccupancy) >= people;
    }

    bool isEmpty() const {
        return currentOccupancy == 0;
    }

    void assignPeople(int people) {
        currentOccupancy += people;
    }

    void clearTable() {
        currentOccupancy = 0;
    }
};

#endif
