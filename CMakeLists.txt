cmake_minimum_required(VERSION 3.5)

project(BigInteger)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Libraries
add_library(
	BigInteger STATIC
	"${DIR}/src/BigInteger.cpp"
	"${DIR}/src/BigIntegerHelper.cpp"
	"${DIR}/src/BigIntegerHelper.hpp"
)
target_include_directories(BigInteger PRIVATE "${DIR}/include")
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang|IntelLLVM|XLClang|IBMClang")
	target_compile_options(BigInteger PRIVATE -Wall -Wextra -Wpedantic -std=c++11)
endif()

set(EXTERNAL "${DIR}/external/C_programming")
set(TERMINAL_TEXT_COLOR "terminal_text_color")
set(TERMINAL_TEXT_COLOR_FOLDER "${EXTERNAL}/${TERMINAL_TEXT_COLOR}")
set(UNIT_TESTING "unit_testing")
set(UNIT_TESTING_FOLDER "${EXTERNAL}/${UNIT_TESTING}")

if (EXISTS "${TERMINAL_TEXT_COLOR_FOLDER}/CMakeLists.txt" AND
	EXISTS "${UNIT_TESTING_FOLDER}/CMakeLists.txt")
	# Add only the necessary library files
	add_subdirectory("${TERMINAL_TEXT_COLOR_FOLDER}")
	add_subdirectory("${UNIT_TESTING_FOLDER}")

	# Tests
	set(TEST_FOLDER "${DIR}/tests")
	add_executable(
		BigIntegerTests
		"${TEST_FOLDER}/BigInteger_tests.cpp"
		"${TEST_FOLDER}/test_main.cpp"
		"${TEST_FOLDER}/measurement.cpp"
		"${TEST_FOLDER}/measurement.h"
	)
	target_include_directories(
		BigIntegerTests PRIVATE
		"${DIR}/include"
		"${EXTERNAL}/includes"
		"${EXTERNAL}/unit_testing"
	)
	if (CCMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang|IntelLLVM|XLClang|IBMClang")
		target_compile_options(BigIntegerTests PRIVATE -Wall -Wextra -Wpedantic -std=c++11)
	endif()
	target_link_libraries(BigIntegerTests BigInteger terminal_text_color unit_testing)
else()
	if (NOT EXISTS "${TERMINAL_TEXT_COLOR_FOLDER}/CMakeLists.txt")
		message("${TERMINAL_TEXT_COLOR_FOLDER}/CMakeLists.txt is not found.")
	endif()
	if (NOT EXISTS "${UNIT_TESTING_FOLDER}/CMakeLists.txt")
		message("${UNIT_TESTING_FOLDER}/CMakeLists.txt")
	endif()

	message("Please run the following Git commands to retrieve external dependencies.")
	message("git submodule init")
	message("git submodule update")
endif()

# Example
set(EXAMPLE_FOLDER "${DIR}/example")
add_executable(Calculator "${EXAMPLE_FOLDER}/Calculator.cpp")
target_include_directories(Calculator PRIVATE "${DIR}/include")
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(Calculator PRIVATE -Wall -Wextra -Wpedantic -std=c++11)
endif()
target_link_libraries(Calculator BigInteger)
