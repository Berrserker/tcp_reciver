//
//  server.hpp
//  server_exp
//
//  Created by MAC on 30.06.2020.
//  Copyright © 2020 Yago_Sevatarion. All rights reserved.
//

#define BOOST_LOG_DYN_LINK 1
#pragma once

#include <array>
#include <fstream>
#include <string>
#include <memory>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

class Session
    : public std::enable_shared_from_this<Session>
{
public:
    using TcpSocket = boost::asio::ip::tcp::socket;

    Session(TcpSocket t_socket);

    void start()
    {
        doRead();
    }

private:
    void doRead();
    void processRead(size_t t_bytesTransferred);
    void createFile();
    void readData(std::istream &stream);
    void doReadFileContent(size_t t_bytesTransferred);
    void handleError(std::string const& t_functionName, boost::system::error_code const& t_ec);


    TcpSocket m_socket;
    enum { MaxLength = 40960 };
    std::array<char, MaxLength> m_buf;
    boost::asio::streambuf m_requestBuf_;
    std::ofstream m_outputFile;
    size_t m_fileSize;
    std::string m_fileName;
    std::string m_filePath;
    boost::filesystem::path efilePath;
    boost::filesystem::path sfilePath;
};


class Server
{
public:
    using TcpSocket = boost::asio::ip::tcp::socket;
    using TcpAcceptor = boost::asio::ip::tcp::acceptor;
    using IoService = boost::asio::io_service;

    Server(IoService& t_ioService, short t_port, std::string const& t_workDirectory);

private:
    void doAccept();
    void createWorkDirectory();

    TcpSocket m_socket;
    TcpAcceptor m_acceptor;

    std::string m_workDirectory;
};
