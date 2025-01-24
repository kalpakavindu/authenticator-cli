#include <iostream>

#include "sha1.hpp"

int main() {
  std::string msg = "The quick brown fox jumps over the lazy dog";

  SHA1 sha1;
  sha1.update(msg);
  std::string hash = sha1.final();

  std::cout << hash << " " << (hash == "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12") << std::endl;

  return 0;
}