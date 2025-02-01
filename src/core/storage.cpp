#include "storage.h"

#include <array>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "utils.h"

void Storage::_load() {
  std::ifstream f(Storage::_filename);
  if (!f.is_open())
    throw std::runtime_error("Failed to open database file.");

  Storage::_accounts.clear();

  std::string line;
  while (std::getline(f, line)) {
    std::istringstream iss(line);
    std::array<std::string, 3> data;

    int i = 0;
    std::string token;
    while (std::getline(iss, token, '|')) {
      data[i++] = token;
    }

    Storage::_accounts.push_back({data[0], data[1], data[2]});
  }
  f.close();
}

void Storage::_save() {
  std::ofstream f(Storage::_filename);
  if (!f.is_open())
    throw std::runtime_error("Failed to open database file.");

  for (const Account& a : Storage::_accounts) {
    f << a.alias << '|' << a.name << '|' << a.key << std::endl;
  }
  f.close();
}

int Storage::_get_index(const std::string alias) const {
  int i = 0;
  for (const Account& a : Storage::_accounts) {
    if (a.alias == alias)
      return i;
    ++i;
  }
  return -1;
}

std::vector<Account> Storage::listAll() {
  Storage::_load();
  return Storage::_accounts;
}

void Storage::add(const std::string& name, const std::string& key, const std::string& alias) {
  Storage::_load();

  if (Storage::_get_index(alias) != -1)
    throw std::invalid_argument("Alias is already taken.");

  Account newAcc{alias, name, key};
  Storage::_accounts.push_back(newAcc);
  Storage::_save();
}

void Storage::updateOne(const std::string id, const std::string* name, const std::string* key, const std::string* alias) {
  Storage::_load();

  if (Storage::_get_index(id) == -1)
    throw std::invalid_argument("Alias not found.");

  if (!name && !key && !alias)
    return;

  for (Account& a : Storage::_accounts) {
    if (a.alias == id) {
      if (name)
        a.name = *name;

      if (key)
        a.key = *key;

      if (alias) {
        if (Storage::_get_index(*alias) != -1)
          throw std::invalid_argument("New alias is already exists.");
        a.alias = *alias;
      }

      Storage::_save();
    }
  }
}

void Storage::deleteOne(const std::string alias) {
  Storage::_load();

  int pos = Storage::_get_index(alias);
  if (pos == -1)
    throw std::invalid_argument("Alias not found.");

  Storage::_accounts.erase(Storage::_accounts.begin() + pos);
  Storage::_save();
}

const Account* Storage::findOne(const std::string alias) {
  Storage::_load();

  for (const Account& a : Storage::_accounts) {
    if (a.alias == alias) {
      return &a;
    }
  }
  return nullptr;
}

Storage* Storage::_storagePtr = new Storage();