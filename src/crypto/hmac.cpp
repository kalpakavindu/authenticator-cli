#include "hmac.h"

#include <bitset>
#include <iostream>

#include "sha256.h"

std::array<unsigned char, HMAC_BLOCK_SIZE> byte_key;
std::string byte_data;
SHA256 sha2;

HMAC::HMAC(const std::string& key) {
  size_t cur_size = 0;

  if (key.size() > HMAC_BLOCK_SIZE) {
    // Create Hash
    sha2.update(key.data(), key.size());
    std::array<uint8_t, SHA256_DIGEST_SIZE> hash = sha2.digest();

    for (size_t i = 0; i < SHA256_DIGEST_SIZE; ++i) {
      byte_key[i] = (char)hash[i];
    }
    cur_size = SHA256_DIGEST_SIZE;
  } else {
    for (size_t i = 0; i < key.size(); ++i) {
      byte_key[i] = ((char)key[i]);
    }
    cur_size = key.size();
  }

  // Append trailing zeros
  if (cur_size < HMAC_BLOCK_SIZE) {
    for (size_t i = cur_size; i < HMAC_BLOCK_SIZE; ++i) {
      byte_key[i] = (char)0x00;
    }
  }
}

void HMAC::update(const std::string& data) {
  byte_data = data;

  for (size_t i = 0; i < HMAC_BLOCK_SIZE; ++i) {
    HMAC::_opad[i] = byte_key[i] ^ (char)0x5c;
    HMAC::_ipad[i] = byte_key[i] ^ (char)0x36;
  }
}

std::array<uint8_t, HMAC_DIGEST_SIZE> HMAC::digest() {
  std::string inner_data;
  for (unsigned char c : _ipad) {
    inner_data += (char)c;
  }
  inner_data += byte_data;
  sha2.update(inner_data.data(), inner_data.size());
  std::array<uint8_t, HMAC_DIGEST_SIZE> inner_hash = sha2.digest();

  std::string outer_data;
  for (unsigned char c : _opad) {
    outer_data += (char)c;
  }
  for (uint8_t x : inner_hash) {
    outer_data += (char)x;
  }
  sha2.update(outer_data.data(), outer_data.size());
  std::array<uint8_t, HMAC_DIGEST_SIZE> outer_hash = sha2.digest();
  return outer_hash;
}

std::string HMAC::hexdigest() {
  std::string inner_data;
  for (unsigned char c : _ipad) {
    inner_data += (char)c;
  }
  inner_data += byte_data;
  sha2.update(inner_data.data(), inner_data.size());
  std::array<uint8_t, HMAC_DIGEST_SIZE> inner_hash = sha2.digest();

  std::string outer_data;
  for (unsigned char c : _opad) {
    outer_data += (char)c;
  }
  for (uint8_t x : inner_hash) {
    outer_data += (char)x;
  }
  sha2.update(outer_data.data(), outer_data.size());
  std::string outer_hash = sha2.hexdigest();
  return outer_hash;
}