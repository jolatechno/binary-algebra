COMPILER=g++
LINKER=ar
LOCALLIBS = $(wildcard binary_arithmetic/*.cpp) $(wildcard binary_arithmetic/**/*.cpp)
LDLIBS=-fopenmp

TARGETS=unit_testing.out example.out

.PHONY: all test clean

all: unit_testing example.out

unit_testing.out: link
	$(COMPILER) unit_testing/test.cpp lib.a -o unit_testing.out $(LDLIBS)

example.out: link
	$(COMPILER) example.cpp lib.a -o example.out $(LDLIBS)

test:	unit_testing.out
	./unit_testing.out

clean:
	$(RM) *.out *.a *.o

link: binary_arithmetic.o utils.o reference_arithmetic.o
	$(LINKER) -crs lib.a binary_arithmetic.o utils.o reference_arithmetic.o

binary_arithmetic.o:
	$(COMPILER) -c binary_arithmetic/binary_arithmetic.cpp $(LDLIBS)

utils.o:
	$(COMPILER) -c binary_arithmetic/utils/utils.cpp $(LDLIBS)

reference_arithmetic.o:
	$(COMPILER) -c binary_arithmetic/reference_arithmetic/reference_arithmetic.cpp $(LDLIBS)
