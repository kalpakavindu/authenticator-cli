file(GLOB SOURCE_FILES *.cpp *.hpp)
file(GLOB HEADER_FILES *.hpp)

add_library(Core SHARED STATIC ${SOURCE_FILES})

install(TARGETS Core DESTINATION ${Authenticator_LIB_DIR})
install(FILES ${HEADER_FILES} DESTINATION ${Authenticator_INC_DIR})