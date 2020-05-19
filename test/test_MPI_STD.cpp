#include "mpi_helper.h"
#include "mpi.h"
#include "cmath"

int main(int argc, char** argv) {
  // Init
  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  double send_val = 1.234 * static_cast<double>(world_rank);
  double std_val = 0.0;

  // Test
  MPI_STD<double>(&send_val, &std_val);

  // Check answer
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  double mean = 0.0;
  for (int i=0; i<world_size; i++) {
    mean += 1.234 * static_cast<double>(i);
  }
  mean = mean / static_cast<double>(world_size);

  double squared_sum = 0.0;
  for (int i=0; i<world_size; i++) {
    double squared = (1.234 * static_cast<double>(i) - mean)
                   * (1.234 * static_cast<double>(i) - mean);
    squared_sum += squared;
  }
  double variance = squared_sum / static_cast<double>(world_size);
  double expected_std = sqrt(variance);

  if (0 == world_rank) {
    double err = expected_std - std_val;
    std::cout << "The difference from the expected standard deviation is: "
              << err << std::endl;
  }

  MPI_Finalize();
  return 0;
}
