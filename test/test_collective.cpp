/*
 * @Author: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @Date: 2023-06-28
 * @FilePath: test/test_collective.cpp
 * @Description:
 *  
 * Copyright (c) 2023 by Yaozhenghang.Ma email:Yaozhenghang.Ma@gmail.com, All Rights Reserved.
 */

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

    // Test broadcast
    if(rank == 0) {
        coord.x = 1;
        coord.y = 2;
        coord.z = 3;
    }
    comm.Broadcast(coord, 0);
    assert(coord.x == 1);
    assert(coord.y == 2);
    assert(coord.z == 3);

    // Test Gather
    coord.x = rank;
    coord.y = rank+10;
    coord.z = rank+100;
    comm.Gather(coord, coord_vec, 0);
    if(rank == 0) {
        for(int i=0; i<size; i++) {
            assert(coord_vec[i].x == i);
            assert(coord_vec[i].y == i+10);
            assert(coord_vec[i].z == i+100);
        }
    }


    // Test Scatter
    if(rank == 0) {
        for(int i=0; i<size; i++) {
            coord_vec[i].x = i;
            coord_vec[i].y = i+100;
            coord_vec[i].z = i+1000;
        }
    }
    comm.Scatter(coord_vec, coord, 0);
    assert(coord.x == rank);
    assert(coord.y == rank+100);
    assert(coord.z == rank+1000);
    return 0;
}