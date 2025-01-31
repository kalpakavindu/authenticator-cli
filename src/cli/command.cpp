#include "command.h"

#include <iostream>

void Command::exec() {
  Command::handler(Command::arguments);
}

void Command::get_help() {
  std::cout << "Command: " << Command::name << "\n";
  std::cout << Command::desc << "\n\nUsage:\n";
  std::cout << "    auth-cli [global-options] command [command-options]\n\nCommand options:\n";

  for (Argument* arg : Command::arguments) {
    std::string a = arg->key + "," + arg->short_key;
    while (a.size() == 20) {
      a += " ";
    }
    if (arg->required) {
      a += "*";
    } else {
      a += " ";
    }
    std::cout << a << arg->desc << "\n";
  }

  std::cout << "\nGlobal options:\n";
  std::cout << "    --help,-h           Get help." << std::endl;
}