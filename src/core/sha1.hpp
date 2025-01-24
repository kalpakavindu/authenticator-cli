#pragma once

#include <cstdint>
#include <string>

class SHA1 {
 public:
  SHA1();
  void update(const std::string &s);
  std::string final();

 private:
  uint32_t digest[5];
  std::string buffer;
  uint64_t transforms;
};
