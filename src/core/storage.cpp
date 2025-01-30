#include "storage.h"

#include <array>
#include <fstream>
#include <sstream>

#include "utils.h"

namespace core {
  bool Storage::_load() {
    std::ifstream f(Storage::_filename);
    if (!f.is_open())
      return false;

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
    return true;
  }

  bool Storage::_save() {
    std::ofstream f(Storage::_filename);
    if (!f.is_open())
      return false;

    for (const Account& a : Storage::_accounts) {
      f << a.id << '|' << a.name << '|' << a.key << std::endl;
    }
    f.close();
    return true;
  }

  int Storage::_get_index(const std::string id) const {
    int i = 0;
    for (const Account& a : Storage::_accounts) {
      if (a.id == id)
        return i;
      ++i;
    }
    return -1;
  }

  Storage::Storage(const std::string filename) : _filename(filename) {
    Storage::_load();
  }

  void Storage::add(const std::string& name, const std::string& key) {
    std::string id = core::utils::generate_uuid();
    Account newAcc{id, name, key};
    Storage::_accounts.push_back(newAcc);
    Storage::_save();
  }

  bool Storage::updateById(const std::string id, const std::string* name, const std::string* key) {
    if (!name && !key)
      return false;

    for (Account& a : Storage::_accounts) {
      if (a.id == id) {
        if (name) {
          a.set_name(*name);
        }

        if (key) {
          a.set_key(*key);
        }

        Storage::_save();
        return true;
      }
    }
    return false;
  }

  bool Storage::deleteById(const std::string id) {
    int pos = Storage::_get_index(id);
    if (pos == -1)
      return false;

    Storage::_accounts.erase(Storage::_accounts.begin() + pos);
    Storage::_save();
    return true;
  }

  const Account* Storage::findById(const std::string id) const {
    for (const Account& a : Storage::_accounts) {
      if (a.id == id) {
        return &a;
      }
    }
    return nullptr;
  }

  std::vector<Account> Storage::listAll() const {
    return Storage::_accounts;
  }
}  // namespace core