#pragma once

#include <stdint.h>

#include <array>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<uint8_t> b32decode(std::string& str);

std::array<uint8_t, 8> int2bytes(int& n);