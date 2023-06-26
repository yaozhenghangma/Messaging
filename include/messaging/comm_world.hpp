/*
 * @Author: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @Date: 2023-06-23
 * @FilePath: include/messaging/comm_world.hpp
 * @Description: Header file for communicator.
 *
 * Copyright (c) 2023 by Yaozhenghang.Ma email:Yaozhenghang.Ma@gmail.com, All Rights Reserved.
 */

#ifndef COMM_WORLD_HPP
#define COMM_WORLD_HPP

#include <messaging/config.hpp>
#include <messaging/environment.hpp>
#include <messaging/serialization.hpp>

namespace messaging {
    class CommWorld {
    public:
        CommWorld();
        CommWorld(int &argc, char** &argv);
        ~CommWorld();

        int Rank();
        int Size();

        template<typename T>
        int Send(T &data, int destination, int tag);

        template<typename T>
        int Recv(T &data, int source, int tag);
    private:
        messaging::Environment env_;
        bool initialized_;
    };

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

#endif //COMM_WORLD_HPP