U_CXX=$(CXX) -std=c++0x
U_LDLIBS=$(LDLIBS)
U_CCFLAGS=$(CCFLAGS)
CRUN=
AMDGPU=
LINKER=ar

.PHONY: all test clean

all: unit_testing.out example.out performance_testing.out

#parameter directive


mpi:
	$(eval U_CCFLAGS+=-DMPIENABLED=1)
	$(eval U_CXX=mpic++ -std=c++0x)
	$(eval CRUN=mpirun)

openmp:
	$(eval U_LDLIBS+=-fopenmp)

gpu-nvidia: openmp
	$(eval U_CCFLAGS+=-DTARGET=1)
	$(eval U_CCFLAGS+=-fno-stack-protector -foffload=nvptx-none)

gpu-amd:	openmp g++-10
	$(eval U_CCFLAGS+=-DTARGET=1)
	$(eval U_CCFLAGS+=-fno-stack-protector -foffload=amdgcn-amdhsa="-march=$(AMDGPU)")

g++-10:
	$(eval U_CXX=g++-10 -std=c++0x)

protection-none:
	$(eval U_CCFLAGS+=-fcf-protection=none)

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
	$(U_CXX) $(U_CCFLAGS) unit_testing/test.cpp lib/lib.a -o unit_testing/test.out $(U_LDLIBS)

performance_testing.out: lib.a
	$(U_CXX) $(U_CCFLAGS) performance_testing/test.cpp lib/lib.a -o performance_testing/test.out $(U_LDLIBS)

example.out: lib.a
	$(U_CXX) $(U_CCFLAGS) examples/example.cpp lib/lib.a -o examples/example.out $(U_LDLIBS)


#linker


lib.a: binary_arithmetic.o utils.o reference_arithmetic.o
	$(LINKER) -crs lib/lib.a lib/binary_arithmetic.o lib/utils.o lib/reference_arithmetic.o


#library.o


binary_arithmetic.o:
	$(U_CXX) $(U_CCFLAGS) -c src/binary_arithmetic.cpp -o lib/binary_arithmetic.o $(U_LDLIBS)

utils.o:
	$(U_CXX) $(U_CCFLAGS) -c src/utils/utils.cpp -o lib/utils.o $(U_LDLIBS)

reference_arithmetic.o:
	$(U_CXX) $(U_CCFLAGS) -c src/reference_arithmetic/reference_arithmetic.cpp -o lib/reference_arithmetic.o $(U_LDLIBS)


#clean


clean:
	$(RM) **/*.out lib/*.a lib/*.o
