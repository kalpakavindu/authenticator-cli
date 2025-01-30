#pragma once

#include <string>
#include <vector>

namespace core {
  struct Account {
    std::string alias;
    std::string name;
    std::string key;
  };

  class Storage {
   private:
    const std::string _filename;
    std::vector<Account> _accounts;

   private:
    void _load();
    void _save();
    int _get_index(const std::string alias) const;

   public:
    Storage(const std::string filename);
    void add(const std::string& name, const std::string& key, const std::string& alias);
    void updateOne(const std::string id, const std::string* name, const std::string* key, const std::string* alias);
    void deleteOne(const std::string alias);
    const Account* findOne(const std::string alias) const;
    std::vector<Account> listAll();
  };
}  // namespace core