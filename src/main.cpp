#include <cassert>
#include <iostream>

#include "crypto/sha256.h"

int main() {
  const std::string secret = "test";
  SHA256 sha2;

  sha2.update(secret.data(), secret.size());
  std::string hash = sha2.hexdigest();

  std::cout << hash << std::endl;
  assert(hash == "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08");

  return 0;
}