/*
 * @Author: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @Date: 2023-06-23 18:18:07
 * @LastEditors: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @LastEditTime: 2023-06-25 18:15:24
 * @FilePath: /Messaging/include/messaging/comm_world.hpp
 * @Description: Header file for communicator.
 *
 * Copyright (c) 2023 by Yaozhenghang.Ma email:Yaozhenghang.Ma@gmail.com, All Rights Reserved.
 */

#ifndef COMM_WORLD_HPP
#define COMM_WORLD_HPP

#include <messaging/config.hpp>
#include <messaging/environment.hpp>

namespace messaging {
    class CommWorld {
    public:
        CommWorld();
        CommWorld(int &argc, char** &argv);
        ~CommWorld();

        int Rank();
        int Size();

    private:
        messaging::Environment env_;
        bool initialized_;
    };
}

#endif //COMM_WORLD_HPP