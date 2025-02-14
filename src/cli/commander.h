#pragma once

#include <utility>

#include "command.h"

typedef Command (*CommandSetup)();

class Commander {
 private:
  std::string _cur_command;
  std::vector<std::pair<std::string, std::string>> _cur_args;
  std::vector<Command> _commands;
  void _get_help(std::string* command_name);

 public:
  Commander(int argc, const char* argv[]);
  void Register(CommandSetup setup_func);
  void run();
};