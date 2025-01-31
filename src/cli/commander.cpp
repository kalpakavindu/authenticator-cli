#include "commander.h"

#include <iostream>
#include <stdexcept>

#include "utils.h"

Commander::Commander(int argc, const char* argv[]) {
  if (argc == 1) {
    Commander::_cur_command = "help";
  } else if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
    Commander::_cur_command = "help";
    if (argc > 2) {
      Commander::_cur_args = {{argv[2], ""}};
    }
  } else {
    std::string cmd = argv[1];
    if (cmd.rfind("-", 0) != 0) {
      Commander::_cur_command = cmd;

      if (argc > 2) {
        for (int i = 2; i < argc; ++i) {
          std::string arg = argv[i];
          if (arg.find("=") != std::string::npos) {
            std::vector<std::string> splitted = utils::split(arg, "=");
            Commander::_cur_args.push_back({splitted[0], splitted[1]});
          } else {
            Commander::_cur_args.push_back({arg, ""});
          }
        }
      }
    } else {
      throw std::invalid_argument("Command not specified.");
    }
  }
}

void Commander::_get_help(std::string* command) {
  if (command) {
    // Check command exists
    Command* cmd = nullptr;
    for (Command* c : Commander::_commands) {
      if (c->name == *command) {
        cmd = c;
      }
    }
    if (!cmd)
      throw std::invalid_argument("Command '" + *command + "' not found.");
    cmd->get_help();
  } else {
    std::cout << "Usage:\n";
    std::cout << "    auth-cli [global-options] command [command-options] [arguments...]\n\n";
    std::cout << "Commands:\n";

    for (Command* cmd : Commander::_commands) {
      std::string c = cmd->name;
      while (c.size() == 20) {
        c += " ";
      }
      std::cout << "    " << c << cmd->desc << "\n";
    }

    std::cout << "\nGlobal options:\n";
    std::cout << "    --help,-h           Get help.\n";
    std::cout << "    --version,-v        Print version number." << std::endl;
  }
}

void Commander::run() {
  if (Commander::_cur_command == "help") {
    // Show help message
    if (Commander::_cur_args.size() > 0) {
      Commander::_get_help(&(Commander::_cur_args[0].first));
    } else {
      Commander::_get_help(nullptr);
    }
  } else {
    // Process command
    for (Command* cmd : Commander::_commands) {
      if (cmd->name == Commander::_cur_command) {
        for (Argument* arg : cmd->arguments) {
          // Check required auguments
          if (arg->required) {
            bool found = false;
            for (std::pair<std::string, std::string> key : Commander::_cur_args) {
              if (arg->key == key.first || arg->short_key == key.first) {
                found = true;
              }
            }

            if (!found) {
              throw std::invalid_argument("Argument '" + arg->key + "' is required.");
            }
          }

          // Set argument values
          for (std::pair<std::string, std::string> key : Commander::_cur_args) {
            if (arg->key == key.first || arg->short_key == key.first) {
              arg->value = key.second;
            }
          }
        }
        cmd->exec();
        return;
      }
    }
    throw std::invalid_argument("Command '" + Commander::_cur_command + "' not found.");
  }
}