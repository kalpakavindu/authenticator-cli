#include <cassert>
#include <iostream>

#include "core/otp.h"

int main() {
  const std::string key = "GEZDGNBVGY3TQOJQGEZDGNBVGY3TQOJQ";
  Totp otp(key, 30);

  std::cout << otp.at(1111111111) << std::endl;
  std::cout << otp.at(1234567890) << std::endl;
  std::cout << otp.at(2000000000) << std::endl;

  assert(otp.at(1111111111) == 50471);
  assert(otp.at(1234567890) == 5924);
  assert(otp.at(2000000000) == 279037);
  return 0;
}