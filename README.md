# MPI Helpers
A library containing common MPI helper functions which I frequently use. 
The current implemenation only allows for a single `int`, `long`, `float`, and `double`. 
The type `T` we seen in the templates must be one of these four types.
This is sufficiant as it covers most of my use cases. 

## Implemented Helper Funtions
#### `MPI_MEAN(T *sendbuf, T *recvbuf)`
Input:
  - `sendbuf` We would pass the value within the current process which we would like to find the mean value of.
  
Output:
  - `recvbuf` This value is the returned mean between all processes.
  
#### `MPI_STD(T *sendbuf, T *recvbuf)`
Input:
  - `sendbuf` We would pass the value within the current process which we would like to find the standard deviation of.
  
Output:
  - `recvbuf` This value is the returned standard deviation between all processes.

