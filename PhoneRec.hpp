#include <filesystem>
#include <string>
#include <vector>

#include "Phone.hpp"

class PhoneRec : public Phone {
public:
  PhoneRec(const std::string &name, const std::string &phone)
      : Phone(phone), name(name) {}
  PhoneRec(const std::string &name, const unsigned long long phone,
           const bool hasPlus)
      : Phone(phone, hasPlus), name(name) {};

  void setName(const std::string &name) { this->name = name; }
  const std::string &getName() const { return this->name; }
  void exportVCF(const std::filesystem::path &path) const;

private:
  std::string name;
};

void printPhoneBook(std::vector<PhoneRec> &pb);