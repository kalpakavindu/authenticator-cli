#include <iostream>

#include "cli/command.h"
#include "core/storage.h"
#include "index.h"

void handler_rename(std::vector<Argument>& args) {
  Storage* store = Storage::getInstance();

  std::string alias;
  std::string name;

  for (Argument& a : args) {
    if (a.key == "--alias")
      alias = a.value;
    if (a.key == "--name")
      name = a.value;
  }

  while (name == "") {
    std::cout << "Enter the new name: ";
    std::cin >> name;
  }

  store->updateOne(alias, &name, nullptr, nullptr);

  std::cout << "Account name updated." << std::endl;
}

Command setup_rename() {
  Command rename("rename", "Change account name.");

  rename.set_arg("--alias", "-a", "Alias of the account.", true);
  rename.set_arg("--name", "-n", "New name for the account.", false);

  rename.set_handler(handler_rename);

  return rename;
}