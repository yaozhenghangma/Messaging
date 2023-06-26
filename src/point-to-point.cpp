/*
 * @Author: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @Date: 2023-06-25 18:50:29
 * @LastEditors: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @LastEditTime: 2023-06-25 19:49:18
 * @FilePath: /Messaging/src/point-to-point.cpp
 * @Description:
 *
 * Copyright (c) 2023 by Yaozhenghang.Ma email:Yaozhenghang.Ma@gmail.com, All Rights Reserved.
 */

#include <messaging/comm_world.hpp>

namespace messaging {
    template<typename T>
    int CommWorld::Send(T &data, int destination, int tag) {
        auto serialized_data = serialization::serialize<T>(data);
        int length = serialized_data.size();
        MPI_Send(&length, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
        MPI_Send(&serialized_data[0], length, MPI_BYTE, destination, tag, MPI_COMM_WORLD);
        return 0;
    }

    template<typename T>
    int CommWorld::Recv(T &data, int source, int tag) {
        int length;
        MPI_Status status;
        std::vector<std::byte> serialized_data;
        MPI_Recv(&length, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        serialized_data.resize(length, std::byte{0});
        MPI_Recv(&serialized_data[0], length, MPI_BYTE, source, tag, MPI_COMM_WORLD, &status);
        serialization::deserialize(data, serialized_data);
        return 0;
    }
}