#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "hmac_sha256.h"

#define SHA256_HASH_SIZE 32

int main() {
  const std::string secret = "key";
  const std::string data = "The quick brown fox jumps over the lazy dog";
  std::stringstream res;

  std::vector<uint8_t> out(SHA256_HASH_SIZE);

  hmac_sha256(secret.data(), secret.size(), data.data(), data.size(), out.data(), out.size());

  for (uint8_t x : out) {
    res << std::hex << std::setfill('0') << std::setw(2) << (int)x;
  }

  std::cout << "Message : " << data << std::endl;
  std::cout << "Secret  : " << secret << std::endl;
  std::cout << "HMAC    : " << res.str() << std::endl;

  assert(res.str() == "f7bc83f430538424b13298e6aa6fb143ef4d59a14946175997479dbc2d1a3cd8");

  return 0;
}