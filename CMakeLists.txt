cmake_minimum_required(VERSION 3.20)
project(Authenticator)

set(CMAKE_CXX_STANDARD 17)
set(Authenticator_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(Authenticator_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(Authenticator_INC_DIR ${PROJECT_SOURCE_DIR}/include)
set(Authenticator_EXT_DIR ${PROJECT_SOURCE_DIR}/dependencies)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
  ${Authenticator_EXT_DIR}/
)

add_subdirectory(src)
add_subdirectory(dependencies)