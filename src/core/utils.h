#pragma once

#include <stdint.h>

#include <array>
#include <stdexcept>
#include <string>
#include <vector>

void b32decode(std::string* str, std::vector<uint8_t>* value);

void int2bytes(int& n, std::array<uint8_t, 8>* value);