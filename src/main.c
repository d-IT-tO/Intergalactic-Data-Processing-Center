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
}

void analyzer(){
    int cnt;
    puts("write the number of numbers");
    scanf("%d", &cnt);
    if (cnt < 1){
        puts("error");
        return;
    }   
    char** arr = malloc(cnt * sizeof(char*));
    int* base = malloc(cnt * sizeof(int));
    if (arr == NULL || base == NULL)
        puts("malloc error");
    else{
        puts("Write the number and base by a space");
        for (int i = 0; i < cnt; i++)
            scanf("%s%d", *(arr + i), (base + i));
        arr_full_analyze(arr, base, cnt);
    }
    free(arr);
    free(base);
    return 0;
}

int main(){
    int choice;
    printf("Welcome to Intergalactic-Data-Processing-Center\n choose your action\n 1. Navigation coordinates decoder\n 2. Telemetry Analyzer\n 0. exit\n");
    while (1){
        switch(scanf("%d", &choice)){
            case 1:
                navigation_decoder();
                puts("Navigation coordinates decoder end");
                continue;
            case 2:
                analyzer();
                puts("Telemetry Analyzer end");
                continue;
            case 0:
                puts("program end");
                return 0;
        }
    }
        
}
