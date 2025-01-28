add_subdirectory(core)
add_subdirectory(crypto)

set(SOURCE_FILES main.cpp)
add_executable(Authenticator ${SOURCE_FILES})

target_link_libraries(Authenticator 
  PRIVATE Core
  PRIVATE Crypto
)
target_include_directories(Authenticator 
  PRIVATE ${Authenticator_INC_DIR}
  PRIVATE ${PROJECT_SOURCE_DIR}/src
)

install(TARGETS Authenticator DESTINATION ${Authenticator_BIN_DIR})