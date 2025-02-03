#include <iostream>

#include "cli/colors.h"
#include "core/storage.h"
#include "index.h"

void handler_add(std::vector<Argument>& args) {
  Storage* store = Storage::getInstance();

  std::string alias = "";
  std::string name = "";
  std::string secret = "";

  for (Argument arg : args) {
    if (arg.key == "--alias")
      alias = arg.value;
    if (arg.key == "--name")
      name = arg.value;
  }

  while (name == "") {
    std::cout << "Enter the name: ";
    std::cin >> name;
  }

  while (alias == "") {
    std::cout << "Enter alias for this account: ";
    std::cin >> alias;
  }

  while (secret == "") {
    std::cout << "Enter the secret provided by the server: ";
    std::cin >> secret;
  }

  store->add(name, secret, alias);
  std::cout << "New account " << colors::blue << alias << colors::reset << " created." << std::endl;
}

Command setup_add() {
  Command add("add", "Add new account.");

  add.set_arg("--alias", "-a", "Alias for the account.", false);
  add.set_arg("--name", "-n", "Name of the account.", false);

  add.set_handler(handler_add);

  return add;
}