#include <mpi.h>
#include <stdint.h>
#include <iostream>
using namespace std;

int main(int argc, char**argv){

	MPI_Init(&argc, &argv);

	int rank;
	int size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	cout << "Je suis le numéro # " << rank << " parmi " << size << endl;

	uint64_t i=0;
	i--;
	//while(i--){}

	int destination = ( rank + 1 ) % size;
	int TAG_BONJOUR = 0;
	MPI_Request request;

	// envoyer un message au suivant
	MPI_Isend(NULL, 0, MPI_BYTE, destination, TAG_BONJOUR,
		MPI_COMM_WORLD, &request);

	cout << rank << " a envoyé un message à " << destination << endl;

	// recevoir le message du précédant

	int source = (rank - 1 + size ) % size;

	MPI_Status status;

	MPI_Recv(NULL, 0, MPI_BYTE, source, TAG_BONJOUR,
		MPI_COMM_WORLD, &status);

	cout << rank << " a reçu un message de " << source << endl;




















	MPI_Finalize();

	return 0;
}
