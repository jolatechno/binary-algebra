COMPILER=g++ -std=c++0x
LINKER=ar
LOCALLIBS = $(wildcard binary_arithmetic/*.cpp) $(wildcard binary_arithmetic/**/*.cpp)
LDLIBS=-fopenmp

TARGETS=unit_testing.out example.out

.PHONY: all test clean

all: unit_testing.out example.out performance_testing.out


#run directive


test:	unit_testing.out
	./unit_testing/test.out

performance_testing: performance_testing.out
	./performance_testing/test.out


#compile directive


unit_testing.out: lib.a
	$(COMPILER) unit_testing/test.cpp lib/lib.a -o unit_testing/test.out $(LDLIBS)

performance_testing.out: lib.a
	$(COMPILER) performance_testing/test.cpp lib/lib.a -o performance_testing/test.out $(LDLIBS)

example.out: lib.a
	$(COMPILER) examples/example.cpp lib/lib.a -o examples/example.out $(LDLIBS)


#linker


lib.a: binary_arithmetic.o utils.o reference_arithmetic.o
	$(LINKER) -crs lib/lib.a lib/binary_arithmetic.o lib/utils.o lib/reference_arithmetic.o


#library.o


binary_arithmetic.o:
	$(COMPILER) -c binary_arithmetic/binary_arithmetic.cpp -o lib/binary_arithmetic.o $(LDLIBS)

utils.o:
	$(COMPILER) -c binary_arithmetic/utils/utils.cpp -o lib/utils.o $(LDLIBS)

reference_arithmetic.o:
	$(COMPILER) -c binary_arithmetic/reference_arithmetic/reference_arithmetic.cpp -o lib/reference_arithmetic.o $(LDLIBS)


#clean


clean:
	$(RM) **/*.out lib/*.a lib/*.o
