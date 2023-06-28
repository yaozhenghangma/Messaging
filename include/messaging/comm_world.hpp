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

        template<typename T>
        int Broadcast(T &data, int root);

        template<typename T>
        int Gather(T &data, std::vector<T> &all_data, int root);

        template<typename T>
        int Scatter(std::vector<T> &all_data, T &data, int root);
    private:
        messaging::Environment env_;
        bool initialized_;
    };

    template<typename T>
    std::vector<std::vector<T>> split_vector(std::vector<T> &data, int length, int size) {
        std::vector<std::vector<T>> split_data;
        split_data.resize(size);
        int index = 0;
        for(int i=0; i<size; i++) {
            split_data[i].resize(length);
            for(int j=0; j<length; j++) {
                split_data[i][j] = data[index];
                index++;
            }
        }
        return split_data;
    }

    template<typename T>
    std::vector<T> merge_vector(std::vector<std::vector<T>> &data, int length, int size) {
        std::vector<T> merge_data;
        merge_data.resize(length*size);
        int index = 0;
        for(int i=0; i<size; i++) {
            for(int j=0; j<length; j++) {
                merge_data[index] = data[i][j];
                index ++;
            }
        }
        return merge_data;
    }

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
        serialized_data.resize(length);
        MPI_Recv(&serialized_data[0], length, MPI_BYTE, source, tag, MPI_COMM_WORLD, &status);
        serialization::deserialize(data, serialized_data);
        return 0;
    }

    template<typename T>
    int CommWorld::Broadcast(T &data, int root) {
        int length=0;
        auto serialized_data = serialization::serialize<T>(data);
        length = serialized_data.size();
        MPI_Bcast(&length, 1, MPI_INT, root, MPI_COMM_WORLD);
        serialized_data.resize(length);
        MPI_Bcast(&serialized_data[0], length, MPI_BYTE, root, MPI_COMM_WORLD);
        serialization::deserialize(data, serialized_data);
        return 0;
    }

    template<typename T>
    int CommWorld::Gather(T &data, std::vector<T> &all_data, int root) {
        auto serialized_data = serialization::serialize<T>(data);
        int length = serialized_data.size();
        std::vector<std::byte> all_serialized_data;
        all_serialized_data.resize(this->Size() * length);
        MPI_Gather(&serialized_data[0], length, MPI_BYTE, &all_serialized_data[0], length, MPI_BYTE, root, MPI_COMM_WORLD);
        if(this->Rank() == root) {
            auto split_serialized_data = split_vector<std::byte>(all_serialized_data, length, this->Size());
            all_data.resize(this->Size());
            for(int i=0; i<this->Size(); i++) {
                serialization::deserialize(all_data[i], split_serialized_data[i]);
            }
        }
        return 0;
    }

    template<typename T>
    int CommWorld::Scatter(std::vector<T> &all_data, T &data, int root) {
        int length = 0;
        std::vector<std::byte> merge_all_serialized_data;
        std::vector<std::byte> serialized_data;
        if(this->Rank() == root) {
            std::vector<std::vector<std::byte>> all_serialized_data;
            all_serialized_data.resize(all_data.size());
            for(int i=0; i<all_data.size(); i++) {
                all_serialized_data[i] = serialization::serialize(all_data[i]);
            }
            length = int(all_serialized_data[0].size());
            merge_all_serialized_data = merge_vector<std::byte>(all_serialized_data, length, this->Size());
        }
        this->Broadcast(length, root);
        serialized_data.resize(length);
        MPI_Scatter(&merge_all_serialized_data[0], length, MPI_BYTE, &serialized_data[0], length, MPI_BYTE, root, MPI_COMM_WORLD);
        serialization::deserialize(data, serialized_data);
        return 0;
    }
}

#endif //COMM_WORLD_HPP