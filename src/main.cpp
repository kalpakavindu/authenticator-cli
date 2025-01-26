#include <cassert>
#include <iostream>

#include "crypto/hmac.h"

int main() {
  const std::string secret = "key";
  const std::string data = "The quick brown fox jumps over the lazy dog";
  HMAC hmac(secret);

  hmac.update(data);
  std::string hash = hmac.hexdigest();

  std::cout << hash << std::endl;

  assert(hash == "f7bc83f430538424b13298e6aa6fb143ef4d59a14946175997479dbc2d1a3cd8");

  return 0;
}