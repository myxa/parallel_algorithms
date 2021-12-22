#include <mpi.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	int n = 500;
	int rank, size;
	MPI_Init(&argc, &argv);

	double start_time, end_time;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int A[n][n], B[n][n], C[n][n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A[i][j] = 1 + rand() % 10;
			B[i][j] = 1 + rand() % 10;
			C[i][j] = 0;
		}
	}

	MPI_Barrier(MPI_COMM_WORLD); 

	start_time = MPI_Wtime();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	end_time = MPI_Wtime();

	cout << "process " << rank << ", execution time=" << (end_time - start_time) << endl;
	MPI_Finalize();
}