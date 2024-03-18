#include "setArr.h"

setArr::setArr() { table = new bool[universeSize + 1]; }

setArr::~setArr() { delete table; }

void setArr::insert(int x) { 
    if (!checkRangeCorrectness(x))
        throw std::out_of_range("Index out of bounds!");
    if (!isInSet(x)) {
        table[x] = true; 
        size++;
    } else {
        std::cerr << "Element: " << x << " already in the set." << std::endl;
    }
    
}

void setArr::withdraw(int x) {
    if (!checkRangeCorrectness(x))
        throw std::out_of_range("Index out of bounds!");

    if (!table[x])
        std::cerr << "Element: " << x << " not in the set." << std::endl;
    else {
        table[x] = false;
        size--;
    }
}

bool setArr::isInSet(int x) { 
    if (!checkRangeCorrectness(x))
        throw std::out_of_range("Index out of bounds!");

    return table[x]; 
}

int setArr::getSize() { return size; }

void setArr::clearSet() {
    delete table;
    table = new bool[universeSize + 1];
    size = 0;
}

void setArr::printSet() {
    std::cout << "{ ";
    for (int i = 0; i < universeSize + 1; i++)
        if (table[i])
            std::cout << i << " ";
    std::cout << "}";
}

setArr setArr::operator+(setArr &other) {
    setArr out = setArr();
    for (int i = 0; i < universeSize + 1; i++)
        if (table[i] || other.table[i])
            out.insert(i);
    return out;
}

setArr setArr::operator*(setArr &other) {
    setArr out = setArr();
    for (int i = 0; i < universeSize + 1; i++)
        if (table[i] && other.table[i])
            out.insert(i);
    return out;
}

setArr setArr::operator-(setArr &other) {
    setArr out = setArr();
    for (int i = 0; i < universeSize + 1; i++)
        if (!(table[i] && other.table[i]) && table[i])
            out.insert(i);
    return out;
}

bool setArr::operator==(setArr &other) {
    for (int i = 0; i < universeSize + 1; i++)
        if (table[i] != other.table[i])
            return false;
    return true;
}

bool setArr::operator<=(setArr &other) {
    for (int i = 0; i < universeSize + 1; i++)
        if (table[i] && !other.table[i])
            return false;
    return true;
}

bool setArr::checkRangeCorrectness(int x) {
    if (x > universeSize) 
        return false;
    return true;
}
