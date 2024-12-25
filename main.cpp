#pragma once
#include <QApplication>
#include <QDebug>
#include <memory>
#include "Interface/MainWindow.hpp"
#include "Data/DataManager.hpp"
#include "Data/ConfigManager.hpp"

int main(int argc, char *argv[]) {
    try {
        // 初始化Qt应用程序
        QApplication app(argc, argv);
        
        // 加载配置文件
        ConfigManager& configManager = ConfigManager::getInstance();
        if (!configManager.loadConfig()) {
            qCritical() << "配置文件加载失败";
            return -1;
        }
        
        // 获取数据管理器实例
        DataManager& dataManager = DataManager::getInstance();
        
        // 创建并显示主窗口
        std::unique_ptr<MainWindow> mainWindow = std::make_unique<MainWindow>();
        mainWindow->show();
        
        // 进入Qt事件循环
        return app.exec();
        
    } catch (const std::exception& e) {
        qCritical() << "程序发生异常:" << e.what();
        return -1;
    } catch (...) {
        qCritical() << "程序发生未知异常";
        return -1;
    }
} 