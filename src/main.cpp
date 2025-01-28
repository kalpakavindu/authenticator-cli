#include <iostream>

#include "core/otp.h"

int main() {
  const std::string key = "GEZDGNBVGY3TQOJQGEZDGNBVGY3TQOJQ";
  const uint64_t data = 1111111111;
  Otp otp(key);

  int code = otp.generate_code(data);

  std::cout << code << std::endl;
  return 0;
}