add_subdirectory(core)
add_subdirectory(crypto)
add_subdirectory(cli)
add_subdirectory(commands)

set(SOURCE_FILES 
  utils.cpp utils.h
  main.cpp
)
add_executable(authenticator ${SOURCE_FILES})

target_link_libraries(authenticator 
  PRIVATE core
  PRIVATE crypto
  PRIVATE cli
  PRIVATE commands
)
target_include_directories(authenticator 
  PRIVATE ${Authenticator_INC_DIR}
  PRIVATE ${PROJECT_SOURCE_DIR}/src
)

install(TARGETS authenticator DESTINATION ${Authenticator_BIN_DIR})
install(FILES utils.h DESTINATION ${Authenticator_INC_DIR})