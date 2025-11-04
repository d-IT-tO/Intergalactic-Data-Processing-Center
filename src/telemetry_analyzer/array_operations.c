#include "array_operations.h"

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

void print_arr(const double* arr, int cnt){
    for (int i = 0; i < cnt; i++)
        printf("%g ", *(arr + i));
    printf("\n");
}
