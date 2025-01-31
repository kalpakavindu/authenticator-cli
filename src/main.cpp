#include <iostream>
#include <stdexcept>
#include <utility>

#include "cli/colors.h"
#include "cli/commander.h"

int main(int argc, const char* argv[]) {
  try {
    Commander commander(argc, argv);

    commander.run();
  } catch (std::invalid_argument e) {
    std::cout << colors::red << e.what() << colors::reset << std::endl;
  }
  return 0;
}