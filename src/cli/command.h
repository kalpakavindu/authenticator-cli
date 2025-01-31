#pragma once

#include <string>
#include <vector>

struct Argument {
  const std::string key;
  const std::string short_key;
  const std::string desc;
  const bool required;
  std::string value;
};

typedef void (*Callable)(std::vector<Argument>&);

class Command {
 private:
  const std::string _name;
  const std::string _desc;
  std::vector<Argument> _arguments;
  Callable _handler;

 public:
  Command(const std::string name, const std::string desc);
  const std::string get_name() const;
  const std::string get_desc() const;
  std::vector<Argument>* get_args();
  void get_help();
  void set_arg(const std::string key, const std::string skey, const std::string desc, const bool required);
  void set_handler(Callable function);
  void exec();
};