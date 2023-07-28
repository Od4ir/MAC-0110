#include <stdio.h>

int main () {
    float f1, f2, f3, f4, f5, f6;
    int n, face, i;

    printf("Digite n: \n");
    scanf("%d", &n);
    i = n;
    f1 = f2 = f3 = f4 = f5 = f6 = 0;

    while(n != 0) {
        scanf("%d", &face);
        if(face == 1) f1++;
        else if(face == 2) f2++;
        else if(face == 3) f3++;
        else if(face == 4) f4++;
        else if(face == 5) f5++;
        else f6++;
        n--;
    }
    f1 /= i;
    f2 /= i;
    f3 /= i;
    f4 /= i;
    f5 /= i;
    f6 /= i;

    printf("f1: %f\n", f1);
    printf("f2: %f\n", f2);
    printf("f3: %f\n", f3);
    printf("f4: %f\n", f4);
    printf("f5: %f\n", f5);
    printf("f6: %f\n", f6);

    return 0;
}