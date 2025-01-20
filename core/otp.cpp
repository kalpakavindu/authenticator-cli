#include "otp.h"

std::vector<uint8_t> b32decode(std::string& str) {
  const std::string _b32alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
  std::vector<uint8_t> out;
  int bits = 0;
  uint32_t value = 0;

  for (char c : str) {
    size_t pos = _b32alphabet.find(toupper(c));
    if (pos == std::string::npos) {
      std::invalid_argument("Invalid base32 character");
    }

    // bit accumulation
    value = (value << 5) | pos;
    bits += 5;

    // byte extraction
    if (bits >= 8) {
      out.push_back(value >> (bits - 8));
      bits -= 8;
      value &= (1 << bits) - 1;
    }
  }

  if (bits > 0) {
    out.push_back(value << (8 - bits));
  }

  return out;
}

std::array<uint8_t, 8> int2bytes(int& n) {
  std::array<uint8_t, 8> bytes = {0};
  for (int i = 7; i >= 0; --i) {
    // convert n to it's least significant byte
    bytes[i] = static_cast<uint8_t>(n & 0xFF);
    n >>= 8;
  }
  return bytes;
}