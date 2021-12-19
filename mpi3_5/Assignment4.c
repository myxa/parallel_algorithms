#include <iostream>
#include "mpi.h"
using namespace std;
int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	double time_start, time_finish;
	int rank, n, i, message;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	time_start = MPI_Wtime();
	if (rank == 1) {
		MPI_Send(&rank, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
	}
	if (rank == 2) {
		MPI_Recv(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
		MPI_Send(&rank, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	if (rank == 1) {
		MPI_Recv(&message, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);
		MPI_Send(&rank, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
	}
	if (rank == 2) {
		MPI_Recv(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
		time_finish = MPI_Wtime();
		cout << "Process 2 recieved message: " << message << " Time: " << time_finish - time_start << endl;

	}
	
	MPI_Finalize();
	return 0;
}