//
//  logger.hpp
//  server_exp
//
//  Created by MAC on 30.06.2020.
//  Copyright © 2020 Yago_Sevatarion. All rights reserved.
//
#define BOOST_LOG_DYN_LINK 1
#pragma once

#include <string>


class Logger
{
    Logger() {}
public:
    static Logger& instance();
    static void setOptions(std::string const& t_fileName, unsigned t_rotationSize,
        unsigned t_maxSize);
};
