# ============================================================
# PDA (下推自动机) 模拟器 - CMake 配置文件
# 课程: 形式语言与自动机 (2025秋)
# ============================================================

# 项目名称
project(PDA_Simulator)

# CMake 最低版本要求 (不要修改)
cmake_minimum_required(VERSION 3.23.0)

# ============================================================
# C++ 标准设置
# ============================================================

# 使用 C++20 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================
# 调试和优化选项
# ============================================================

# 如果没有指定构建类型，默认为 Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Debug 模式：添加调试符号，禁用优化
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall")
    message(STATUS "Debug 模式已启用 (包含调试符号)")
endif()

# Release 模式：优化性能
if(CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    message(STATUS "Release 模式已启用 (性能优化)")
endif()

# ============================================================
# 项目目录结构
# ============================================================

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/pda-project/include)

# 收集所有源文件
# src 目录下的所有 .cpp 文件
aux_source_directory(${PROJECT_SOURCE_DIR}/pda-project/src SRC_FILES)

# ============================================================
# 生成可执行文件
# ============================================================

# 设置可执行文件输出路径为 bin 目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 生成名为 pda 的可执行文件
add_executable(pda ${SRC_FILES})

# ============================================================
# 编译与运行说明
# ============================================================
# 1. 创建构建目录: cmake -B build
# 2. 编译项目: cd ./build; make
# 3. 运行程序: ./bin/pda <pda文件> <输入串>
# 
# 示例:
#   ./bin/pda anbn.pda aaabbb
#   ./bin/pda case.pda "(()())"
# ============================================================
