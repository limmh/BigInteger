#ifndef TEST_MEASUREMENT_H
#define TEST_MEASUREMENT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Calls (*function_pointer)(data) and measure its execution time in nanoseconds
int64_t execute_function_and_measure_duration_in_nanoseconds(void (*function_pointer)(void*), void *data);

#ifdef __cplusplus
}
#endif

#endif
