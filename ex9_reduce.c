#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    int n = 2000000;
    int* a = (int*)calloc(n, sizeof(int));

    int n_, size, rank, i;
    int product, product_;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (i = 0; i < n; i++) {
        a[i] = 1;
    }

    n_ = n / size + 1;

    int* a_ = (int*)calloc(n_, sizeof(int));
    double start_time = MPI_Wtime();
    MPI_Scatter(a, n_, MPI_INT, a_, n_, MPI_INT, 0, MPI_COMM_WORLD);

    product_ = 0;
    for (i = 0; i < n_; i++) {
        product_ += a_[i];
    }

    free(a_);

    MPI_Reduce(&product_, &product, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    double end_time = MPI_Wtime();
    if (rank == 0) {
        cout << "sum: " << product << " time: " << end_time - start_time << endl;
    }

    MPI_Finalize();
    return 0;
}