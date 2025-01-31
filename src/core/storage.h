#pragma once

#include <mutex>
#include <string>
#include <vector>

struct Account {
  std::string alias;
  std::string name;
  std::string key;
};

class Storage {
 private:
  const std::string _filename = "data.txt";
  std::vector<Account> _accounts;
  static Storage* _storagePtr;
  static std::mutex _mtx;

 private:
  void _load();
  void _save();
  int _get_index(const std::string alias) const;
  Storage() {};

 public:
  Storage(const Storage& obj) = delete;
  void add(const std::string& name, const std::string& key, const std::string& alias);
  void updateOne(const std::string id, const std::string* name, const std::string* key, const std::string* alias);
  void deleteOne(const std::string alias);
  const Account* findOne(const std::string alias);
  std::vector<Account> listAll();

  static Storage* Instance() {
    if (Storage::_storagePtr == nullptr) {
      // For thread safety
      std::lock_guard<std::mutex> lock(Storage::_mtx);
      if (Storage::_storagePtr == nullptr) {
        Storage::_storagePtr = new Storage();
      }
    }
    return Storage::_storagePtr;
  }
};