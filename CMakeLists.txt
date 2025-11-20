project(tmp)
cmake_minimum_required(VERSION 3.23.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(${PROJECT_SOURCE_DIR}/pda-project)

aux_source_directory(${PROJECT_SOURCE_DIR}/pda-project CPP_SRC)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(pda ${CPP_SRC})

