#include "sha256.h"

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

void SHA256::_init() {
  SHA256::_h[0] = 0x6A09E667;
  SHA256::_h[1] = 0xBB67AE85;
  SHA256::_h[2] = 0x3C6EF372;
  SHA256::_h[3] = 0xA54FF53A;
  SHA256::_h[4] = 0x510E527F;
  SHA256::_h[5] = 0x9B05688C;
  SHA256::_h[6] = 0x1F83D9AB;
  SHA256::_h[7] = 0x5BE0CD19;
  SHA256::_data.clear();
}

uint32_t rotr(uint32_t x, uint32_t n) {
  return (((x) >> (n)) | ((x) << (32 - (n))));
}

uint32_t ch(uint32_t a, uint32_t b, uint32_t c) {
  return (c ^ (a & (b ^ c)));
}

uint32_t maj(uint32_t a, uint32_t b, uint32_t c) {
  return (((a | b) & c) | (a & b));
}

uint32_t sig0(uint32_t x) {
  return (rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22));
}

uint32_t sig1(uint32_t x) {
  return (rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25));
}

uint32_t sum0(uint32_t x) {
  return (rotr(x, 7) ^ rotr(x, 18) ^ ((x & 0xFFFFFFFF) >> 3));
}

uint32_t sum1(uint32_t x) {
  return (rotr(x, 17) ^ rotr(x, 19) ^ ((x & 0xFFFFFFFF) >> 10));
}

void SHA256::update(const char* message, size_t length) {
  SHA256::_init();
  uint64_t ml = length * 8;
  for (size_t i = 0; i < length; i++) {
    SHA256::_data.push_back(message[i]);
  }
  SHA256::_data.push_back((char)0x80);  // Append '1' byte
  while (SHA256::_data.size() % SHA256::BLOCK_SIZE != (SHA256::BLOCK_SIZE - 8)) {
    SHA256::_data.push_back((char)0x00);
  }
  // Append message length as big-endian 64-bit integer
  for (int i = 56; i >= 0; i -= 8) {
    SHA256::_data.push_back((char)((ml >> i) & 0xFF));
  }
}

void SHA256::_transform(uint32_t chunk[16]) {
  uint32_t v[8];
  uint32_t w[64];
  for (int i = 0; i < 16; ++i) {
    w[i] = chunk[i];
  }
  for (int i = 16; i < 64; ++i) {
    w[i] = w[i - 16] + sum0(w[i - 15]) + w[i - 7] + sum1(w[i - 2]);
  }
  for (int i = 0; i < 8; ++i) {
    v[i] = SHA256::_h[i];
  }

  // Compress
  for (int i = 0; i < 64; ++i) {
    uint32_t t1 = v[7] + sig1(v[4]) + ch(v[4], v[5], v[6]) + K[i] + w[i];
    uint32_t t2 = sig0(v[0]) + maj(v[0], v[1], v[2]);

    v[7] = v[6];
    v[6] = v[5];
    v[5] = v[4];
    v[4] = v[3] + t1;
    v[3] = v[2];
    v[2] = v[1];
    v[1] = v[0];
    v[0] = t1 + t2;
  }

  for (int i = 0; i < 8; ++i) {
    SHA256::_h[i] += v[i];
  }
}

void SHA256::_calculate() {
  uint32_t chunk[16];
  int round = 0;
  for (int i = 0; i < SHA256::_data.size(); i += 4) {
    chunk[round] = (SHA256::_data[i] << 24) |
                   (SHA256::_data[i + 1] << 16) |
                   (SHA256::_data[i + 2] << 8) |
                   (SHA256::_data[i + 3]);
    ++round;

    if (round == 16) {
      SHA256::_transform(chunk);
      round = 0;
    }
  }
}

std::array<uint8_t, SHA256::DIGEST_SIZE> SHA256::digest() {
  SHA256::_calculate();

  std::array<uint8_t, SHA256::DIGEST_SIZE> out;
  int count = 0;

  for (size_t i = 0; i < 8; ++i) {
    out[count] = ((SHA256::_h[i] >> 24) & 0xFF);
    out[count + 1] = ((SHA256::_h[i] >> 16) & 0xFF);
    out[count + 2] = ((SHA256::_h[i] >> 8) & 0xFF);
    out[count + 3] = (SHA256::_h[i] & 0xFF);
    count += 4;
  }

  return out;
}

std::string SHA256::hexdigest() {
  std::stringstream ss;
  std::array<uint8_t, SHA256::DIGEST_SIZE> d = SHA256::digest();
  for (uint8_t x : d) {
    ss << std::hex << std::setfill('0') << std::setw(2) << (int)x;
  }
  return ss.str();
}