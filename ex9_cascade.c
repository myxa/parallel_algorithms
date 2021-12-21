#include <iostream>
#include "mpi.h"
using namespace std;

int main(int argc, char** argv)
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;

	int n = 1000000;
	int n_ = n / size +1;

	int* a = (int*)calloc(n, sizeof(int));
	int* a_ = (int*)calloc(n_, sizeof(int));

	int* subsums = (int*)calloc(n, sizeof(int));
	int sum = 0;

	for (int i = 0; i < 1000000; i++)
	{
		a[i] = 1;
	}


	double start_time = MPI_Wtime();

	MPI_Scatter(a, n, MPI_INT, a_, n_, MPI_INT, 0, MPI_COMM_WORLD);

	int subsum = 0;
	for (int i = 0; i < (n_); i++) {
		subsum += a_[i];
	}

	for (int i = 2; i <= size; i *= 2)
	{

		if (rank % i == 0)
		{
			int temp;
			MPI_Recv(&subsum, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			//subsum += temp;
			cout << "Level: " << i << "  Receiver thread: " << rank << "  Sender thread:  " << status.MPI_SOURCE << "  value:  " << temp << "  Accumulated total:  " << subsum << endl;
		}

		else
		{
			MPI_Send(&subsum, 1, MPI_INT, rank - (rank % i), 0, MPI_COMM_WORLD);
			break;
		}
	}

	if (rank == 0)
	{
		printf("Total answer: %d\n", subsum);
		printf("Point to point execution time: %f \n", (MPI_Wtime() - start_time));
	}
	MPI_Finalize();
	return 0;
}