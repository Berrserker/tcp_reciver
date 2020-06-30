//
//  main.cpp
//  server_exp
//
//  Created by MAC on 30.06.2020.
//  Copyright © 2020 Yago_Sevatariob. All rights reserved.
//

#define BOOST_LOG_DYN_LINK 1

#include <iostream>

#include <boost/asio/io_service.hpp>
#include <boost/filesystem.hpp>

#include "server.hpp"
#include "../sup/logger.hpp"

using namespace boost;
int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: server <port> <base cash workDirectory> -- will use default app ::path(workdir/filestorage)??port(5000)\n";
    }
    
    Logger::instance().setOptions("server_%3N.log", 1 * 1024 * 1024, 10 * 1024 * 1024);
    auto current = boost::filesystem::current_path().string();
    current+="/filestorage";
    
    try {
        boost::asio::io_service ioService;
        
        short port = (argc == 3) ? (std::stoi(argv[1])) : (std::stoi("5000"));
        std::string dir = (argc == 3) ? argv[2] : current;
        Server server(ioService, port, dir);

        ioService.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

