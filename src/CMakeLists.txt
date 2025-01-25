add_subdirectory(core)

set(SOURCE_FILES main.cpp)
add_executable(Authenticator ${SOURCE_FILES})

target_link_libraries(Authenticator 
  PRIVATE Core
  PRIVATE HMACSHA256
)
target_include_directories(Authenticator 
  PRIVATE ${PROJECT_SOURCE_DIR}/src/core
  PRIVATE ${Authenticator_EXT_DIR}/hmac_sha256
)

install(TARGETS Authenticator DESTINATION ${Authenticator_BIN_DIR})