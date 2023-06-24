/*
 * @Author: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @Date: 2023-06-23 16:50:02
 * @LastEditors: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @LastEditTime: 2023-06-24 15:30:04
 * @FilePath: /Messaging/test/test.cpp
 * @Description:
 *
 * Copyright (c) 2023 by Yaozhenghang.Ma email:Yaozhenghang.Ma@gmail.com, All Rights Reserved.
 */
#include <iostream>
#include <messaging.hpp>

int main(int argc, char** argv) {
    messaging::CommWorld comm;
    int rank = comm.Rank();
    std::cout << rank << std::endl;
    return 0;
}