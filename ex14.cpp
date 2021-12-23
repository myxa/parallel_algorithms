#include <cstdlib>
#include <iostream>
#include "mpi.h"
using namespace std;
#define n 1000

void smod5(void* a, void* b, int* l, MPI_Datatype* type) {
	int i;
	for (i = 0; i < *l; i++)
		((int*)b)[i] = (((int*)a)[i] + ((int*)b)[i]) % 5;
}
void max_fun(void* a, void* b, int* l, MPI_Datatype* dtp)
{
	for (int i = 0; i < *l; i++)
	{
		if (((int*)a)[i] > ((int*)b)[i])
			((int*)b)[i] = ((int*)a)[i];
	}
}
int main(int argc, char** argv)
{
	int rank, size, i;
	int a[n];
	int b[n];
	int b_reduce[n];
	MPI_Init(&argc, &argv);
	MPI_Op op;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (i = 0; i < n; i++) a[i] = i + rank + 1;
	printf("process %d a[0] = %d\n", rank, a[0]);
	MPI_Op_create(&smod5, 1, &op);
	MPI_Reduce(a, b, n, MPI_INT, op, 0, MPI_COMM_WORLD);
	MPI_Op_free(&op);

	//MPI_Reduce(a, b, n, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	if (rank == 0) cout << "Max: " << b[0] << endl;

	MPI_Finalize();
}