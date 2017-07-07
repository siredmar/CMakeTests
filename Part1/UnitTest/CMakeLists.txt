cmake_minimum_required (VERSION 2.6)
project (UnitTest)
add_executable(UnitTest UnitTest.cxx)
target_link_libraries (UnitTest  CppUTest CppUTestExt)
