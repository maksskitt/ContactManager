#include "PhoneRec.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::cout << "Phone book interactive application." << std::endl
            << "Usage: answer questions, capital letter is the default choice. "
               "To exit, enter empty name or zero phone number."
            << std::endl
            << "Author: Maxim Kitov maksskitt@gmail.com. Homepage: https://github.com/maksskitt/ContactManager." << std::endl;
  std::vector<PhoneRec> pb;

  std::string name, phone;

  while (true) {
    std::cout << "Enter name: ";
    std::getline(std::cin, name);

    std::cout << "Enter phone number: ";
    std::getline(std::cin, phone);
    PhoneRec pr = PhoneRec(name, phone);

    if (pr.getPhone() == 0)
      break;
    if (pr.getPhone() == 1) {
        std::cout << "Parsing phone number failed. The record will be skipped." << std::endl;
        continue;
    }

    pb.push_back(pr);
  }

  printPhoneBook(pb);

  std::cout << "Export phone book? (Y/n) ";
  std::string doExport;
  std::getline(std::cin, doExport);

  if (!(doExport == "n" || doExport == "N" || doExport == "No" ||
        doExport == "no")) {
    std::string filename = "contacts.vcf";
    std::filesystem::path path =
        std::filesystem::current_path().append(filename);

    if (std::filesystem::exists(path)) {
      std::string doOverwrite;
      std::cout << "Overwrite file? (y/N): ";
      std::getline(std::cin, doOverwrite);

      if (doOverwrite == "y" || doOverwrite == "Y" || doOverwrite == "Yes" ||
          doOverwrite == "yes")
        std::filesystem::remove(path);
      else {
        std::cout << "Enter filename: ";
        std::getline(std::cin, filename);

        if (!filename.ends_with(".vcf"))
          filename += ".vcf";

        path.replace_filename(filename);
      }
    }

    for (auto &pr : pb)
      pr.exportVCF(filename);

    std::cout << "File saved at: " << path.string() << std::endl;
  }

  return 0;
}