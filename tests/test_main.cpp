#include "measurement.h"
#include <iostream>

extern void run_all_tests();

struct data_t
{
	int return_value;
	int arg_count;
	char **argv;
};

void run_tests(void *config_data)
{
	config_data; // unused
	run_all_tests();
}

int main(int argc, char *argv[])
{
	data_t data;
	data.return_value = 0;
	data.arg_count = argc;
	data.argv = argv;
	int64_t duration_in_nanoseconds = execute_function_and_measure_duration_in_nanoseconds(run_tests, &data);
	std::cout << "Test execution duration: " << duration_in_nanoseconds << " nanoseconds" << '\n';
	return data.return_value;
}
