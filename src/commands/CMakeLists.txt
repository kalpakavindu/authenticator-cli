file(GLOB SOURCE_FILES *.cpp *.h)
file(GLOB HEADER_FILES *.h)

add_library(commands STATIC ${SOURCE_FILES})
target_link_libraries(commands PRIVATE core)
target_link_libraries(commands PRIVATE crypto)

install(TARGETS commands DESTINATION ${Authenticator_LIB_DIR})
install(FILES ${HEADER_FILES} DESTINATION ${Authenticator_INC_DIR}/commands)