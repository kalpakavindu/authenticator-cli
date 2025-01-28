#include "otp.h"

#include "../crypto/hmac.h"
#include "../crypto/sha1.h"
#include "utils.h"

Otp::Otp(const std::string& secret) {
  Otp::_secret = Utils::b32decode(secret);
}

int Otp::generate_code(const uint64_t& data) {
  std::string byte_data;

  for (int i = 7; i >= 0; --i) {
    byte_data += (char)((data >> (i * 8)) & 0xFF);
  }

  HMAC<SHA1> hmac(Otp::_secret);
  hmac.update(byte_data);
  std::array<uint8_t, SHA1::DIGEST_SIZE> hash = hmac.digest();

  int offset = (hash[SHA1::DIGEST_SIZE - 1] & 0x0F);
  int truncated_hash = ((hash[offset] & 0x7F) << 24 |
                        (hash[offset + 1] & 0xFF) << 16 |
                        (hash[offset + 2] & 0xFF) << 8 |
                        (hash[offset + 3]) & 0xFF);

  return (truncated_hash % 1000000);
}