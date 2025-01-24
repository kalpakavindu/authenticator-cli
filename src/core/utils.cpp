#include "utils.hpp"

#include <cstdint>
#include <stdexcept>

std::vector<unsigned char> b32decode(const std::string& str) {
  std::vector<unsigned char> out;

  const std::string _b32alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
  int bits = 0;
  uint32_t val = 0;

  for (char c : str) {
    size_t pos = _b32alphabet.find(toupper(c));
    if (pos == std::string::npos) {
      std::invalid_argument("Invalid base32 character");
    }

    // bit accumulation
    val = (val << 5) | pos;
    bits += 5;

    // byte extraction
    if (bits >= 8) {
      out.push_back(val >> (bits - 8));
      bits -= 8;
      val &= (1 << bits) - 1;
    }
  }

  if (bits > 0) {
    out.push_back(val << (8 - bits));
  }

  return out;
}