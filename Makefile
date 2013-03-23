all: Programme1 Programme1-Iprobe

Programme1: Programme1.cpp
	mpicxx -std=c++98 Programme1.cpp -o Programme1

Programme1-Iprobe: Programme1-Iprobe.cpp
	mpicxx -Wall -std=c++98 Programme1-Iprobe.cpp -o Programme1-Iprobe

test: Programme1
	mpiexec -n 24 ./Programme1

edit:
	vim Programme1.cpp
