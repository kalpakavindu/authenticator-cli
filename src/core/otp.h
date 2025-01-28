#pragma once

#include <cstdint>
#include <ctime>
#include <string>

class Otp {
 protected:
  std::string _secret;

 public:
  Otp(const std::string& secret);
  int generate_code(const uint64_t& data);
};

class Totp : public Otp {
 private:
  int _time_step;
  time_t _cur_time;

 private:
  uint64_t _get_counter(time_t* time);

 public:
  Totp(const std::string& secret, int step);
  int now();
  int at(time_t time);
};