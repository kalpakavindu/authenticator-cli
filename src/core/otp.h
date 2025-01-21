#pragma once

#include <openssl/evp.h>
#include <openssl/hmac.h>

#include "utils.h"

class OTP {
  std::vector<uint8_t> _byte_secret;
  int _digits;

 public:
  OTP(std::string& secret, int digits);

  std::string generate_otp(int& data);
};