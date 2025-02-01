#include <iostream>
#include <stdexcept>
#include <utility>

#include "cli/colors.h"
#include "cli/commander.h"
#include "commands/index.h"

int main(int argc, const char* argv[]) {
  try {
    Commander commander(argc, argv);

    // Register commands
    commander.Register(setup_add);
    commander.Register(setup_list);
    commander.Register(setup_rename);
    commander.Register(setup_delete);

    commander.run();
  } catch (std::invalid_argument e) {
    std::cout << e.what() << std::endl;
  } catch (std::runtime_error e) {
    std::cout << colors::red << e.what() << colors::reset << std::endl;
    return 1;
  }
  return 0;
}