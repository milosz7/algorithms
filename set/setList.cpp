#include "setList.h"

int setList::getSize() { return vec.size(); }

void setList::printSet() {   
    std::cout << "{ ";
    for (auto it = vec.begin(); it != vec.end(); it++)
            std::cout << *it << " ";
    std::cout << "}";
}

void setList::insert(int x) {
    if (!isInSet(x))
        vec.push_back(x);
    else
        std::cerr << "Element: " << x << " already in the set!\n";
}

void setList::withdraw(int x) {
    int current_size = vec.size();
    vec.remove(x);
    if (current_size == vec.size())
        std::cerr << "Element: " << x << " not in the set!\n";
}

bool setList::isInSet(int x) {
    for (int elem : vec)
        if (elem == x) return true;
    return false;
}

void setList::clearSet() { vec.clear(); }

setList setList::operator+(setList& other) {
    setList out = setList();
    for (int elem : vec)
        out.insert(elem);
    for (int elem : other.vec)
        if (!out.isInSet(elem))
            out.insert(elem);
    return out;
}  

setList setList::operator*(setList& other) {
    setList out = setList();
    for (int elem : vec)
        if (other.isInSet(elem))
            out.insert(elem);
    return out;
}  

setList setList::operator-(setList& other) {
    setList out = setList();
    for (int elem : vec)
        if (!other.isInSet(elem))
            out.insert(elem);
    return out;
}

bool setList::operator<=(setList& other) {
    for (int elem : vec)
        if (!other.isInSet(elem)) return false;
    return true;
}

bool setList::operator==(setList& other) {
    if (getSize() != other.getSize()) return false;
    for (int elem : vec)
        if (!other.isInSet(elem)) return false;
    return true;
} 
