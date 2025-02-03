#include <iomanip>
#include <iostream>
#include <sstream>

#include "core/otp.h"
#include "core/storage.h"
#include "index.h"
#include "utils.h"

std::string format_code(int& code) {
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(3) << (int)(code / 1000) << "-";
  ss << std::setfill('0') << std::setw(3) << (int)(code % 1000);
  return ss.str();
}

void handler_view(std::vector<Argument>& args) {
  Storage* store = Storage::getInstance();
  std::string alias;
  bool follow = false;

  for (Argument& a : args) {
    if (a.key == "--alias")
      alias = a.value;
    if (a.key == "--follow") {
      if (a.specified)
        follow = true;
    }
  }

  const Account* acc = store->findOne(alias);

  std::cout << acc->name << "\n";

  if (follow) {
    while (true) {
      Totp totp(acc->key, 30);
      int cur_code = totp.now();

      std::cout << format_code(cur_code) << std::endl;

      utils::setTimeOut(1000 * totp.remaining());
    }
  } else {
    Totp totp(acc->key, 30);
    int cur_code = totp.now();
    std::cout << format_code(cur_code) << " (remaining time: ";
    std::cout << std::setfill('0') << std::setw(2) << totp.remaining() << "s)" << std::endl;
  }
}

Command setup_view() {
  Command view("view", "View an account.");

  view.set_arg("--alias", "-a", "Alias of the account.", true);
  view.set_arg("--follow", "-f", "Automatically show new codes.", false);

  view.set_handler(handler_view);

  return view;
}