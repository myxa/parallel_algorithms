#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include "mpi.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;

	for (int i = 0; i <= 6; i++) {
		int n = 10;
		double array_size = pow(10, i);
		double L = array_size * sizeof(double);
		double *ar = (double*)calloc(L, sizeof(double));

		double start_time = MPI_Wtime();

		for (int i = 0; i < n; i++) {
			if (rank == 0) {
				MPI_Send(ar, array_size, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
				MPI_Recv(ar, array_size, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD, &status);
			}
			if (rank == 1) {
				MPI_Recv(ar, array_size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
				MPI_Send(ar, array_size, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
			}
		}
		double end_time = MPI_Wtime();
		if (rank == 0) {
			double bandwidth = 2 * n * L / (end_time - start_time);
			double latency = (end_time - start_time) / (2 * n);

			cout << "----------------" << endl;
			cout << "message length = " << L << " bytes" << endl;
			cout << "bandwidth = " << bandwidth /1024 /1024 << " mb/s" << endl;

			free(ar);
		}
	}
	MPI_Finalize();
	return 0;
}
//mpic++ -o main as3.c
//mpiexec - n 6 . / main