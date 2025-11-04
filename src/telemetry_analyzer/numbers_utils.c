#include "numbers_utils.h" 

int char_to_decimal(char c){
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    else if (c >= 'a' && c <= 'z')
        return c - 'a' + 10;
    return -1;
}

int is_valid_num(char* num_str, int base){
    int i = 0, cnt_dot = 0, char_num;

    if (*num_str == '-' && char_to_decimal(*(num_str + 1)) != -1)
        i++;

    while (*(num_str + i) != '\0'){
        char_num = char_to_decimal(*(num_str + i));
        if (char_num == -1 || char_num >= base)
            return 0;
        i++;
        if (*(num_str + i) == '.' && *(num_str + i + 1) != '\0'){
            cnt_dot += 1;
            i++;
            if (cnt_dot > 1)
                return 0;
        }
    }
    return 1;
}

double num_cnvrt_to_dcml(char* num_str, int base){
    double num_decimal = 0, k = 1, multipler = 1.0 / base;
    int is_decimal = 1, i = 0;

    if (*(num_str) == '-'){
        k = -1;
        i++;
    }

    while (*(num_str + i) != '\0'){
        if (is_decimal)
            num_decimal = num_decimal * base + char_to_decimal(*(num_str + i++));
        else{
            num_decimal += (double) char_to_decimal(*(num_str + i++)) * multipler;
            multipler /= base;
        }
        if (*(num_str + i) == '.'){
            is_decimal = 0;
            i++;
        }
    }
    
    return k * num_decimal;
}

double* arr_create_dcml_nums(char** nums_str, int* bases, int cnt){
    double* nums_dcml = (double*) malloc(cnt * sizeof(double));
    if (nums_dcml == NULL) {
        puts("malloc error, array = NULL");
            return NULL;
        }

    for (int i = 0; i < cnt; i++){
        if (!is_valid_num(*(nums_str + i), *(bases + i))){
            printf("%s@%d Incorrect , result is replaced by zero, values of the median and mean will be inaccurate\n", *(nums_str + i), *(bases + i));
            *(nums_dcml + i) = 0;
        }
        else               
            *(nums_dcml + i) = num_cnvrt_to_dcml(*(nums_str + i), *(bases + i));
    }
    
    return nums_dcml;
}
