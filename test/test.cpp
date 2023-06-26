/*
 * @Author: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @Date: 2023-06-23
 * @FilePath: test/test.cpp
 * @Description:
 *
 * Copyright (c) 2023 by Yaozhenghang.Ma email:Yaozhenghang.Ma@gmail.com, All Rights Reserved.
 */
#include <stdio.h>
#include <messaging.hpp>

int main(int argc, char** argv) {
    messaging::CommWorld comm;
    int size = comm.Size();
    int rank = comm.Rank();

    if(rank == 0) {
        int i1 = 1;
        comm.Send(i1, 1, 99);
    } else {
        int i2 = 2;
        comm.Recv(i2, 0, 99);
        printf("processor: %d, i: %d\n", rank+1, i2);
    }

    printf("processor: %d/%d\n", rank+1, size);
    return 0;
}