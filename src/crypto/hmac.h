#pragma once

#include <array>
#include <cstdint>
#include <string>

// Be careful! this is a template.
template <class H>
class HMAC {
 private:
  H _hash;
  std::array<unsigned char, H::BLOCK_SIZE> _ipad, _opad;
  std::array<unsigned char, H::BLOCK_SIZE> _byte_key;
  std::string _data;

 private:
  void _calculate() {
    std::string inner_data;
    for (unsigned char c : _ipad) {
      inner_data += (char)c;
    }
    inner_data += HMAC::_data;
    HMAC::_hash.update(inner_data.data(), inner_data.size());
    std::array<uint8_t, H::DIGEST_SIZE> inner_hash = HMAC::_hash.digest();

    std::string outer_data;
    for (unsigned char c : _opad) {
      outer_data += (char)c;
    }
    for (uint8_t x : inner_hash) {
      outer_data += (char)x;
    }
    HMAC::_hash.update(outer_data.data(), outer_data.size());
  }

 public:
  HMAC(const std::string& key) {
    size_t cur_size = 0;

    if (key.size() > H::BLOCK_SIZE) {
      // Create Hash
      HMAC::_hash.update(key.data(), key.size());
      std::array<uint8_t, H::DIGEST_SIZE> hash = HMAC::_hash.digest();

      for (size_t i = 0; i < H::DIGEST_SIZE; ++i) {
        HMAC::_byte_key[i] = (char)hash[i];
      }
      cur_size = H::DIGEST_SIZE;
    } else {
      for (size_t i = 0; i < key.size(); ++i) {
        HMAC::_byte_key[i] = ((char)key[i]);
      }
      cur_size = key.size();
    }

    // Append trailing zeros
    if (cur_size < H::BLOCK_SIZE) {
      for (size_t i = cur_size; i < H::BLOCK_SIZE; ++i) {
        HMAC::_byte_key[i] = (char)0x00;
      }
    }
  }

  void update(const std::string& data) {
    HMAC::_data = data;

    for (size_t i = 0; i < H::BLOCK_SIZE; ++i) {
      HMAC::_opad[i] = HMAC::_byte_key[i] ^ (char)0x5c;
      HMAC::_ipad[i] = HMAC::_byte_key[i] ^ (char)0x36;
    }
  }

  std::array<uint8_t, H::DIGEST_SIZE> digest() {
    HMAC::_calculate();
    return HMAC::_hash.digest();
  }

  std::string hexdigest() {
    HMAC::_calculate();
    return HMAC::_hash.hexdigest();
  }
};