#pragma once

#include <string>

namespace core {
  namespace utils {
    std::string generate_uuid();

    std::string b32decode(const std::string& str);
  }  // namespace utils
}  // namespace core