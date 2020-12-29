CXX+=-std=c++0x
LINKER=ar
LDLIBS=
CCFLAGS=
CRUN=
AMDGPU=

.PHONY: all test clean

all: unit_testing.out example.out performance_testing.out

#parameter directive


mpi:
	$(eval CCFLAGS+=-DMPIENABLED=1)
	$(eval CXX=mpic++ -std=c++0x)
	$(eval CRUN=mpirun)

openmp:
	$(eval LDLIBS+=-fopenmp)

gpu-nvidia: openmp
	$(eval CCFLAGS+=-DTARGET=1)
	$(eval LDLIBS+=-fno-stack-protector -foffload=nvptx-none)

gpu-amd:	openmp
	$(eval CCFLAGS+=-DTARGET=1)
	$(eval LDLIBS+=-fno-stack-protector -foffload=amdgcn-amdhsa=\"$(AMDGPU)\")

fiji:
	$(eval AMDGPU=fiji)

vega10:
	$(eval AMDGPU=gfx900)

vega20:
	$(eval AMDGPU=gfx906)


#run directive


test:	unit_testing.out
	$(CRUN) ./unit_testing/test.out

performance_testing: performance_testing.out
	$(CRUN) ./performance_testing/test.out


#compile directive


unit_testing.out: lib.a
	$(CXX) $(CCFLAGS) unit_testing/test.cpp lib/lib.a -o unit_testing/test.out $(LDLIBS)

performance_testing.out: lib.a
	$(CXX) $(CCFLAGS) performance_testing/test.cpp lib/lib.a -o performance_testing/test.out $(LDLIBS)

example.out: lib.a
	$(CXX) $(CCFLAGS) examples/example.cpp lib/lib.a -o examples/example.out $(LDLIBS)


#linker


lib.a: binary_arithmetic.o utils.o reference_arithmetic.o
	$(LINKER) -crs lib/lib.a lib/binary_arithmetic.o lib/utils.o lib/reference_arithmetic.o


#library.o


binary_arithmetic.o:
	$(CXX) $(CCFLAGS) -c src/binary_arithmetic.cpp -o lib/binary_arithmetic.o $(LDLIBS)

utils.o:
	$(CXX) $(CCFLAGS) -c src/utils/utils.cpp -o lib/utils.o $(LDLIBS)

reference_arithmetic.o:
	$(CXX) $(CCFLAGS) -c src/reference_arithmetic/reference_arithmetic.cpp -o lib/reference_arithmetic.o $(LDLIBS)


#clean


clean:
	$(RM) **/*.out lib/*.a lib/*.o
