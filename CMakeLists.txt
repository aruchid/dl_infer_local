cmake_minimum_required(VERSION 3.16)
project(YourProjectName VERSION 1.0.0 LANGUAGES CXX)

# 包含模块文件
include(cmake/modules.cmake)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 查找所有依赖包
find_all_packages()

# 源文件
file(GLOB_RECURSE SOURCES
    "main.cpp"
    "Interface/*.cpp"
    "Controller/*/*.cpp"
    "Data/*.cpp"
)

# 头文件
file(GLOB_RECURSE HEADERS
    "Interface/*.hpp"
    "Controller/*/*.hpp"
    "Data/*.hpp"
)

# Qt UI文件
file(GLOB UI_FILES "Interface/*.ui")

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI_FILES})

# 设置包含目录
set_all_includes(${PROJECT_NAME})

# Qt自动生成
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

# 链接所有依赖库
link_all_libraries(${PROJECT_NAME})

# 复制配置文件到构建目录
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# 安装规则
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY config/
    DESTINATION etc/${PROJECT_NAME}
    FILES_MATCHING PATTERN "*.yaml"
)

# 添加测试
option(BUILD_TESTS "Build the tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# 版本信息
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.h
)

# 调试信息
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "Qt version: ${Qt5_VERSION}")
message(STATUS "Boost version: ${Boost_VERSION}")
message(STATUS "CUDA version: ${CUDA_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}") 