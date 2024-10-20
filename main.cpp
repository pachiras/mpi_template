#include <stdio.h>
#include <cstdio>
#include <random>
#include <mpi.h>

const int TRIAL = 1000000;
const int NAME_LENGTH = 10;

double calc_pi(const int seed) {
  std::mt19937 mt(seed);
  std::uniform_real_distribution<double> ud(0.0, 1.0);
  int n = 0;
  for (int i = 0; i < TRIAL; i++) {
    double x = ud(mt);
    double y = ud(mt);
    if (x * x + y * y < 1.0) n++;
  }
  return 4.0 * static_cast<double>(n) / static_cast<double>(TRIAL);
}


int main(int argc, char* argv[]){
  int rank, proc;
  int name_len = NAME_LENGTH;
  char name[NAME_LENGTH];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc);
  MPI_Get_processor_name(name, &name_len);

  const double pi = calc_pi(rank);
  printf("%s : %d of %d\n", name, rank, proc);
  printf("%d: %f\n", rank, pi);

  MPI_Finalize();
  return 0;
}
