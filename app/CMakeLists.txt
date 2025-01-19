add_executable(App "main.cpp" "main.h")

set_property(TARGET App PROPERTY CXX_STANDARD 20)

target_link_libraries(App PRIVATE Authenticator)
target_include_directories(App PRIVATE "../core/")