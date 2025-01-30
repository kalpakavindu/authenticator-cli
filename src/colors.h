#pragma once

#include <iostream>

namespace Colors {
  template <class CharT, class Traits>
  constexpr std::basic_ostream<CharT, Traits>& reset(std::basic_ostream<CharT, Traits>& os) {
    return os << "\033[0m";
  }

  template <class CharT, class Traits>
  constexpr std::basic_ostream<CharT, Traits>& green(std::basic_ostream<CharT, Traits>& os) {
    return os << "\033[32m";
  }

  template <class CharT, class Traits>
  constexpr std::basic_ostream<CharT, Traits>& red(std::basic_ostream<CharT, Traits>& os) {
    return os << "\033[31m";
  }

  template <class CharT, class Traits>
  constexpr std::basic_ostream<CharT, Traits>& yellow(std::basic_ostream<CharT, Traits>& os) {
    return os << "\033[33m";
  }

  template <class CharT, class Traits>
  constexpr std::basic_ostream<CharT, Traits>& blue(std::basic_ostream<CharT, Traits>& os) {
    return os << "\033[34m";
  }
}  // namespace Colors