#include <stdio.h>

void troca(int *a, int *b) {
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

int main() {
    int a, b;

    printf("Digite a: \n");
    scanf("%d", &a);
    printf("Digite b: \n");
    scanf("%d", &b);

    troca(&a, &b);
    printf("a = %d\n", a);
    printf("b = %d\n", b);

    return 0;
}

