#include "telemetry_analyzer.h"

void arr_full_analyze(char** nums_str, int* bases, int cnt){
    double* arr_dcml;
    double min, max, mean, median;

    arr_dcml = arr_create_dcml_nums(nums_str, bases, cnt);
    if (arr_dcml == NULL){
        puts("array error, function break");
        return;
    }
    arr_bubble_sort(arr_dcml, cnt);
    arr_find_min_max(arr_dcml, cnt, 1, &min, &max);
    mean = arr_mean(arr_dcml, cnt);
    median = arr_median(arr_dcml, cnt, 1);

    print_arr(arr_dcml, cnt);
    printf("min: %g\nmax: %g\nmean: %g\nmedian: %g\n", min, max, mean, median);

    free(arr_dcml);
}
