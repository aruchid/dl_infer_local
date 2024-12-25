# 控制器模块说明

## 目录结构

本目录包含了系统的各个控制模块，每个子目录负责特定的功能域：

## Communication（通讯模块）
负责系统与外部设备的通信功能：
- TCPController: TCP服务器/客户端通信
- UDPController: UDP通信功能
- SerialController: 串口通信功能
- 支持多种通信协议和数据格式

## DisplayProcess（显示处理模块）
负责图像显示和可视化相关功能：
- DisplayController: 管理图像显示逻辑
- 支持多种显示模式（原始图像、处理后图像、叠加结果等）
- 处理显示刷新和图像渲染
- 提供图像标注和可视化功能

## InferProcess（推理处理模块）
负责图像处理和深度学习推理：
- ImageProcessor: 图像预处理和后处理
- TensorRTController: 深度学习模型推理
- 支持多种图像处理算法
- 管理模型加载和推理过程

## InputCamera（输入相机模块）
负责管理各类输入源：
- CameraController: 相机设备控制
- VideoController: 视频文件输入
- ImageController: 图片文件输入
- 提供统一的数据采集接口

## 主要特点
- 模块化设计，各模块独立运行
- 统一的数据流管理
- 线程安全的数据交互
- 可扩展的接口设计

## 使用说明
1. 每个模块都通过DataManager与其他模块交互
2. 所有模块都支持异步操作
3. 可以根据需求启用或禁用特定模块
4. 模块间通过标准接口通信，便于扩展 