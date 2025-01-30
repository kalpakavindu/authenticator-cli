#include "utils.h"

#include <random>
#include <sstream>

namespace core {
  namespace utils {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);
    static const std::string _b32alpabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

    std::string generate_uuid() {
      std::stringstream ss;
      int i;
      ss << std::hex;
      for (i = 0; i < 8; i++) {
        ss << dis(gen);
      }
      ss << "-";
      for (i = 0; i < 4; i++) {
        ss << dis(gen);
      }
      ss << "-4";
      for (i = 0; i < 3; i++) {
        ss << dis(gen);
      }
      ss << "-";
      ss << dis2(gen);
      for (i = 0; i < 3; i++) {
        ss << dis(gen);
      }
      ss << "-";
      for (i = 0; i < 12; i++) {
        ss << dis(gen);
      };
      return ss.str();
    }

    std::string b32decode(const std::string& str) {
      std::string decoded;
      int bits = 0;
      unsigned int value = 0;

      for (char c : str) {
        size_t pos = _b32alpabet.find(toupper(c));
        if (pos == std::string::npos) {
          return "";
        }

        value = (value << 5) | pos;

        bits += 5;

        if (bits >= 8) {
          decoded += (char)(value >> (bits - 8) & 0xFF);
          bits -= 8;
        }
      }

      if (bits > 0) {
        decoded += (char)(value << (8 - bits) & 0xFF);
      }
      return decoded;
    }
  }  // namespace utils
}  // namespace core