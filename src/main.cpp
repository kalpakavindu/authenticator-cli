#include <iostream>

#include "core/otp.h"

int main() {
  const std::string key = "GEZDGNBVGY3TQOJQGEZDGNBVGY3TQOJQ";
  const uint64_t data = 0;
  Otp otp(key);

  std::string code = otp.generate_code(data);

  std::cout << code << std::endl;
  return 0;
}