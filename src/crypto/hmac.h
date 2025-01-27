#pragma once

#include <array>
#include <string>

constexpr size_t HMAC_BLOCK_SIZE = 64;
constexpr size_t HMAC_DIGEST_SIZE = 32;

class HMAC {
 private:
  std::array<unsigned char, HMAC_BLOCK_SIZE> _ipad;
  std::array<unsigned char, HMAC_BLOCK_SIZE> _opad;

 public:
  HMAC(const std::string& key);
  void update(const std::string& data);
  std::array<uint8_t, HMAC_DIGEST_SIZE> digest();
  std::string hexdigest();
};