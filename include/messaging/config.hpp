/*
 * @Author: Yaozhenghang.Ma Yaozhenghang.Ma@gmail.com
 * @Date: 2023-06-21
 * @FilePath: include/messaging/config.hpp
 * @Description:
 *  This file contains the MPI configuration details that expose
 *  the capabilities of the underlying MPI implementation.
 * Copyright (c) 2023 by Yaozhenghang.Ma email:Yaozhenghang.Ma@gmail.com, All Rights Reserved.
 */

#ifndef MESSAGING_CONFIG_HPP
#define MESSAGING_CONFIG_HPP

#include <mpi.h>

#ifndef MPI_VERSION
#define MPI_VERSION 2
// Assume a safe MPI version if not provided.
#endif

#if MPI_VERSION >= 2
#define NO_ARG_INITIALIZATION
#endif

#endif //MESSAGING_CONFIG_HPP