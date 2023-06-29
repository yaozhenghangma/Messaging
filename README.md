# Messaging

Messaging is a modern C++20 MPI wrapper, inspired by Boost.MPI and mpi4py.

## Abstract

Multiprocess paralleling using MPI is the standard approach in high-performance
computing. However, implementing message passing can be a tedious task due to the
limited support for data types in MPI. Although there's library like Boost.MPI
that offers high-level interfaces, it necessitates building the entire Boost library,
which can be burdensome for users. In light of this, I decide to
develop this simple library to wrap the basic operators in MPI.

The data serialization part of this library is based on 
[zpp_bits](https://github.com/eyalz800/zpp_bits), which is serialization library
only supports C++20 and newer standard. Consequently, to utilize this library, your
project must be set to C++20 or a newer standard.

Since this library is build with CMake toolkit, you can use this library by
simply adding it to subdirectory and linking it. For example:
```cmake
add_subdirectory(lib/Messaging)
target_link_libraries(project_name PUBLIC Messaging)
```

## Usage
### MPI environment
A C++ object named `CommWorld` is provided to set up the environment and communicator.
```c++
#include <iostream>
#include <messaging.hpp>

int main() {
    messaging::CommWorld comm;
    int rank = comm.Rank();
    int size = comm.Size();
    
    std::cout << "This is the number " << rank << "process of " << size << "processes." 
    << std::endl;
    return 0;
}
```

### Point-to-point communication
#### Blocking communication
The blocking communication is realized by two methods named `Send` and `Recv`.
```c++
template<typename T>
messaging::CommWorld::Send(T &data, int dest, int tag);
```
```c++
template<typename T>
messaging::CommWorld::Recv(T &data, int source, int tag);
```
Parameters:
* data: data to be sent or saved
* dest: rank of processor where the data will be sent to
* source: rank of processor where the data will be sent from
* tag: tag labeling the message
```c++
#include <messaging.hpp>

class Coordinate {
public:
    double x;
    double y;
    double z;
};

int main() {
    Coordinate coord;
    messaging::CommWorld comm;
    if(comm.Rank() == 0) {
        coord.x = 0;
        coord.y = 1;
        coord.z = 2;
        comm.Send(coord, 1, 99);
    } else if(comm.Rank() == 1) {
        comm.Recv(coord, 0, 99);
    }
}
```

### Collective communication
#### Broadcast
```c++
template<typename T>
messaging::CommWorld::Broadcast(T &data, int root);
```
Parameters:
* data: data to be broadcast
* root: rank of the processor that will broadcast data

```c++
#include <messaging.hpp>

class Coordinate {
public:
    double x;
    double y;
    double z;
};

int main() {
    messaging::CommWorld comm;
    Coordinate coord;
    std::vector<Coordinate> coord_vec;
    int rank = comm.Rank();
    int size = comm.Size();
    
    if(rank == 0) {
        coord.x = 1;
        coord.y = 2;
        coord.z = 3;
    }
    comm.Broadcast(coord, 0);
    return 0;
}
```

#### Gather
```c++
template<typename T>
messaging::CommWorld::Gather(T &data, std::vector<T> &all_data, int root);
```
Parameters:
* data: data to be sent
* all_data: vector to save the gathered data (stored in root processor)
* root: rank of root processor

```c++
#include <messaging.hpp>

class Coordinate {
public:
    double x;
    double y;
    double z;
};

int main() {
    messaging::CommWorld comm;
    Coordinate coord;
    std::vector<Coordinate> coord_vec;
    int rank = comm.Rank();
    int size = comm.Size();
    
    coord.x = rank;
    coord.y = rank+10;
    coord.z = rank+100;
    comm.Gather(coord, coord_vec, 0);
    return 0;
}
```

#### Scatter
```c++
template<typename T>
messaging::CommWorld::Scatter(std::vector<T> &all_data, T &data, int root);
```
Parameters:
* all_data: data to be scattered from root processor
* data: received data
* root: rank of root processor

```c++
#include <messaging.hpp>

class Coordinate {
public:
    double x;
    double y;
    double z;
};

int main() {
    messaging::CommWorld comm;
    Coordinate coord;
    std::vector<Coordinate> coord_vec;
    int rank = comm.Rank();
    int size = comm.Size();
    
    if(rank == 0) {
        for(int i=0; i<size; i++) {
            coord_vec[i].x = i;
            coord_vec[i].y = i+100;
            coord_vec[i].z = i+1000;
        }
    }
    comm.Scatter(coord_vec, coord, 0);
    return 0;
}
```