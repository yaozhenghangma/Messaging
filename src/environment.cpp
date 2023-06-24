/*
 * @Author: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @Date: 2023-06-23 18:18:17
 * @LastEditors: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @LastEditTime: 2023-06-24 15:26:57
 * @FilePath: /Messaging/src/environment.cpp
 * @Description:
 *
 * Copyright (c) 2023 by Yaozhenghang.Ma email:Yaozhenghang.Ma@gmail.com, All Rights Reserved.
 */

#include <messaging/environment.hpp>

namespace messaging {
#ifdef NO_ARG_INITIALIZATION
    Environment::Environment()
        :initialized_(false), finalized_(false) {
        if(!initialized_) {
            MPI_Init(NULL, NULL);
            initialized_ = true;
            finalized_ = false;
        }
    }
#else
    Environment::Environment()
        :initialized_(false), finalized_(false) {}
#endif

    Environment::Environment(int &argc, char** &argv)
        : initialized_(false), finalized_(false) {
        if(!initialized_) {
            MPI_Init(&argc, &argv);
            initialized_ = true;
            finalized_ = false;
        }
    }

    Environment::~Environment() {
        if(!finalized_) {
            MPI_Finalize();
            finalized_ = true;
        }
    }
}