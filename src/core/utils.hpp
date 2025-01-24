#pragma once

#include <string>
#include <vector>

std::vector<unsigned char> b32decode(const std::string& str);

template <typename T>
std::vector<unsigned char> int2bytes(T value) {
  std::vector<unsigned char> out;
  size_t size = sizeof(T);

  union {
    T integer;
    unsigned char bytes[sizeof(T)];
  } converter;

  converter.integer = value;

  for (size_t i = 0; i < size; ++i) {
    out.push_back(converter.bytes[i]);
  }

  return out;
}