#include <iostream>

#include "core/storage.h"
#include "index.h"

void handler_delete(std::vector<Argument>& args) {
  Storage* store = Storage::getInstance();
  std::string alias;
  std::string o = "";

  for (Argument& a : args) {
    if (a.key == "--alias")
      alias = a.value;
    if (a.key == "--yes" && a.specified)
      o = "yes";
  }

  if (o == "") {
    std::cout << "Are you sure, you want to delete the account '" << alias << "' ?\n";
    std::cout << "[yes/y, no/n]: ";
    std::cin >> o;
  }

  if (o == "yes" || o == "y") {
    store->deleteOne(alias);
    std::cout << "Account deleted." << std::endl;
  } else {
    std::cout << "Task cancelled." << std::endl;
  }
}

Command setup_delete() {
  Command del("delete", "Delete an account.");

  del.set_arg("--alias", "-a", "Alias of the account.", true);
  del.set_arg("--yes", "-y", "Skip confirmation.", false);

  del.set_handler(handler_delete);

  return del;
}