#include "PhoneRec.hpp"
#include <fstream>
#include <iostream>

void PhoneRec::exportVCF(const std::filesystem::path &path) const {
  std::ofstream vcf;
  vcf.open(path, std::ios_base::app);
  vcf << "BEGIN:VCARD\nVERSION:2.1\nFN:" << this->getName()
      << "\nTEL;CELL:" << this->sprintPhone() << "\nEND:VCARD\n";
  vcf.close();
}

void printPhoneBook(std::vector<PhoneRec> &pb) {
  size_t phoneLength = 0;
  size_t nameLength = 0;

  for (auto &pr : pb) {
    phoneLength = std::max(pr.sprintPhone().length(), phoneLength);
    nameLength = std::max(pr.getName().length(), nameLength);
  }

  phoneLength += 2;
  nameLength += 2;

  std::cout << std::left << std::setw(nameLength) << "Name"
            << std::setw(phoneLength) << "Phone" << std::endl;
  for (auto &pr : pb)
    std::cout << std::left << std::setw(nameLength) << pr.getName()
              << std::setw(phoneLength) << pr.sprintPhone() << std::endl;
}