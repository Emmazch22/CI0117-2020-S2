
#include <iostream>
#include <omp.h>

using namespace std;

static const int thread_count = 3;

int main(int argc, char * argv[]){
    --argc;

    if (argc <= 1){
        cout << "Invalid number of parameters" << endl;
        return 1;
    } else if ( (argc % thread_count != 0) ){
        cout << "Invalid number of parameters" << endl;
        return 1;
    }

    double sum = 0.0;

    #pragma omp parallel for num_threads(thread_count) reduction(+:sum)
    for (int i = 1; i < argc + 1; ++i){
        sum += stoi(argv[i]);
    }

    cout << "Average: " << (sum / argc) << endl;
    return 0;
}