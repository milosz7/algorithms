#pragma once
#include <iostream>
#include <stdexcept>

class setArr {
const int universeSize = 100;
bool* table;
int size = 0;
bool checkRangeCorrectness(int x);
public:
	setArr();
	~setArr();
	void insert(int x);
	void withdraw(int x);
	bool isInSet(int i);
	int getSize();
	void clearSet();
	void printSet();
	setArr operator+(setArr& other);
	setArr operator*(setArr& other);
	setArr operator-(setArr& other);
	bool operator==(setArr& other);
	bool operator<=(setArr& other);
};
