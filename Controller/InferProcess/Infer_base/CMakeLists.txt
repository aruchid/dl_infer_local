# 设置CMake最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(infer_process)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置Qt自动处理
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 查找必要的包
find_package(Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Boost相关设置
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# 定义导出宏
add_definitions(-DARC_INFER_PROCESS_LIB)

# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/..  # 添加上层目录
)

# 收集源文件
file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
file(GLOB_RECURSE CURRENT_SOURCES  *.cpp)

# 源文件分组
source_group("Include" FILES ${CURRENT_HEADERS}) 
source_group("Source" FILES ${CURRENT_SOURCES})

# 创建动态库目标
add_library(infer_process SHARED 
    ${CURRENT_HEADERS} 
    ${CURRENT_SOURCES}
)

# 设置目标属性
set_target_properties(infer_process PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
    DEBUG_POSTFIX "d"
)

# 链接依赖库
target_link_libraries(infer_process PRIVATE
    Qt5::Core
    Qt5::Gui
    ${Boost_LIBRARIES}
)

# 安装头文件
install(FILES 
    infer_process_define.h
    infer_process.h
    DESTINATION include/infer_process
)

# 安装库文件
install(TARGETS infer_process 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# 导出配置
install(EXPORT infer_process-config
    DESTINATION cmake
    NAMESPACE ARC::
) 