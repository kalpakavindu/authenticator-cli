#include "sha1.h"

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

void SHA1::_init() {
  SHA1::_h[0] = 0x67452301;
  SHA1::_h[1] = 0xEFCDAB89;
  SHA1::_h[2] = 0x98BADCFE;
  SHA1::_h[3] = 0x10325476;
  SHA1::_h[4] = 0xC3D2E1F0;
  SHA1::_data.clear();
}

uint32_t rotl(uint32_t x, uint32_t n) {
  return (((x) << (n)) | ((x) >> (32 - (n))));
}

void SHA1::update(const char* message, size_t length) {
  SHA1::_init();
  uint64_t ml = length * 8;
  for (size_t i = 0; i < length; i++) {
    SHA1::_data.push_back(message[i]);
  }
  SHA1::_data.push_back((char)0x80);  // Append '1' byte
  while (SHA1::_data.size() % SHA1::BLOCK_SIZE != (SHA1::BLOCK_SIZE - 8)) {
    SHA1::_data.push_back((char)0x00);
  }
  // Append message length as big-endian 64-bit integer
  for (int i = 56; i >= 0; i -= 8) {
    SHA1::_data.push_back((char)((ml >> i) & 0xFF));
  }
}

void SHA1::_transform(uint32_t chunk[16]) {
  uint32_t v[5];
  uint32_t w[80];
  for (int i = 0; i < 16; ++i) {
    w[i] = chunk[i];
  }
  for (int i = 16; i < 80; ++i) {
    w[i] = rotl((w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]), 1);
  }
  for (int i = 0; i < 5; ++i) {
    v[i] = SHA1::_h[i];
  }

  // Compress
  for (int i = 0; i < 80; ++i) {
    uint32_t f, u, k;

    if (i < 20) {
      f = (v[3] ^ (v[1] & (v[2] ^ v[3])));
      k = 0x5A827999;
    } else if (i < 40) {
      f = (v[1] ^ v[2] ^ v[3]);
      k = 0x6ED9EBA1;
    } else if (i < 60) {
      f = ((v[1] & v[2]) | (v[1] & v[3]) | (v[2] & v[3]));
      k = 0x8F1BBCDC;
    } else {
      f = (v[1] ^ v[2] ^ v[3]);
      k = 0xCA62C1D6;
    }

    u = rotl(v[0], 5) + f + v[4] + k + w[i];
    v[4] = v[3];
    v[3] = v[2];
    v[2] = rotl(v[1], 30);
    v[1] = v[0];
    v[0] = u;
  }

  for (int i = 0; i < 5; ++i) {
    SHA1::_h[i] = SHA1::_h[i] + v[i];
  }
}

void SHA1::_calculate() {
  uint32_t chunk[16];
  int round = 0;
  for (int i = 0; i < SHA1::_data.size(); i += 4) {
    chunk[round] = (SHA1::_data[i] << 24) |
                   (SHA1::_data[i + 1] << 16) |
                   (SHA1::_data[i + 2] << 8) |
                   (SHA1::_data[i + 3]);
    ++round;

    if (round == 16) {
      SHA1::_transform(chunk);
      round = 0;
    }
  }
}

std::array<uint8_t, SHA1::DIGEST_SIZE> SHA1::digest() {
  SHA1::_calculate();

  std::array<uint8_t, SHA1::DIGEST_SIZE> out;
  int count = 0;

  for (size_t i = 0; i < 5; ++i) {
    out[count] = ((SHA1::_h[i] >> 24) & 0xFF);
    out[count + 1] = ((SHA1::_h[i] >> 16) & 0xFF);
    out[count + 2] = ((SHA1::_h[i] >> 8) & 0xFF);
    out[count + 3] = (SHA1::_h[i] & 0xFF);
    count += 4;
  }

  return out;
}

std::string SHA1::hexdigest() {
  std::stringstream ss;
  std::array<uint8_t, SHA1::DIGEST_SIZE> d = SHA1::digest();
  for (uint8_t x : d) {
    ss << std::hex << std::setfill('0') << std::setw(2) << (int)x;
  }
  return ss.str();
}