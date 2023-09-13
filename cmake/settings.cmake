

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")


if (MSVC)
    add_compile_options(/utf-8) # warning C4819: 该文件包含不能在当前代码页(936)中表示的字符
endif()


option(BUILD_ALL_SAMPLES "Build all samples" OFF)

configure_file(${CMAKE_SOURCE_DIR}/configuration/root_directory.h.in ${CMAKE_SOURCE_DIR}/configuration/root_directory.h)
include_directories(${CMAKE_SOURCE_DIR}/configuration)