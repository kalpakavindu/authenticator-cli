#include "cli/colors.h"
#include "core/storage.h"
#include "index.h"

void handler_list(std::vector<Argument>& args) {
  Storage* store = Storage::getInstance();

  std::cout << colors::green << "\nAlias                " << "Name\n";
  std::cout << colors::green << "-----                " << "----" << colors::reset << "\n";

  for (Account& acc : store->listAll()) {
    std::string n = acc.alias;
    while (n.size() < 20) {
      n += " ";
    }
    std::cout << n << " " << acc.name << "\n";
  }
  std::cout << std::endl;
}

Command setup_list() {
  Command list("list", "List available accounts.");
  list.set_handler(handler_list);
  return list;
}