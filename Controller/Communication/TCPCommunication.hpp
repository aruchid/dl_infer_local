#pragma once
#include "ICommunication.hpp"
#include <boost/asio.hpp>

namespace txr {
namespace communication {

class TCPCommunicationImpl : public ICommunicationImpl {
public:
    TCPCommunicationImpl(const std::string& ip, uint16_t port);
    ~TCPCommunicationImpl() override;
    
    bool connect() override;
    bool disconnect() override;
    bool isConnected() const override;
    bool send(const std::vector<uint8_t>& data) override;
    bool receive(std::vector<uint8_t>& data) override;
    std::string getStatus() const override;
    std::string getLastError() const override;

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    std::string ip_;
    uint16_t port_;
    std::string last_error_;
    bool connected_;
};

class TCPCommunication : public Communication {
public:
    TCPCommunication(const std::string& ip, uint16_t port)
        : Communication(std::make_unique<TCPCommunicationImpl>(ip, port)) {}
};

} // namespace communication
} // namespace txr 