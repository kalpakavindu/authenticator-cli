#include <iostream>

#include "cli/colors.h"
#include "core/storage.h"
#include "index.h"

void handler_add(std::vector<Argument>& args) {
  Storage* store = Storage::getInstance();

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

  store->add(name, secret, alias);
  std::cout << "New account '" << colors::blue << alias << colors::reset << "' created." << std::endl;
}

Command setup_add() {
  Command add("add", "Add new account.");

  add.set_arg("--alias", "-a", "Alias for the account.", true);
  add.set_arg("--name", "-n", "Name of the account.", true);
  add.set_arg("--secret", "-s", "Secret provided by the server.", true);

  add.set_handler(handler_add);

  return add;
}