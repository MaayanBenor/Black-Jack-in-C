#pragma once
#include <stdbool.h>
#include <stdint.h>

#define RED "\033[0;31m" //change output text color to red
#define GREEN "\033[0;32m" //change output text color to green
#define YELLOW "\033[0;33m" //change output text color tO yellow
#define RST "\033[0m" //reset text color
#define MY_ASSERT(condition, message) my_assert((condition),__FILE__, __func__, __LINE__, (message));

void my_assert(bool condition, const char *file, const char *func,
               const int line, const char *error_message);

void clear_buffer();

size_t get_user_input_size_t();