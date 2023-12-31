/*
 * @Author: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @Date: 2023-06-23
 * @FilePath: include/messaging/environment.hpp
 * @Description:
 *
 * Copyright (c) 2023 by Yaozhenghang.Ma email:Yaozhenghang.Ma@gmail.com, All Rights Reserved.
 */

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <messaging/config.hpp>

namespace messaging {
    class Environment {
    public:
        Environment();
        Environment(int &argc, char** &argv);
        ~Environment();
    private:
        bool initialized_;
        bool finalized_;
    };
}

#endif //ENVIRONMENT_HPP