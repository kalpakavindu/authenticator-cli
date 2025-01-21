add_subdirectory(core)

set(SOURCE_FILES main.cpp)

add_executable(Authenticator ${SOURCE_FILES})

target_link_libraries(Authenticator PRIVATE Core)
target_include_directories(Authenticator PRIVATE ./core)

install(TARGETS Authenticator DESTINATION ${Authenticator_BIN_DIR})