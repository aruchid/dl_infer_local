#pragma once
#include "ICommunication.hpp"
#include <boost/asio.hpp>

namespace txr {
namespace communication {

class UDPCommunicationImpl : public ICommunicationImpl {
public:
    UDPCommunicationImpl(const std::string& ip, uint16_t port);
    ~UDPCommunicationImpl() override;
    
    bool connect() override;
    bool disconnect() override;
    bool isConnected() const override;
    bool send(const std::vector<uint8_t>& data) override;
    bool receive(std::vector<uint8_t>& data) override;
    std::string getStatus() const override;
    std::string getLastError() const override;

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    std::string last_error_;
    bool connected_;
};

class UDPCommunication : public Communication {
public:
    UDPCommunication(const std::string& ip, uint16_t port)
        : Communication(std::make_unique<UDPCommunicationImpl>(ip, port)) {}
};

} // namespace communication
} // namespace txr 