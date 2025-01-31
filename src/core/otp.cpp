#include "otp.h"

#include "crypto/hmac.h"
#include "crypto/sha1.h"
#include "utils.h"

namespace core {
  Otp::Otp(const std::string& secret) {
    Otp::_secret = utils::b32decode(secret);
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

  Totp::Totp(const std::string& secret, int step) : Otp(secret) {
    Totp::_time_step = step;
    Totp::_cur_time = std::time(nullptr);
  }

  uint64_t Totp::_get_counter(time_t* time) {
    if (time)
      return *time / Totp::_time_step;

    return Totp::_cur_time / Totp::_time_step;
  }

  int Totp::now() {
    uint64_t counter = Totp::_get_counter(nullptr);
    return Totp::generate_code(counter);
  }

  int Totp::at(time_t time) {
    uint64_t counter = Totp::_get_counter(&time);
    return Totp::generate_code(counter);
  }
}  // namespace core