#include "coordinates_decoder.h"
#include "telemetry_analyzer.h"

void navigation_decoder() {
    int src, dest;
    char* num = (char*)malloc(32 * sizeof(char));
    scanf("%d %d %31s", &src, &dest, num);

    char* result = student1_process(src, dest, num);
    if (result) {
        printf("Result: %s\n", result);
        free(result);
    }
    free(num)
}

void analyzer() {
    int cnt;
    puts("write the number of numbers");
    if (scanf("%d", &cnt) != 1) {
        puts("Invalid input for count.");
        return;
    }
    if (cnt < 1) {
        puts("error: Count must be 1 or greater.");
        return;
    }

    char** arr = malloc(cnt * sizeof(char*));
    int* base = malloc(cnt * sizeof(int));
    if (arr == NULL || base == NULL) {
        puts("malloc error");
        free(arr); 
        free(base);
        return;
    } 

    puts("Write the number and base by a space (max length: 63)");
    for (int i = 0; i < cnt; i++) {
        arr[i] = malloc(64 * sizeof(char));
        if (arr[i] == NULL) {
            puts("malloc error for number");
            for (int j = 0; j < i; j++) {
                free(*(arr + j));
            }
            free(arr);
            free(base);
            return;
        }
        if (scanf("%63s%d", *(arr + i), (base + i)) != 2) {
            puts("input error, num = 0, base = 2");
            *(arr + i) = "0";
            *(base + i) = 2;
        }
    }
    
    arr_full_analyze(arr, base, cnt);
    
    for (int i = 0; i < cnt; i++)
        free(*(arr + i));
    free(arr);
    free(base);
}

int main(){
    int choice;
    printf("Welcome to Intergalactic-Data-Processing-Center\n choose your action\n 1. Navigation coordinates decoder\n 2. Telemetry Analyzer\n 0. exit\n");
    while (1){
        scanf("%d", &choice);
        switch(choice){
            case 1:
                navigation_decoder();
                puts("Navigation coordinates decoder end");
                break;
            case 2:
                analyzer();
                puts("Telemetry Analyzer end");
                break;
            case 0:
                puts("program end");
                return 0;
        }
    }        
}


