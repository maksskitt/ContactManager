#include "Phone.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("Valid plain numbers", "[phone][basic]") {
  auto phone1 = parsePhone("+79999999999");
  REQUIRE(phone1.first == 79999999999);
  REQUIRE(phone1.second == true);

  auto phone2 = parsePhone("79999999999");
  REQUIRE(phone2.first == 79999999999);
  REQUIRE(phone2.second == false);
}

TEST_CASE("Numbers with formatting characters", "[phone][formatting]") {
  auto phone1 = parsePhone("7+ (987) + 765-96-23");
  REQUIRE(phone1.first == 79877659623);
  REQUIRE(phone1.second == false);

  auto phone2 = parsePhone("+7+ (987) + 765-96-23");
  REQUIRE(phone2.first == 79877659623);
  REQUIRE(phone2.second == true);

  auto phone3 = parsePhone("(999) 888-77-66");
  REQUIRE(phone3.first == 9998887766);
  REQUIRE(phone3.second == false);

  auto phone4 = parsePhone("+1 (555) 123-4567");
  REQUIRE(phone4.first == 15551234567);
  REQUIRE(phone4.second == true);
}

TEST_CASE("Numbers with spaces or mixed delimiters", "[phone][spaces]") {
  auto phone1 = parsePhone("+7 999 123 45 67");
  REQUIRE(phone1.first == 79991234567);
  REQUIRE(phone1.second == true);

  auto phone2 = parsePhone("7 999 123 45 67");
  REQUIRE(phone2.first == 79991234567);
  REQUIRE(phone2.second == false);

  auto phone3 = parsePhone("7(999)1 2-+3-+4567");
  REQUIRE(phone3.first == 79991234567);
  REQUIRE(phone3.second == false);
}

TEST_CASE("Invalid or malformed numbers", "[phone][invalid]") {
  auto phone1 = parsePhone("abc");
  REQUIRE(phone1.first == 1);
  REQUIRE(phone1.second == false);

  auto phone2 = parsePhone("+7abc999");
  REQUIRE(phone2.first == 7999);
  REQUIRE(phone2.second == true);

  auto phone3 = parsePhone("++79991234567");
  REQUIRE(phone3.first == 79991234567);
  REQUIRE(phone3.second == true);

  auto phone4 = parsePhone("+-7(999)123-45-67");
  REQUIRE(phone4.first == 79991234567);
  REQUIRE(phone4.second == true);

  auto phone5 = parsePhone(" ");
  REQUIRE(phone5.first == 1);
  REQUIRE(phone5.second == false);
}

TEST_CASE("Boundary and special cases", "[phone][boundary]") {
  auto phone1 = parsePhone("+0");
  REQUIRE(phone1.first == 0);
  REQUIRE(phone1.second == true);

  auto phone2 = parsePhone("00000000000");
  REQUIRE(phone2.first == 0);
  REQUIRE(phone2.second == false);

  auto phone3 = parsePhone("+999999999999999");
  REQUIRE(phone3.first == 999999999999999);
  REQUIRE(phone3.second == true);
}

TEST_CASE("clearPhone basic formatting", "[clearPhone]") {
  REQUIRE(clearPhone("+420123456789") == "+420123456789");
  REQUIRE(clearPhone("420123456789") == "420123456789");
  REQUIRE(clearPhone("00420123456789") == "00420123456789");
}

TEST_CASE("clearPhone ignores non-digit symbols", "[clearPhone]") {
  REQUIRE(clearPhone("+420 123 456 789") == "+420123456789");
  REQUIRE(clearPhone("(420)-123-456-789") == "420123456789");
  REQUIRE(clearPhone("+420-123-456x789") == "+420123456789");
}

TEST_CASE("clearPhone handles multiple plus signs correctly", "[clearPhone]") {
  REQUIRE(clearPhone("++420123456789") == "+420123456789");
  REQUIRE(clearPhone("+420+123456789") == "+420123456789");
  REQUIRE(clearPhone("420+123456789") == "420123456789");
}

TEST_CASE("clearPhone handles misplaced plus and junk chars", "[clearPhone]") {
  REQUIRE(clearPhone("text+420123456789") == "+420123456789");
  REQUIRE(clearPhone("  +420abc123xyz456") == "+420123456");
  REQUIRE(clearPhone("++--+++999") == "+999");
  REQUIRE(clearPhone("++++") == "+");
}

TEST_CASE("clearPhone handles empty and minimal input", "[clearPhone]") {
  REQUIRE(clearPhone("") == "");
  REQUIRE(clearPhone("+") == "+");
  REQUIRE(clearPhone("123") == "123");
  REQUIRE(clearPhone("+1") == "+1");
}

TEST_CASE("clearPhone handles no valid characters", "[clearPhone]") {
  REQUIRE(clearPhone("abcxyz") == "");
  REQUIRE(clearPhone("+++---***") == "+");
}