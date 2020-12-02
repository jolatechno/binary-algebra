COMPILER=g++
LOCALLIBS = $(wildcard binary_arithmetic/*.cpp) $(wildcard binary_arithmetic/**/*.cpp)
LDLIBS=-fopenmp

TARGETS=unit_testing.out example.out

all: $(TARGETS) test

example.out:
	$(COMPILER) $(LOCALLIBS) -o example.out example.cpp $(LDLIBS)

unit_testing.out:
	$(COMPILER) $(LOCALLIBS) -o unit_testing.out unit_testing/test.cpp $(LDLIBS)

test:	unit_testing.out
	./unit_testing.out

clean:
	$(RM) $(TARGETS)
