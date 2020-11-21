#include <iostream>
#include "mpi.h"

using namespace std;

int main(){
  int my_id, num_processes, array_size, num, min, max, sum;
  int * array;
  double average;
  int message_sent = 1;
  int message_received;
  MPI_Init(&argc, &argv);

  MPI_Status status;

  MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

  if (my_id == 0){
      cout << "Enter the amount of numbers: " << endl;
      cin >> array_size;

      array = new int[array_size];
      cout << "Enter " << array_size << "numbers: " << endl;
      for (int i = 0; i < array_size; ++i){
          cin >> array[i];
      }
  }

  MPI_Bcast(&array_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (my_id != 0){
    array = new int[array_size];
  }
  MPI_Bcast(array, array_size, MPI_INT, 0, MPI_COMM_WORLD);
  srand(time(NULL) * my_id * 1000);
  int index = rand() % array_size;
  num = array[index];

    MPI_Allreduce(&num, &max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&num, &min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    MPI_Allreduce(&num, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if (my_id != 0){
      MPI_Recv(&message_received,, MPI_INT, my_id - 1 , 123 , MPI_COMM_WORLD, &status);
    }

    cout << "Process #" << my_id << " . Number: " << num << endl;

    if (my_id == 0){
      cout << "The max is: " << max << "\nThe minimum is: " << min << "\nThe average is: " << sum / array_size << endl;
    }

    if (my_id < num_processes - 1){
      MPI_Send(&message_sent, 1, MPI_INT, my_id + 1, 123, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    delete[] array;

    return 0;
}
