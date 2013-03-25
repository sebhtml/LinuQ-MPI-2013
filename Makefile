MPICXX=mpicxx
CXXFLAGS=-std=c++98

all: Programme1 Programme1-Iprobe test-MPI-IO

test-MPI-IO: test-MPI-IO.cpp
	$(MPICXX) -showme
	$(MPICXX) -std=c++98 test-MPI-IO.cpp -o test-MPI-IO

Programme1: Programme1.cpp
	$(MPICXX) -std=c++98 Programme1.cpp -o Programme1

Programme1-Iprobe: Programme1-Iprobe.cpp
	$(MPICXX) -Wall -std=c++98 Programme1-Iprobe.cpp -o Programme1-Iprobe

test: Programme1
	mpiexec -n 24 ./Programme1

edit:
	vim Programme1.cpp
