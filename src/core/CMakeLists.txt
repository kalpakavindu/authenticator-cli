file(GLOB SOURCE_FILES *.cpp *.h)
add_library(Core SHARED STATIC ${SOURCE_FILES})

target_link_libraries(Core PRIVATE OpenSSL::Crypto)
target_include_directories(Core PRIVATE ${OPENSSL_INCLUDE_DIR})

install(TARGETS Core DESTINATION ${Authenticator_LIB_DIR})
install(FILES otp.h utils.h DESTINATION ${Authenticator_INC_DIR})