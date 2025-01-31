#include "command.h"

#include <iostream>

Command::Command(const std::string name, const std::string desc) : _name(name), _desc(desc) {}

void Command::get_help() {
  std::cout << "Command: " << Command::_name << "\n";
  std::cout << Command::_desc << "\n\nUsage:\n";
  std::cout << "    auth-cli [global-options] command [command-options]\n\nCommand options:\n";

  for (Argument& arg : Command::_arguments) {
    std::string a = arg.key + "," + arg.short_key;
    while (a.size() < 20) {
      a += " ";
    }
    if (arg.required) {
      a += "*    ";
    } else {
      a += "     ";
    }
    std::cout << "    " << a << arg.desc << "\n";
  }

  std::cout << "\nGlobal options:\n";
  std::cout << "    --help,-h           Get help." << std::endl;
}

const std::string Command::get_name() const {
  return Command::_name;
}

const std::string Command::get_desc() const {
  return Command::_desc;
}

std::vector<Argument>* Command::get_args() {
  return &(Command::_arguments);
}

void Command::set_arg(const std::string key,
                      const std::string skey,
                      const std::string desc,
                      const bool required) {
  Argument arg({key, skey, desc, required});
  Command::_arguments.push_back(arg);
}

void Command::set_handler(Callable function) {
  Command::_handler = function;
}

void Command::exec() {
  Command::_handler(Command::_arguments);
}