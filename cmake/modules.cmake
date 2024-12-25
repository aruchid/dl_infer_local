# 设置CMake模块路径
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/modules)

# Qt配置
macro(find_qt)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
    find_package(Qt5 COMPONENTS 
        Core 
        Widgets 
        Gui 
        Network 
        REQUIRED
    )
endmacro()

# OpenCV配置
macro(find_opencv)
    find_package(OpenCV REQUIRED)
    if(OpenCV_FOUND)
        message(STATUS "OpenCV Found: ${OpenCV_VERSION}")
    else()
        message(FATAL_ERROR "OpenCV not found")
    endif()
endmacro()

# Boost配置
macro(find_boost)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    find_package(Boost COMPONENTS 
        system 
        thread 
        filesystem 
        REQUIRED
    )
    if(Boost_FOUND)
        message(STATUS "Boost Found: ${Boost_VERSION}")
    else()
        message(FATAL_ERROR "Boost not found")
    endif()
endmacro()

# CUDA配置
macro(find_cuda)
    find_package(CUDA REQUIRED)
    if(CUDA_FOUND)
        message(STATUS "CUDA Found: ${CUDA_VERSION}")
        # CUDA编译选项
        set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-O3;-G;-g)
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-G;-g)
        endif()
    else()
        message(FATAL_ERROR "CUDA not found")
    endif()
endmacro()

# TensorRT配置
macro(find_tensorrt)
    find_package(TensorRT REQUIRED)
    if(TensorRT_FOUND)
        message(STATUS "TensorRT Found: ${TensorRT_VERSION}")
    else()
        message(FATAL_ERROR "TensorRT not found")
    endif()
endmacro()

# yaml-cpp配置
macro(find_yaml_cpp)
    find_package(yaml-cpp REQUIRED)
    if(yaml-cpp_FOUND)
        message(STATUS "yaml-cpp Found")
    else()
        message(FATAL_ERROR "yaml-cpp not found")
    endif()
endmacro()

# 所有依赖包的查找
macro(find_all_packages)
    find_qt()
    find_opencv()
    find_boost()
    find_cuda()
    find_tensorrt()
    find_yaml_cpp()
endmacro()

# 设置所有包的包含目录
macro(set_all_includes target)
    target_include_directories(${target} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${OpenCV_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        ${CUDA_INCLUDE_DIRS}
        ${TensorRT_INCLUDE_DIRS}
    )
endmacro()

# 链接所有依赖库
macro(link_all_libraries target)
    target_link_libraries(${target} PRIVATE
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        Qt5::Network
        ${OpenCV_LIBS}
        ${Boost_LIBRARIES}
        yaml-cpp
        ${CUDA_LIBRARIES}
        ${TensorRT_LIBRARIES}
    )
endmacro() 