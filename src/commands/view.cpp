#include <iomanip>
#include <iostream>

#include "core/otp.h"
#include "core/storage.h"
#include "index.h"
#include "utils.h"

void handler_view(std::vector<Argument>& args) {
  Storage* store = Storage::getInstance();
  std::string alias;

  for (Argument& a : args) {
    if (a.key == "--alias")
      alias = a.value;
  }

  const Account* acc = store->findOne(alias);

  Totp totp(acc->key, 30);

  std::cout << acc->name << "\n";
  std::cout << std::setfill('0') << std::setw(6) << totp.now() << " (remaining time: ";
  std::cout << std::setfill('0') << std::setw(2) << totp.remaining() << "s)" << std::endl;
}

Command setup_view() {
  Command view("view", "View an account.");

  view.set_arg("--alias", "-a", "Alias of the account.", true);

  view.set_handler(handler_view);

  return view;
}