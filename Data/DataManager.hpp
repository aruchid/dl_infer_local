#pragma once
#include <memory>
#include "SharedMemory.hpp"
#include "StateManager.hpp"
#include "CacheManager.hpp"
#include "ConfigManager.hpp"

class DataManager {
public:
    static DataManager& getInstance();
    
    // 获取各个管理器的实例
    SharedMemory& getSharedMemory() { return *sharedMemory_; }
    StateManager& getStateManager() { return *stateManager_; }
    CacheManager& getCacheManager() { return *cacheManager_; }
    ConfigManager& getConfigManager() { return *configManager_; }

private:
    DataManager();
    ~DataManager() = default;
    
    std::unique_ptr<SharedMemory> sharedMemory_;
    std::unique_ptr<StateManager> stateManager_;
    std::unique_ptr<CacheManager> cacheManager_;
    std::unique_ptr<ConfigManager> configManager_;
}; 