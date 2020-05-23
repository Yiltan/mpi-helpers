# MPI Helpers
A library containing common MPI helper functions which I frequently use.
The current implemenation only allows for a single `int`, `long`, `float`, and `double`.
The type `T` we seen in the templates must be one of these four types.
This is sufficiant as it covers most of my use cases.

## Usage
To use this project in your code just copy and paste the file in `src/mpi-helpers.h`
into your project and then `#include` it your program.

## Implemented Helper Funtions
#### `MPI_MEAN(T *x, T *mean)`
#### `MPI_MEAN(T *x, T *mean, T *stddev)`
Input:
  - `x` Our input value.

Output:
  - `mean` The arithmetic mean of our input values.
  - `stddev` The standard deviation of our input values.

#### `format_bytes(long long int num_bytes)`
Input:
  - `num_bytes` The number of bytes in decimal format.

Returns:
  - An `std::string` is retruned formating the num bytes with the SI suffix (1024 becomes 1K).
