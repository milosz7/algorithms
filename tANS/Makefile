CXX := g++
CXXFLAGS := -Wall -Wextra -O3 -pedantic
LDFLAGS :=

HEADERS := $(wildcard *.hpp)
TAR_FNAME := Milosz_Bargiel_Zestaw01.tar.gz
TO_COMPRESS := $(filter-out $(wildcard *.[o|x]), $(wildcard *))

.PHONY: all clean tar
all: Stack.x Generator.x ONP.x

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.x: %.o
	$(CXX) $(LDFLAGS) -o $@ $^

main.x: tANS.hpp tANS.cpp

clean:
	$(RM) $(wildcard *.[o|x])

tar:
	make clean
	tar -cvzf ../$(TAR_FNAME) $(TO_COMPRESS)
