#include "tests.h"
#include "coordinates_decoder.h"

void test_convertations(void){
    char *r = student1_process(16, 8, "FF");
    assert(r != NULL && strcmp(r, "377.0") == 0);
    free(r);

    r = student1_process(8, 16, "377");
    assert(r != NULL && strcmp(r, "FF.0") == 0);
    free(r);
}

void test_fractional(void){
    char *r = student1_process(16, 8, "a7.f1");
    assert(r != NULL && strcmp(r, "247.742") == 0);
    free(r);
}
void test_blya_nu_tut_ne_ebu(){}

void test_err(void){
    char *r = student1_process(32, 8, "a7.f1");
    assert(r == NULL);

    r = student1_process(16, 0, "a7.f1");
    assert(r == NULL);

    r = student1_process(16, 8, "a7.ffffffffff");
    assert(r == NULL);
    free(r);
}
int main(){
    test_blya_nu_tut_ne_ebu();
    test_convertations();
    test_err();
    test_fractional();
}
