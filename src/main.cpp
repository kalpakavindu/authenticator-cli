#include <iostream>
#include <stdexcept>
#include <utility>

#include "cli/colors.h"
#include "cli/commander.h"

// Commands
#include "commands/add.cpp"

int main(int argc, const char* argv[]) {
  try {
    Commander commander(argc, argv);

    // Register commands
    commander.Register(setup_add);

    commander.run();
  } catch (std::invalid_argument e) {
    std::cout << colors::red << e.what() << colors::reset << std::endl;
  }
  return 0;
}