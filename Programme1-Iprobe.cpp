#include <mpi.h>
#include <stdint.h>
#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char**argv){

	MPI_Init(&argc, &argv);

	int rank;
	int size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	char machine[32];
	int length;
	MPI_Get_processor_name(machine, &length);

	cout << "Je suis le numéro # " << rank;
	cout << " (" << machine << ")" << " parmi " << size << endl;

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

	int receivedMessages = 0;

	while(receivedMessages == 0){

		MPI_Status status;
		int flag = 0;

		MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag,  &status);

		if(!flag)
			continue;

		int source = status.MPI_SOURCE;
		int tag = status.MPI_TAG;

		MPI_Status status2;
		MPI_Recv(NULL, 0, MPI_BYTE, source, tag,
			MPI_COMM_WORLD, &status2);

		cout << rank << " a reçu un message de " << source << endl;

		receivedMessages++;
	}

// écrire un beau fichier

	MPI_File fp;
	char fileName []= "Fichier-de-Sortie.txt";

	MPI_File_open(MPI_COMM_WORLD, fileName, MPI_MODE_CREATE | MPI_MODE_RDWR,
		MPI_INFO_NULL, &fp);

        MPI_Datatype elementType = MPI_BYTE;
        MPI_Datatype fileType = MPI_BYTE;

	int bytesPerRank=16;

        char representation[] = "native";
        MPI_Offset displacement= rank * bytesPerRank;

	MPI_File_set_view(fp, displacement, elementType,fileType,representation,MPI_INFO_NULL);

	ostringstream buffer;
	buffer << rank << "\t" << size;

	buffer << "\t" << machine;

	int remaining = bytesPerRank - buffer.str().length();

	remaining--;
	while(remaining--){

		buffer<<".";
	}

	buffer<<"\n";

	string value = buffer.str();
	char* content= const_cast<char*> ( value.c_str() );

	MPI_Status fileStatus;

	MPI_File_write(fp, content, value.length(), 
		fileType, &fileStatus);

	MPI_File_close(&fp);

	MPI_Finalize();

	return 0;
}
