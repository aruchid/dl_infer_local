#pragma once
#include <boost/asio.hpp>
#include "../../Data/DataManager.hpp"

class TCPController {
public:
    TCPController();
    
    bool startServer(uint16_t port);
    bool connectToServer(const std::string& ip, uint16_t port);
    void sendData(const std::vector<uint8_t>& data);
    void receiveData();

private:
    boost::asio::io_context ioContext_;
    boost::asio::ip::tcp::socket socket_;
    DataManager& dataManager_;
}; 