#include <coordinates_decoder.h>

int main() {
    int src, dest;
    char* num = (char*)malloc(32 * sizeof(char));
    scanf("%d %d %31s", &src, &dest, num);

    char* result = student1_process(src, dest, num);
    if (result) {
        printf("Результат: %s\n", result);
        free(result);
    }
    return 0;
}

