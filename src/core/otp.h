#pragma once

#include "utils.h"

class OTP {
  std::vector<uint8_t> byteSecret;
  int d;

 public:
  OTP(std::string& secret, int& digits);
};