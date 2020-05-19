#include "mpi_helper.h"
#include "mpi.h"

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);

  MPI_Datatype d0 = get_type<int>();
  MPI_Datatype d1 = get_type<double>();
  MPI_Datatype d2 = get_type<float>();
  MPI_Datatype d3 = get_type<long>();
  MPI_Datatype d4 = get_type<long long int>();

  MPI_Finalize();
  return 0;
}
