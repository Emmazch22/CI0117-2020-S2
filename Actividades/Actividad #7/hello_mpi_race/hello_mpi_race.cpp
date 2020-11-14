#include <iostream>
#include "mpi.h"
using namespace std;

define SIZE 100

int main(int argc, char *argv[]) {

    int my_id, num_processes;
    int message = 1
    MPI_Init(&argc, &argv);
    
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    if (my_id == 0){
        message_sent = 1;
        for (int i = 0; i < num_processes; ++i){
            MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            cout << "Process " << status.MPI_SOURCE << endl;
        }
    }
    else {
        cout << "Hello, I am process: " << my_id << endl;
        MPI_Send(&message, SIZE, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
