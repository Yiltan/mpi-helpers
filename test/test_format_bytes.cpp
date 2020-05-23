#include "mpi_helper.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv) {

  // Header
  std::cout << "Bytes\t\tFormated" << std::endl;

  long long int n = 0;
  std::cout << n <<  "\t\t" << format_bytes(n) << std::endl;

  n = 1024;
  std::cout << n <<  "\t\t" << format_bytes(n) << std::endl;

  n = n * 1024;
  std::cout << n <<  "\t\t" << format_bytes(n) << std::endl;

  n = n * 1024;
  std::cout << n <<  "\t" << format_bytes(n) << std::endl;

  n = 64 * n;
  std::cout << n <<  "\t" << format_bytes(n) << std::endl;

  return 0;
}
