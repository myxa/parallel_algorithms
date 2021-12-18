#include <iostream>
#include <ctime>
#include <omp.h>
#include <cstdlib>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
    int N = atoi(argv[1]);
    vector<vector<int>> A(N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i].push_back(rand() / 1000);
        }

    }
    vector<vector<int>> B(N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            B[i].push_back(rand() / 1000);
        }

    }
    vector<vector<int>> C(N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i].push_back(0);
        }
    }
    for (int t = 1; t < 11; t++) {

        double st = omp_get_wtime();
#pragma omp parallel num_threads(10)
        {
#pragma omp for collapse(3)
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    for (int k = 0; k < N; k++)
                    {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        double t1;
        if (t == 1) {
            t1 = omp_get_wtime() - st;
        }
        cout <<"Thread: " << t << " Time: " << omp_get_wtime() - st << " Efficiency: "<< t1/ (omp_get_wtime() - st) << endl;
    }
    cout << endl;
    for (int t = 1; t < 11; t++) {
        double st = omp_get_wtime();
#pragma omp parallel num_threads(10)
        {
#pragma omp for collapse(3)
            for (int j = 0; j < N; j++)
            {
                for (int k = 0; k < N; k++)
                {
                    for (int i = 0; i < N; i++)
                    {
                        C[j][k] += A[j][i] * B[i][k];
                    }
                }
            }
        }
        double t1;
        if (t == 1) {
            t1 = omp_get_wtime() - st;
        }
        cout << "Thread: " << t << " Time: " << omp_get_wtime() - st << " Efficiency: " << t1 / (omp_get_wtime() - st) << endl;
    }
    cout << endl;
    for (int t = 1; t < 11; t++) {
        double st = omp_get_wtime();
#pragma omp parallel num_threads(10)
        {
#pragma omp for collapse(3)
            for (int i = 0; i < N; i++)
            {
                for (int k = 0; k < N; k++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        C[i][k] += A[i][j] * B[j][k];
                    }
                }
            }
        }
        double t1;
        if (t == 1) {
            t1 = omp_get_wtime() - st;
        }
        cout << "Thread: " << t << " Time: " << omp_get_wtime() - st << " Efficiency: " << t1 / (omp_get_wtime() - st) << endl;
    }
    return 0;
}