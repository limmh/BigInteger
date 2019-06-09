#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "measurement.h"
#include <iostream>

struct data_t
{
	int return_value;
	int arg_count;
	char **argv;
};

void run_tests(void *config_data)
{
	data_t *data = static_cast<data_t*>(config_data);
	data->return_value = Catch::Session().run(data->arg_count, data->argv);
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
