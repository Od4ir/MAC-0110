#include <stdio.h>

int main () {
    char op = 'b';
    int num = 0;

    while(op != 'a') {
        scanf(" %c", &op);
        printf("%c\n", op);
        printf("Passada %d\n", num);
        num++;
    }

}