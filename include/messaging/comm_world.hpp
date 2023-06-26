/*
 * @Author: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @Date: 2023-06-23 18:18:07
 * @LastEditors: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @LastEditTime: 2023-06-25 19:49:31
 * @FilePath: /Messaging/include/messaging/comm_world.hpp
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
}

#endif //COMM_WORLD_HPP