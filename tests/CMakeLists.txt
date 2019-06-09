add_executable(BigIntegerTests BigInteger_tests.cpp test_main.cpp measurement.cpp measurement.h catch.hpp)
target_link_libraries(BigIntegerTests BigInteger)
