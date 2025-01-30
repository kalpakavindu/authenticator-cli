set(Commander_SRC_DIR ${Authenticator_EXT_DIR}/cpp-commander/Commander)
file(GLOB Commander_SOURCE_FILES ${Commander_SRC_DIR}/*.cpp ${Commander_SRC_DIR}/*.hpp)
file(GLOB Commander_HEADER_FILES ${Commander_SRC_DIR}/*.hpp)

add_library(commander STATIC ${Commander_SOURCE_FILES})

install(TARGETS commander DESTINATION ${Authentication_LIB_DIR}/dependencies)
install(FILES ${Commander_HEADER_FILES} DESTINATION ${Authentication_INC_DIR}/dependencies/cpp-commander)