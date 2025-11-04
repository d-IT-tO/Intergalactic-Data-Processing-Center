#include <stdio.h>
#include <stdlib.h>

void arr_copy(double* arr_cp, double* arr, int cnt){
    for (int i = 0; i < cnt; i++)
        *(arr_cp + i) = *(arr + i);
}

void swap_nums(double* frst_num, double* scnd_num){
    double tmp = *frst_num;
    *frst_num = *scnd_num;
    *scnd_num = tmp;
}

void arr_bubble_sort(double* arr, int cnt){
    for (int i = 0; i < cnt; i++){
        for (int j = i + 1; j < cnt; j++){
            if (*(arr + i) > *(arr + j))
                swap_nums((arr + i), (arr + j));
        }
    }
}

double arr_mean(double* arr, int cnt){
    double sum = 0;
    for (int i = 0; i < cnt; i++)
        sum += *(arr + i);
    return sum / cnt;
}

double arr_median(double* arr, int cnt, int is_sort){
    double median;
    double* tmp_arr;

    if (!is_sort){
        tmp_arr = (double*) malloc(cnt * sizeof(double));
        if (tmp_arr == NULL) {
            puts("malloc error, mean = 0");
            return 0;
        }
        arr_copy(tmp_arr, arr, cnt);
        arr_bubble_sort(tmp_arr, cnt);
    }
    else tmp_arr = arr;

    if (cnt % 2 == 0)
        median = (*(tmp_arr + cnt / 2) + *(tmp_arr + cnt / 2 - 1)) / 2.0;
    else
        median = *(tmp_arr + cnt / 2);
    
    if (!is_sort)
        free(tmp_arr);
    
    return median;
}

void arr_find_min_max(double* arr, int cnt, int is_sort, double* min, double* max){
    *min = *arr;
    *max = *(arr + cnt - 1);
    
    if (!is_sort){
        for (int i = 1; i < cnt; i++){
            if (*(arr + i) > *max)
                *max = *(arr + i);
            if (*(arr + i) < *min)
                *min = *(arr + i);
        }
    }
}

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

void print_arr(const double* arr, int cnt){
    for (int i = 0; i < cnt; i++)
        printf("%g ", *(arr + i));
    printf("\n");
}

void arr_full_analyze(char** nums_str, int* bases, int cnt){
    double* arr_dcml;
    double min, max, mean, median;

    arr_dcml = arr_create_dcml_nums(nums_str, bases, cnt);
    arr_bubble_sort(arr_dcml, cnt);
    arr_find_min_max(arr_dcml, cnt, 1, &min, &max);
    mean = arr_mean(arr_dcml, cnt);
    median = arr_median(arr_dcml, cnt, 1);

    print_arr(arr_dcml, cnt);
    printf("min: %g\nmax: %g\nmean: %g\nmedian: %g\n", min, max, mean, median);

    free(arr_dcml);
}


int main(){
    char* s[] = {"15.7", "D.a", "1101.101", "25.75", "40.gf"}; 
    int bs[] = {8, 16, 2, 10, 40};  
    int k = 5;
    arr_full_analyze(s, bs, k);

    return 0;
}
