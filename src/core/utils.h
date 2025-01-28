#pragma once

#include <string>

namespace Utils {
  std::string generate_uuid();

  std::string b32decode(const std::string& str);
}