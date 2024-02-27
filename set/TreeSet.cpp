#include "TreeSet.h"

int TreeSet::getSize() { return tree.size(); }

void TreeSet::printSet() {
    std::cout << "{ ";
    tree.inorder();
    std::cout << "}";
}

void TreeSet::insert(int x) {
    if (tree.search(x) == nullptr)
        tree.insert(x);
}

void TreeSet::withdraw(int x) {
    Node* to_remove = tree.search(x);
    if (to_remove == nullptr)
        std::cout << "Element: " << x << " is not in the set!\n";
    else 
        tree.remove(to_remove);
}

bool TreeSet::isInSet(int x) { return tree.search(x) != nullptr; }

void TreeSet::clearSet() { tree.clear(); }

TreeSet TreeSet::operator+(TreeSet& other) {
    TreeSet out = TreeSet();
    Node* current = tree.getRoot();
    std::function<void(Node*)> add = [&](Node* current) {
        if (current != nullptr) {
            int value = current->value;
            add(current->left);
            add(current->right);
            if (!out.isInSet(value))
                out.insert(value);
        }
    };
    add(current);
    current = other.tree.getRoot();
    add(current);
    return out;
}

TreeSet TreeSet::operator*(TreeSet& other) {
    TreeSet out = TreeSet();
    Node* current = tree.getRoot();
    std::function<void(Node*)> intersect = [&](Node* current) {
        if (current != nullptr) {
            int value = current->value;
            intersect(current->left);
            intersect(current->right);
            if (other.isInSet(value))
                out.insert(value);
        }
    };
    intersect(current);
    return out;
}

TreeSet TreeSet::operator-(TreeSet& other) {
    TreeSet out = TreeSet();
    Node* current = tree.getRoot();
    std::function<void(Node*)> difference = [&](Node* current) {
        if (current != nullptr) {
            int value = current->value;
            difference(current->left);
            difference(current->right);
            if (!other.isInSet(value))
                out.insert(value);
        }
    };
    difference(current);
    return out;
}

bool TreeSet::operator==(TreeSet& other) {
    if (getSize() != other.getSize()) return false;
    Node *current = tree.getRoot();
    bool are_equal = true;
    std::function<void(Node*)> equal = [&](Node *current) {
        if (current != nullptr && are_equal) {
            int value = current->value;
            if (!other.isInSet(value)) are_equal = false;
            equal(current->left);
            equal(current->right);
        }
    };
    equal(current);
    return are_equal;
}

bool TreeSet::operator<=(TreeSet& other) {
    Node *current = tree.getRoot();
    bool includes = true;
    std::function<void(Node*)> inclusion = [&](Node *current) {
        if (current != nullptr && includes) {
            int value = current->value;
            if (!other.isInSet(value)) includes = false;
            inclusion(current->left);
            inclusion(current->right);
        }
    };
    inclusion(current);
    return includes;
}