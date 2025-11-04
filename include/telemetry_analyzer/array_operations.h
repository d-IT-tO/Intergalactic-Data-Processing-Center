#ifndef ARRAY_OPERATIONS_H
#define ARRAY_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>

void arr_copy(double* arr_cp, double* arr, int cnt);
void swap_nums(double* frst_num, double* scnd_num);
void arr_bubble_sort(double* arr, int cnt);
double arr_mean(double* arr, int cnt);
double arr_median(double* arr, int cnt, int is_sort);
void arr_find_min_max(double* arr, int cnt, int is_sort, double* min, double* max);
void print_arr(const double* arr, int cnt);

#endif
