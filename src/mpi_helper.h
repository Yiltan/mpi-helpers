#ifndef MPI_HELPER_H
#define MPI_HELPER_H

#include "mpi.h"
#include "cmath"
#include <vector>

template<typename T>
static inline MPI_Datatype get_type() {
  const char *type_name = typeid(T).name();

  switch (*type_name) {
    case 'i' : { return MPI_INT; }
    case 'd' : { return MPI_DOUBLE; }
    case 'f' : { return MPI_FLOAT; }
    case 'l' : { return MPI_LONG; }
    default : {
                std::cout << "The type " << type_name
                          << " is not recognised" << std::endl;
                return MPI_BYTE;
              }
  }
}

// Calculate mean value between processes
template<typename T>
void MPI_MEAN(T *x, T *mean) {
    T sum;
    MPI_Allreduce((const void *) x, (void *) &sum, 1, get_type<T>(), MPI_SUM, MPI_COMM_WORLD);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    *mean = sum / static_cast<T>(world_size);
}

// Calculate Mean and Standard Deviation between processes
template<typename T>
void MPI_MEAN(T *x, T* mean, T *stddev) {

    MPI_MEAN<T>(x, mean);

    T squared = (*x - *mean) * (*x- *mean);
    T squared_sum;

    MPI_Allreduce((const void *) &squared, (void *) &squared_sum, 1, get_type<T>(), MPI_SUM, MPI_COMM_WORLD);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    T variance = squared_sum / static_cast<T>(world_size);
    *stddev= static_cast<T>(sqrt(variance));
}

std::string format_bytes(long long int num_bytes) {
    if (0 == num_bytes) return "0";

    const std::vector<std::string> suffixes = {"", "K", "M", "G"};

    int index = floor(log(num_bytes) / log(1024));
    int size = num_bytes / pow(1024, index);

    return std::to_string(size) + suffixes[index];
}

#endif // MPI_HELPER_H
