#pragma once

#include <cstdint>
#include <string>

class Otp {
 protected:
  std::string _secret;

 public:
  Otp(const std::string& secret);
  int generate_code(const uint64_t& data);
};