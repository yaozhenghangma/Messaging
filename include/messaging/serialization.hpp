/*
 * @Author: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @Date: 2023-06-25 16:25:37
 * @LastEditors: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @LastEditTime: 2023-06-25 19:47:43
 * @FilePath: /Messaging/include/messaging/serialization.hpp
 * @Description:Header file for serialization.
 *
 * Copyright (c) 2023 by Yaozhenghang.Ma email:Yaozhenghang.Ma@gmail.com, All Rights Reserved.
 */

#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

#include <vector>

namespace messaging {
    namespace serialization {
        template<typename T>
        std::vector<std::byte> serialize(T &data);

        template<typename T>
        int deserialize(T &data, std::vector<std::byte> &serialized_data);
    }
}

#endif //SERIALIZATION_HPP