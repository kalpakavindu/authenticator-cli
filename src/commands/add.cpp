#include <iostream>

#include "cli/colors.h"
#include "cli/command.h"

void handler(std::vector<Argument>& args) {
  std::string alias;
  std::string name;
  std::string secret;

  for (Argument arg : args) {
    if (arg.key == "--alias")
      alias = arg.value;
    if (arg.key == "--name")
      name = arg.value;
    if (arg.key == "--secret")
      secret = arg.value;
  }

  std::cout << colors::blue << name << colors::reset << " ";
  std::cout << colors::green << alias << colors::reset << " ";
  std::cout << colors::yellow << secret << colors::reset << " ";
}

Command setup_add() {
  Command add("add", "Add new account.");

  add.set_arg("--alias", "-a", "Alias for the account.", true);
  add.set_arg("--name", "-n", "Name of the account.", true);
  add.set_arg("--secret", "-s", "Secret provided by the server.", true);

  add.set_handler(handler);

  return add;
}