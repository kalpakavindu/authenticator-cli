#include "otp.h"

#include <iostream>

OTP::OTP(std::string& secret, int digits) {
  b32decode(&secret, &_byte_secret);
  _digits = digits;
}

std::string OTP::generate_otp(int& data) { return ""; }