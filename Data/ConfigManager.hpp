#pragma once
#include <yaml-cpp/yaml.h>
#include <string>
#include <memory>

class ConfigManager {
public:
    static ConfigManager& getInstance();
    
    // 加载配置文件
    bool loadConfig(const std::string& env = "default");
    
    // 获取当前环境
    std::string getEnv() const { return currentEnv_; }
    
    // 配置获取方法
    template<typename T>
    T get(const std::string& path, const T& defaultValue = T()) const;
    
    // 检查配置项是否存在
    bool exists(const std::string& path) const;

private:
    ConfigManager() = default;
    ~ConfigManager() = default;
    
    YAML::Node config_;
    std::string currentEnv_;
    
    // 从路径获取节点
    YAML::Node getNode(const std::string& path) const;
    // 合并配置
    void mergeConfig(YAML::Node& target, const YAML::Node& source);
};

// 模板方法实现
template<typename T>
T ConfigManager::get(const std::string& path, const T& defaultValue) const {
    try {
        YAML::Node node = getNode(path);
        return node.as<T>(defaultValue);
    } catch (...) {
        return defaultValue;
    }
} 