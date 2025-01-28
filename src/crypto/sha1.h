#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

class SHA1 {
 public:
  static const size_t DIGEST_SIZE = 20;
  static const size_t BLOCK_SIZE = 64;

 private:
  uint32_t _h[5];
  std::vector<unsigned char> _data;

 private:
  void _transform(uint32_t chunk[16]);
  void _calculate();
  void _init();

 public:
  SHA1() {};
  void update(const char* message, size_t length);
  std::array<uint8_t, SHA1::DIGEST_SIZE> digest();
  std::string hexdigest();
};