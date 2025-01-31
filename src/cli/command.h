#pragma once

#include <string>
#include <vector>

struct Argument {
  const std::string key;
  const std::string short_key;
  std::string value;
  const std::string desc;
  const bool required;
  const bool only_key;
};

typedef void (*Callable)(std::vector<Argument*>);

struct Command {
  const std::string name;
  const std::string desc;
  std::vector<Argument*> arguments;
  Callable handler;

  void exec();
  void get_help();
};