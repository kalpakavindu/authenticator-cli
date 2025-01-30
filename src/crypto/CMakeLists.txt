file(GLOB SOURCE_FILES *.cpp *.h)
file(GLOB HEADER_FILES *.h)

add_library(crypto SHARED STATIC ${SOURCE_FILES})

install(TARGETS crypto DESTINATION ${Authenticator_LIB_DIR})
install(FILES ${HEADER_FILES} DESTINATION ${Authenticator_INC_DIR}/crypto)