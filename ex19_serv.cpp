#include <stdio.h>
#include "mpi.h"
int main(int argc, char** argv)
{
	int r;
	int m = 25;
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Status status;
	MPI_Comm intercomm;
	MPI_Open_port(MPI_INFO_NULL, port_name);
	printf("portname: %s\n", port_name);
	printf("waiting for the client...\n");
	MPI_Comm_accept(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	printf("client connected\n");
	MPI_Send(&m, 1, MPI_INT, 0, 0, intercomm);
	MPI_Recv(&r, 1, MPI_INT, 0, 0, intercomm, &status);
	MPI_Comm_free(&intercomm);
	MPI_Close_port(port_name);
	printf("server sent value: %i\n", m);
	printf("server recieved value: %i\n", r);
	MPI_Finalize();
	return 0;
}