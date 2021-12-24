#include "mpi.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int main(int argc, char** argv)
{
	int rank, r;
	int m = 42;
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Status status;
	MPI_Comm intercomm;
	strcpy(port_name, argv[1]);
	MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	printf("attempt to connect\n");
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("server connection\n");
	MPI_Send(&m, 1, MPI_INT, 0, 0, intercomm);
	MPI_Recv(&r, 1, MPI_INT, 0, 0, intercomm, &status);
	printf("server sent value: %i\n", m);
	printf("server recieved value: %i\n", r);
	MPI_Finalize();
	return 0;
}