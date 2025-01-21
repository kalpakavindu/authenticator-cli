cmake_minimum_required(VERSION 3.20)
project(Authenticator)

set(CMAKE_CXX_STANDARD 20)

set(Authenticator_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(Authenticator_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(Authenticator_INC_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories(${Authenticator_INC_DIR})

add_subdirectory(src)