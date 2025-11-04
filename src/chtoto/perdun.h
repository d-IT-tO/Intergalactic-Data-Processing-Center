#ifndef PERDUN_H
#define PERDUN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Валидация
int validate_base(int base);
int validate_number(const char* number, int base);

//Преобразования
double string_to_decimal(const char* number, int base);
char* decimal_to_string(double number, int base, int precision);

//Вспомогательные функции
int char_to_value(char c);
char value_to_char(int value);
void split_number_string(const char* number, char* integer_part, char* fractional_part);

//Главная функция
char* student1_process(int src_base, int dest_base, const char* number);

#endif
