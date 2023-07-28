#include <stdio.h>
#define MAX 256

int main() {
    int n, ja_foi;
    int i, j, k;
    double v[MAX];

    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        scanf("%lf", &v[i]);
    }

    for(i = 0; i < n; i++) {
        k = 0; ja_foi = 0;
        for(j = 0; (j < i)&&(!ja_foi); j++) {
            if(v[j] == v[i]) {
                ja_foi = 1;
            }
        }
        for(j = 0; (j < n)&&(!ja_foi); j++) {
            if(v[i] == v[j]) {
                k++;
            }
            if(j + 1 == n) {
                printf("%f apareceu %d vezes! \n", v[i], k);
            }
        }
    }
    return 0;
}