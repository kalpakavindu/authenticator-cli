find_package(OpenSSL REQUIRED)

file(GLOB SOURCE_FILES *.cpp *.h)

add_library(Core SHARED STATIC ${SOURCE_FILES})

target_include_directories(Core PRIVATE ${OPENSSL_INCLUDE_DIR})
install(TARGETS Core DESTINATION ${Authenticator_LIB_DIR})
install(FILES otp.h utils.h hmac.h DESTINATION ${Authenticator_INC_DIR})