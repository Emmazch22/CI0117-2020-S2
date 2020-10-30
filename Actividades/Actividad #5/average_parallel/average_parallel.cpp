#include <iostream>
#include <string> 
#include <omp.h>

using namespace std;

const int thread_count = 3;

static void calculate_sum(char **array, int array_size, double* global_sum) {
    double local_sum = 0.0;

    #pragma omp parallel num_threads(thread_count) reduction(+: local_sum)
    for (int i = 1; i < array_size + 1 ; ++i){
        local_sum += stoi(array[i]);
    }
    #pragma omp critical
        *global_sum += local_sum;
}

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        cout << "Invalid number of parameters.\n";
        return 1;
        
    } else if ( (argc - 1) % thread_count != 0) {
        cout << "Error, invalid number of threads.\n";
        return 1;
    }
    double global_sum = 0.0;
    #pragma omp parallel num_threads(thread_count) shared(global_sum, argc, argv)
        calculate_sum(argv, argc - 1, &global_sum);
    
    cout << "Average: " << ( (global_sum / thread_count ) / (argc - 1)) << endl;
    
    return 0;
}