#ifndef MPI_HELPER_H
#define MPI_HELPER_H

#include "mpi.h"

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

template<typename T>
void MPI_MEAN(T *sendbuf, T *recvbuf) {
    T sum;
    MPI_Allreduce((const void *) sendbuf, (void *) &sum, 1,
                  get_type<T>(), MPI_SUM, MPI_COMM_WORLD);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    *recvbuf = sum / static_cast<T>(world_size);
}

#endif // MPI_HELPER_H
