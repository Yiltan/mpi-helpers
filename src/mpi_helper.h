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

#endif // MPI_HELPER_H
