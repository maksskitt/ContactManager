#include <string>

std::pair<unsigned long long, bool> parsePhone(std::string phone);
std::string clearPhone(const std::string &phone);

class Phone {
public:
  Phone(unsigned long long phone, bool hasPlus) {
    this->phone = phone;
    this->hasPlus = hasPlus;
  }
  Phone(const std::string &phone) { this->setPhone(phone); }

  void setPhone(const unsigned long long phone) { this->phone = phone; }
  void setPhone(const std::string &phone) {
    std::pair<unsigned long long, bool> number = parsePhone(phone);
    this->setPhone(number.first);
    this->hasPlus = number.second;
  }
  unsigned long long getPhone() const { return this->phone; }
  virtual std::string sprintPhone() const {
    return this->hasPlus ? "+" + std::to_string(this->phone)
                         : std::to_string(this->phone);
  }

private:
  unsigned long long phone : 50;
  unsigned long long hasPlus : 1;
};