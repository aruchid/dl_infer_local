#pragma once
#include <string>

namespace Config {
    // 相机配置
    constexpr int DEFAULT_CAMERA_ID = 0;
    constexpr int CAMERA_WIDTH = 1920;
    constexpr int CAMERA_HEIGHT = 1080;
    constexpr int CAMERA_FPS = 30;
    
    // 网络配置
    constexpr uint16_t DEFAULT_TCP_PORT = 8080;
    constexpr char DEFAULT_TCP_IP[] = "127.0.0.1";
    
    // 推理配置
    constexpr char MODEL_PATH[] = "../models/model.engine";
    constexpr int BATCH_SIZE = 1;
    
    // 显示配置
    constexpr int DISPLAY_WIDTH = 1280;
    constexpr int DISPLAY_HEIGHT = 720;
    
    // 线程配置
    constexpr int THREAD_SLEEP_MS = 1;
    
    // 日志配置
    constexpr char LOG_PATH[] = "../logs/";
    constexpr bool ENABLE_DEBUG_LOG = true;
} 