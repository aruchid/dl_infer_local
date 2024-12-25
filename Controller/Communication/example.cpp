#include "TCPCommunication.hpp"
#include "UDPCommunication.hpp"

void example() {
    // 创建TCP通信实例
    txr::communication::TCPCommunication tcp("127.0.0.1", 8080);
    if (tcp.connect()) {
        std::vector<uint8_t> data = {1, 2, 3, 4};
        tcp.send(data);
    }
    
    // 创建UDP通信实例
    txr::communication::UDPCommunication udp("127.0.0.1", 8081);
    if (udp.connect()) {
        std::vector<uint8_t> recv_data;
        udp.receive(recv_data);
    }
} 