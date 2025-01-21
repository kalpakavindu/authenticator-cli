#include "utils.h"

void b32decode(std::string* str, std::vector<uint8_t>* value) {
  value->clear();

  const std::string _b32alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
  int bits = 0;
  uint32_t val = 0;

  for (char c : *str) {
    size_t pos = _b32alphabet.find(toupper(c));
    if (pos == std::string::npos) {
      std::invalid_argument("Invalid base32 character");
    }

    // bit accumulation
    val = (val << 5) | pos;
    bits += 5;

    // byte extraction
    if (bits >= 8) {
      value->push_back(val >> (bits - 8));
      bits -= 8;
      val &= (1 << bits) - 1;
    }
  }

  if (bits > 0) {
    value->push_back(val << (8 - bits));
  }
}

void int2bytes(int& n, std::array<uint8_t, 8>* value) {
  *value = {0};
  for (int i = 7; i >= 0; --i) {
    // convert n to it's least significant byte
    (*value)[i] = static_cast<uint8_t>(n & 0xFF);
    n >>= 8;
  }
}