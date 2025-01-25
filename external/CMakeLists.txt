add_library(HMACSHA256 SHARED STATIC 
  ${Authenticator_EXT_DIR}/hmac_sha256/sha256.h
  ${Authenticator_EXT_DIR}/hmac_sha256/sha256.c
  ${Authenticator_EXT_DIR}/hmac_sha256/hmac_sha256.h
  ${Authenticator_EXT_DIR}/hmac_sha256/hmac_sha256.c
)

install(TARGETS HMACSHA256 DESTINATION ${Authenticator_LIB_DIR})
install(FILES
  ${Authenticator_EXT_DIR}/hmac_sha256/sha256.h
  ${Authenticator_EXT_DIR}/hmac_sha256/hmac_sha256.h
  DESTINATION ${Authenticator_INC_DIR}
)