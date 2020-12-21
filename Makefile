COMPILER=g++ -std=c++0x
LINKER=ar
LOCALLIBS = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
LDLIBS=
CCFLAGS=

.PHONY: all test clean

all: unit_testing.out example.out performance_testing.out

#parameter directive


gpu: openmp
	$(eval CCFLAGS+=-DTARGET=1)
	$(eval LDLIBS+=-fno-stack-protector -fcf-protection=none -foffload=nvptx-none)

openmp:
	$(eval LDLIBS+=-fopenmp)


#run directive


test:	unit_testing.out
	./unit_testing/test.out

performance_testing: performance_testing.out
	./performance_testing/test.out


#compile directive


unit_testing.out: lib.a
	$(COMPILER) $(CCFLAGS) unit_testing/test.cpp lib/lib.a -o unit_testing/test.out $(LDLIBS)

performance_testing.out: lib.a
	$(COMPILER) $(CCFLAGS) performance_testing/test.cpp lib/lib.a -o performance_testing/test.out $(LDLIBS)

example.out: lib.a
	$(COMPILER) $(CCFLAGS) examples/example.cpp lib/lib.a -o examples/example.out $(LDLIBS)


#linker


lib.a: binary_arithmetic.o utils.o reference_arithmetic.o
	$(LINKER) -crs lib/lib.a lib/binary_arithmetic.o lib/utils.o lib/reference_arithmetic.o


#library.o


binary_arithmetic.o:
	$(COMPILER) $(CCFLAGS) -c src/binary_arithmetic.cpp -o lib/binary_arithmetic.o $(LDLIBS)

utils.o:
	$(COMPILER) $(CCFLAGS) -c src/utils/utils.cpp -o lib/utils.o $(LDLIBS)

reference_arithmetic.o:
	$(COMPILER) $(CCFLAGS) -c src/reference_arithmetic/reference_arithmetic.cpp -o lib/reference_arithmetic.o $(LDLIBS)


#clean


clean:
	$(RM) **/*.out lib/*.a lib/*.o
