/**
 *
 * Test MPI I/O
 *
 * \author Sébastien Boisvert
 */

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

	char machine[256];
	int length;
	MPI_Get_processor_name(machine, &length);

	MPI_File fp;
	char fileName []= "SampleFile.txt";

	MPI_File_open(MPI_COMM_WORLD, fileName, MPI_MODE_CREATE | MPI_MODE_RDWR,
		MPI_INFO_NULL, &fp);

        MPI_Datatype elementType = MPI_BYTE;
        MPI_Datatype fileType = MPI_BYTE;

	int bytesPerRank=256;
        MPI_Offset displacement= rank * bytesPerRank;

	char representation[] = "native";
	MPI_File_set_view(fp, displacement, elementType,fileType, representation,MPI_INFO_NULL);

	ostringstream buffer;
	buffer << "Rank: "<<rank << " Size: "<< size;
	buffer << " ProcessorName: " << machine<<" ";

	int remaining = bytesPerRank - buffer.str().length();

	remaining--;
	while(remaining--)
		buffer<<".";

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
