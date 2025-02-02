#pragma once

#include <string>
#include <vector>

namespace utils {
  std::string generate_uuid();

  std::string b32decode(const std::string& str);

  std::vector<std::string> split(std::string& s, const std::string delimiter);

  void trim(std::string& str, const char c);

  void setTimeOut(int ms);
}  // namespace utils