#ifndef PROJECT_PARSER_PARSE_INPUT_H_
#define PROJECT_PARSER_PARSE_INPUT_H_

#include <stddef.h>

int read_size_from_input(size_t *size);
int read_array_from_input(int **arr, size_t size);

#endif  // PROJECT_PARSER_PARSE_INPUT_H_