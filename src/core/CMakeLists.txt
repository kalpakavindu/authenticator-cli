file(GLOB SOURCE_FILES *.cpp *.h)
file(GLOB HEADER_FILES *.h)

add_library(core SHARED STATIC ${SOURCE_FILES})

install(TARGETS core DESTINATION ${Authenticator_LIB_DIR})
install(FILES ${HEADER_FILES} DESTINATION ${Authenticator_INC_DIR}/core)