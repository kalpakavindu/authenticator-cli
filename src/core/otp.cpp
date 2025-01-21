#include "otp.h"

OTP::OTP(std::string& secret, int& digits) {
  d = digits;
  byteSecret = b32decode(secret);
}
