#ifndef COORDINATES_DECODER_H
#define COORDINATES_DECODER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//validation
int validate_base(int base);
int validate_number(const char* number, int base);

//transformations
double string_to_decimal(const char* number, int base);
char* decimal_to_string(double number, int base, int precision);

//auxiliary functions
int char_to_value(char c);
char value_to_char(int value);
void split_number_string(const char* number, char* integer_part, char* fractional_part);

//main function
char* student1_process(int src_base, int dest_base, const char* number);

#endif
