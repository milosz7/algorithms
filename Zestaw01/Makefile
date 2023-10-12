CXX := g++
CXXFLAGS := -Wall -Wextra -O3 -pedantic
LDFLAGS :=

HEADERS := $(wildcard *.hpp)
NAMES := $(patsubst %.cpp,%,$(wildcard *.cpp))
OBJS := $(patsubst %,%.o,$(NAMES))

EX_4_FILENAME := Generator.cpp
EX_5_FILENAME := ONP.cpp


.PHONY: all clean
all: Stack.x Generator.x ONP.x

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.x: %.o
	$(CXX) $(LDFLAGS) -o $@ $^

Generator.x: Generator.o $(HEADERS)

Stack.x: ArrayStack.o LinkedStack.o $(HEADERS) 

ONP.x: $(HEADERS)

main.x: main.o LinkedStack.o TemplateStack.o LinkedStack.hpp TemplateStack.hpp

clean:
	$(RM) $(wildcard *.[o|x])
