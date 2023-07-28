#include <stdio.h>

void troca(int *pa, int *pb) {
    int trc;
    trc = *pa;
    *pa = *pb;
    *pb = trc;
}

int main() {
    int a, b;

    printf("Digite a: ");
    scanf("%d", &a);
    printf("Digite b: ");
    scanf("%d", &b);

    troca(&a, &b);

    printf("a = %d e b = %d\n", a, b);
    return 0;
}
