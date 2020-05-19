#include "mpi_helper.h"
#include "mpi.h"

int main(int argc, char** argv) {
  // Init
  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  double send_val = 1.234 * static_cast<double>(world_rank);
  double mean_val = 0.0;

  // Test
  MPI_MEAN<double>(&send_val, &mean_val);

  // Check answer
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  double expected_mean = 0.0;
  for (int i=0; i<world_size; i++) {
    expected_mean += 1.234 * static_cast<double>(i);
  }
  expected_mean = expected_mean / static_cast<double>(world_size);

  if (0 == world_rank) {
    double err = expected_mean - mean_val;
    std::cout << "The difference from the expected mean is: "
              << err << std::endl;
  }

  MPI_Finalize();
  return 0;
}
