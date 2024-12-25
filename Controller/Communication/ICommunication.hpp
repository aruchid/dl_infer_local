#pragma once
#include <string>
#include <vector>
#include <memory>

namespace txr {
namespace communication {

// 通信接口的抽象类
class ICommunication {
public:
    virtual ~ICommunication() = default;
    
    // 基础通信接口
    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual bool isConnected() const = 0;
    
    // 数据收发接口
    virtual bool send(const std::vector<uint8_t>& data) = 0;
    virtual bool receive(std::vector<uint8_t>& data) = 0;
    
    // 状态查询
    virtual std::string getStatus() const = 0;
    virtual std::string getLastError() const = 0;
};

// 通信实现的抽象类
class ICommunicationImpl {
public:
    virtual ~ICommunicationImpl() = default;
    
    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual bool isConnected() const = 0;
    virtual bool send(const std::vector<uint8_t>& data) = 0;
    virtual bool receive(std::vector<uint8_t>& data) = 0;
    virtual std::string getStatus() const = 0;
    virtual std::string getLastError() const = 0;
};

// 通信基类（桥接模式）
class Communication : public ICommunication {
public:
    explicit Communication(std::unique_ptr<ICommunicationImpl> impl)
        : impl_(std::move(impl)) {}
    
    bool connect() override {
        return impl_->connect();
    }
    
    bool disconnect() override {
        return impl_->disconnect();
    }
    
    bool isConnected() const override {
        return impl_->isConnected();
    }
    
    bool send(const std::vector<uint8_t>& data) override {
        return impl_->send(data);
    }
    
    bool receive(std::vector<uint8_t>& data) override {
        return impl_->receive(data);
    }
    
    std::string getStatus() const override {
        return impl_->getStatus();
    }
    
    std::string getLastError() const override {
        return impl_->getLastError();
    }

protected:
    std::unique_ptr<ICommunicationImpl> impl_;
};

} // namespace communication
} // namespace txr 