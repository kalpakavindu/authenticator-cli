#pragma once

#include <string>
#include <vector>

struct Account {
  std::string id;
  std::string name;
  std::string key;

  void set_name(const std::string val) {
    Account::name = val;
  }

  void set_key(const std::string val) {
    Account::key = val;
  }
};

class Storage {
 private:
  const std::string _filename = "data.txt";
  std::vector<Account> _accounts;

 private:
  bool _load();
  bool _save();
  int _get_index(const std::string id) const;

 public:
  Storage();
  void add(const std::string& name, const std::string& key);
  bool updateById(const std::string id, const std::string* name, const std::string* key);
  bool deleteById(const std::string id);
  const Account* findById(const std::string id) const;
  std::vector<Account> listAll() const;
};