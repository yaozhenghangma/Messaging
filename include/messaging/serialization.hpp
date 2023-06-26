/*
 * @Author: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @Date: 2023-06-25
 * @FilePath: include/messaging/serialization.hpp
 * @Description:
 *  Header file for serialization.
 * Copyright (c) 2023 by Yaozhenghang.Ma email:Yaozhenghang.Ma@gmail.com, All Rights Reserved.
 */

#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

#include <vector>

#ifdef __cplusplus
#if __cplusplus >= 202002L
#endif
//TODO: c++ standard under 20
#endif //__cplusplus

#include <zpp_bits.h>

namespace messaging {
    namespace serialization {
        template<typename T>
        std::vector<std::byte> serialize(T &data) {
            auto [serialized_data, out] = zpp::bits::data_out();
            static_cast<void>(out(data));
            return serialized_data;
        }

        template<typename T>
        int deserialize(T &data, std::vector<std::byte> &serialized_data) {
            auto [serialized_data_to_decode, in] = zpp::bits::data_in();
            serialized_data_to_decode = serialized_data;
            static_cast<void>(in(data));
            return 0;
        }
    }
}

#endif //SERIALIZATION_HPP