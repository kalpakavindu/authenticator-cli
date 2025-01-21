file(GLOB SOURCE_FILES *.cpp *.h)

add_library(Core SHARED STATIC ${SOURCE_FILES})
install(TARGETS Core DESTINATION ${Authenticator_LIB_DIR})
install(FILES otp.h utils.h DESTINATION ${Authenticator_INC_DIR})