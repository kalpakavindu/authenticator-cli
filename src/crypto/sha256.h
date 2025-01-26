#pragma once
#include <array>
#include <cstdint>
#include <string>

constexpr size_t SHA256_DIGEST_SIZE = 32;

class SHA256 {
 private:
  uint32_t h[8];

 private:
  void transform(uint32_t chunk[16]);
  void calculate();
  void init();

 public:
  SHA256() {};
  void update(const char* message, size_t length);
  std::array<uint8_t, SHA256_DIGEST_SIZE> digest();
  std::string hexdigest();
};