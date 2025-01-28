#pragma

#include <array>
#include <cstdint>
#include <string>
#include <vector>

class SHA256 {
 public:
  static const size_t DIGEST_SIZE = 32;
  static const size_t BLOCK_SIZE = 64;

 private:
  std::vector<unsigned char> _data;
  uint32_t _h[8];

 private:
  void _transform(uint32_t chunk[16]);
  void _calculate();
  void _init();

 public:
  SHA256() {};
  void update(const char* message, size_t length);
  std::array<uint8_t, SHA256::DIGEST_SIZE> digest();
  std::string hexdigest();
};