add_subdirectory(core)
add_subdirectory(crypto)

set(SOURCE_FILES main.cpp)
add_executable(authenticator ${SOURCE_FILES})

target_link_libraries(authenticator 
  PRIVATE core
  PRIVATE crypto
)
target_include_directories(authenticator 
  PRIVATE ${Authenticator_INC_DIR}
  PRIVATE ${PROJECT_SOURCE_DIR}/src
)

install(TARGETS authenticator DESTINATION ${Authenticator_BIN_DIR})