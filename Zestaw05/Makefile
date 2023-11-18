CXX := g++
CXXFLAGS := -Wall -Wextra -O3 -pedantic
LDFLAGS :=

TAR_FNAME := Milosz_Bargiel_Zestaw05.tar.gz
TO_COMPRESS := $(filter-out $(wildcard *.[o|x]), $(wildcard *))

.PHONY: all clean tar
all: BubbleSort.x SelectionSort.x InsertionSort.x Generator.x

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.x: %.o
	$(CXX) $(LDFLAGS) -o $@ $^

SelectionSort.x: SelectionSort.hpp

BubbleSort.x: BubbleSort.hpp

InsertionSort.x: InsertionSort.hpp

clean:
	$(RM) $(wildcard *.[o|x])

tar:
	make clean
	tar -cvzf ../$(TAR_FNAME) $(TO_COMPRESS)
