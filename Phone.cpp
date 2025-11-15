#include <string>

std::string clearPhone(const std::string &phone) {
  std::string clean;
  bool hadPlus = false, hadDigit = false;

  for (unsigned char c : phone) {
    if (std::isdigit(c)) {
      clean += c;
      hadDigit = true;
    } else if (c == '+' && !hadPlus && !hadDigit) {
      clean += '+';
      hadPlus = true;
    }
  }

  return clean;
}

std::pair<unsigned long long, bool> parsePhone(std::string phone) {
  phone = clearPhone(phone);

  bool hasPlus = false;

  if (phone[0] == '+') {
    hasPlus = true;
    phone = phone.substr(1, phone.length());
  }

  unsigned long long number = 1;
  if (!phone.empty()) {
    char *end = nullptr;
    number = std::strtoull(phone.c_str(), &end, 10);

    if (*end != '\0')
      number = 1;
  }

  return std::make_pair(number, hasPlus);
}