#include <omp.h>
#include <iostream>
#include <vector>

using namespace std;
int main(int argc, char* argv[]) {
    long int n = atoi(argv[1]);
    vector <int> a;
    
    for (int i = 0; i < n; i++)
    {
        a.push_back(rand());
    }
    double mm = a[0];

    
    for (int i = 1; i < 11; i++) {
        double st = omp_get_wtime();
# pragma omp parallel num_threads(i) reduction(max:mm)
        {
# pragma omp for

            for (int i = 0; i < n; i++) {
                if (mm < a[i]) {
                    mm = a[i];
                }

            }
        }
        cout << "Time: " << omp_get_wtime() - st << endl;
    }
    return 0;
}