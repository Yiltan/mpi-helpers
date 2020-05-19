#ifndef MPI_HELPER_H
#define MPI_HELPER_H

#include "mpi.h"
#include "cmath"

template<typename T>
MPI_Datatype get_type() {
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

// Calculated mean value between processes
template<typename T>
void MPI_MEAN(T *sendbuf, T *recvbuf) {
    T sum;
    MPI_Allreduce((const void *) sendbuf, (void *) &sum, 1,
                  get_type<T>(), MPI_SUM, MPI_COMM_WORLD);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    *recvbuf = sum / static_cast<T>(world_size);
}

// Calculated Standard Deviation between processes
template<typename T>
void MPI_STD(T *sendbuf, T *recvbuf) {
    T mean_val;
    MPI_MEAN<T>(sendbuf, &mean_val);

    T squared = (*sendbuf - mean_val) * (*sendbuf - mean_val);
    T squared_sum;

    MPI_Allreduce((const void *) &squared, (void *) &squared_sum, 1,
                  get_type<T>(), MPI_SUM, MPI_COMM_WORLD);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    T variance = squared_sum / static_cast<T>(world_size);
    *recvbuf = static_cast<T>(sqrt(variance));
}

#endif // MPI_HELPER_H
