/*
 * @Author: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @Date: 2023-06-23 18:18:25
 * @LastEditors: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @LastEditTime: 2023-06-24 15:29:46
 * @FilePath: /Messaging/src/comm_world.cpp
 * @Description:
 *
 * Copyright (c) 2023 by Yaozhenghang.Ma email:Yaozhenghang.Ma@gmail.com, All Rights Reserved.
 */

#include <iostream>
#include <messaging/comm_world.hpp>

namespace messaging {
    CommWorld::CommWorld()
        : initialized_(false) {
#ifdef NO_ARG_INITIALIZATION
        initialized_ = true;
#else
#endif

    }

    CommWorld::CommWorld(int &argc, char** &argv)
        : initialized_(false) {
        if(!initialized_) {
            env_ = messaging::Environment(argc, argv);
            initialized_ = true;
        }
    }

    CommWorld::~CommWorld() {
    }

    int CommWorld::Rank() {
        if(initialized_) {
            int rank;
            MPI_Comm_rank(MPI_COMM_WORLD, &rank);
            return rank;
        } else {
            std::cout << "Uninitialized MPI environment. Note: the initialization function with command-line arguments should be used for MPI under version 2." << std::endl;
            exit(-1);
        }
    }
}