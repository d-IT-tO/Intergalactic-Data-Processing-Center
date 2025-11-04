#ifndef ARRAY_OPERATIONS_H
#define ARRAY_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>

int char_to_decimal(char c);
int is_valid_num(char* num_str, int base);
double num_cnvrt_to_dcml(char* num_str, int base);
double* arr_create_dcml_nums(char** nums_str, int* bases, int cnt);

#endif
