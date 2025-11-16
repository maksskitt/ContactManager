cmake_minimum_required(VERSION 3.31.6)

project("Contact book" LANGUAGES CXX VERSION 1)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory("Catch2")
add_executable(tests test_phone.cpp Phone.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)

add_executable(main main.cpp PhoneRec.cpp Phone.cpp)