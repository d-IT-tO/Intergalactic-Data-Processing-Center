#include "coordinates_decoder.h"

//VALIDATION
int validate_base(int base) {
    return base >= 2 && base <= 16;
}

int validate_number(const char* number, int base) {
    int dot_count = 0;
    int len = strlen(number);

    if (len == 0 || len >= 13) return 0;

    for (int i = 0; i < len; i++) {
        char c = toupper(number[i]);

        if (c == '.') {
            dot_count++;
            if (dot_count > 1) return 0;
            continue;
        }

        int val = char_to_value(c);
        if (val < 0 || val >= base) return 0;
    }
    return 1;
}

//TRANSFORMATIONS

void split_number_string(const char* number, char* integer_part, char* fractional_part) {
    const char* dot = strchr(number, '.');
    if (dot) {
        strncpy(integer_part, number, dot - number);
        integer_part[dot - number] = '\0';
        strcpy(fractional_part, dot + 1);
    } else {
        strcpy(integer_part, number);
        fractional_part[0] = '\0';
    }
}

//GORNER'S ALGORITHM FOR THE INTEGER PART
double string_to_decimal(const char* number, int base) {
    char int_part[32] = {0}, frac_part[32] = {0};
    split_number_string(number, int_part, frac_part);

    //integer
    double result = 0;
    for (int i = 0; i < strlen(int_part); i++) {
        result = result * base + char_to_value(toupper(int_part[i]));
    }

    //fractional
    double frac = 0;
    double power = 1.0 / base;
    for (int i = 0; i < strlen(frac_part); i++) {
        int val = char_to_value(toupper(frac_part[i]));
        frac += val * power;
        power /= base;
    }

    return result + frac;
}

char* decimal_to_string(double number, int base, int precision) {
    if (precision > 12) precision = 12;

    long long int_part = (long long)number;
    double frac_part = number - int_part;

    //integer
    char buffer[128];
    int idx = 0;

    if (int_part == 0) {
        buffer[idx++] = '0';
    } else {
        char temp[64];
        int t = 0;
        while (int_part > 0) {
            temp[t++] = value_to_char(int_part % base);
            int_part /= base;
        }
        for (int i = t - 1; i >= 0; i--)
            buffer[idx++] = temp[i];
    }

    buffer[idx++] = '.';

    //farctional
    for (int i = 0; i < precision; i++) {
        frac_part *= base;
        int digit = (int)frac_part;
        buffer[idx++] = value_to_char(digit);
        frac_part -= digit;
        if (frac_part < 1e-12) break;
    }

    buffer[idx] = '\0';
    char* result = (char*)malloc(strlen(buffer) + 1);
    if (!result) return NULL;
    strcpy(result, buffer);
    return result;
}

//AUXILIARY FUNCTIONS

int char_to_value(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return -1;
}

char value_to_char(int value) {
    if (value >= 0 && value <= 9) return '0' + value;
    return 'A' + (value - 10);
}

//MAIN FUNCTION

char* student1_process(int src_base, int dest_base, const char* number) {
    if (validate_base(src_base) == 0 || validate_base(dest_base) == 0) {
        fprintf(stderr, "Недопустимое основание системы счисления.\n");
        return NULL;
    }

    if (validate_number(number, src_base) == 0) {
        fprintf(stderr, "Недопустимое число для данной системы.\n");
        return NULL;
    }

    double decimal_value = string_to_decimal(number, src_base);
    char* result = decimal_to_string(decimal_value, dest_base, 12);

    if (result == 0) {
        fprintf(stderr, "Ошибка выделения памяти.\n");
        return NULL;
    }

    return result;
}

