CXX := g++
CXXFLAGS := -Wall -Wextra -O3 -pedantic
LDFLAGS :=

HEADERS := $(wildcard *.hpp)
TAR_FNAME := Milosz_Bargiel_Zestaw04.tar.gz
TO_COMPRESS := $(filter-out $(wildcard *.[o|x]), $(wildcard *))

.PHONY: all clean tar
all: ArrayList.x CursorList.x

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.x: %.o
	$(CXX) $(LDFLAGS) -o $@ $^

Generator.x: Generator.o

ArrayList.x: $(HEADERS)

CursorList.x: $(HEADERS)

clean:
	$(RM) $(wildcard *.[o|x])

tar:
	make clean
	tar -cvzf ../$(TAR_FNAME) $(TO_COMPRESS)
