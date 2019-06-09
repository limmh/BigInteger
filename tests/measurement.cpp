#include "measurement.h"
#include <chrono>

using namespace std::chrono;

int64_t execute_function_and_measure_duration_in_nanoseconds(void (*function_pointer)(void*), void *data)
{
	time_point<high_resolution_clock> start_time = high_resolution_clock::now();
	(*function_pointer)(data);
	time_point<high_resolution_clock> end_time = high_resolution_clock::now();
	nanoseconds fn_duration = duration_cast<nanoseconds>(end_time - start_time);
	return fn_duration.count();
}
