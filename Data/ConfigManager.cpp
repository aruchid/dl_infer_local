#pragma once
#include "ConfigManager.hpp"
#include <iostream>

bool ConfigManager::loadConfig(const std::string& configPath) {
    try {
        config_ = YAML::LoadFile(configPath);
        return true;
    } catch (const YAML::Exception& e) {
        std::cerr << "配置文件加载失败: " << e.what() << std::endl;
        return false;
    }
}

int ConfigManager::getCameraDeviceId() const {
    return config_["camera"]["device_id"].as<int>();
}

int ConfigManager::getCameraWidth() const {
    return config_["camera"]["width"].as<int>();
}

// 其他getter方法的实现... 