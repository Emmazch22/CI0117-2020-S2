#include <iostream>
#include <mpi.h>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

void initArray(int * array, int size){
  for (int i = 0; i < size; ++i){
    array[i] = 0;
  }
}

int main(int argc, char *argv[]){
  string sequence;
  int sequence_count_local[26];
  int sequence_count_global[26];
  char * recvBuff;
  int my_id, numProcesses;
  double start_time, end_time;

  initArray(sequence_count_local, 26);
  initArray(sequence_count_global, 26);

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  MPI_Status status;

  if (my_id == 0){
    if (argc < 2){
      cerr << "Error, invalid number of parameters" << endl;
      return 1;
    }
    else {
      ifstream file(argv[1]);
      if (file.is_open())
      {
          getline(file, sequence);
          file.close();
      }
      else
      {
          cout << "Unable to open file" << argv[1] << endl;
          return 1;
      }
    }
  }
  char * sequence_segment;
  int sequence_size = sequence.length();

  MPI_Bcast(&sequence_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
  int segment_size = floor((float)sequence_size / numProcesses);

  if (segment_size < 1){
    if (my_id == 0){
      cout << "Too many processes for this sequence" << endl;
    }
    return 1;
  }

  sequence_segment = new char[segment_size];
    start_time = MPI_Wtime();

  MPI_Scatter(&sequence[0], segment_size, MPI_CHAR, sequence_segment, segment_size, MPI_CHAR, 0, MPI_COMM_WORLD);

  int index;

  for (int i = 0; i < segment_size; ++i){
    index = sequence_segment[i] - 'a';
    if (index < 26 && index >= 0){
      sequence_count_local[index]++;
    }
  }

  if (my_id == 0){
    int remaining = sequence_size % segment_size;
    for (int i = sequence_size - 1; i >= (sequence_size - remaining); --i){
      index = sequence[i] - 'a';
      if (index < 26 && index >= 0){
        sequence_count_local[index]++;
      }
    }
  }

  MPI_Reduce(sequence_count_local, sequence_count_global, 26, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  end_time = MPI_Wtime();

  if (my_id == 0){
    cout << "Sequence size: " << fixed << sequence_size << ". Duration: " << end_time - start_time << endl;
    cout << "Sequence ocurrences: " << endl;

    for (int i = 0; i < 26; ++i){
      if (sequence_count_global[i] > 0){
        cout << " " << (char)('a' + i) << " = " << sequence_count_global[i];
      }
    }
    cout << endl;
  }
  MPI_Finalize();

  delete [] sequence_segment;
  return 0;
}
