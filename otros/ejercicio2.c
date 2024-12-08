#include <stdio.h>


int main() {
    int n = 11;
    int calculoMod = n % 3;

    if (calculoMod != 0) {
        printf("El numero ingresado es par. Intentelo nuevamente\n");
        return 0;
    }

    unsigned int a = 1;
    for (int i = n - 1; i > 0; i = i - 2 ){
        printf("a(viejo) : %d\n", a);
        a = a * i;
        printf("i: %d\n", i);
        printf("a(nuevo) : %d\n", a);
        printf("------\n\n");
    }

    printf("El segundo for");
    int b = 0;
    for( int i = 1; i <= n; i = i + 2 ){
        b = b + i;
        printf("%d\n", b);
    }

    int c = b^n;
    int total = a/c;

    printf("El total es %d \n", total);


    return 0;
}