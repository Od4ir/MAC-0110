#include <stdio.h>
#define MAX 356

int elimina_repet(int v[MAX], int n) {
    int i, j, k = 1;
    int achou;

    for(i = 1; i < n; i++) {
        achou = 0;
        for(j = 0; (j < i)&&(!achou); j++) {
            if(v[j] == v[i]) {
                achou  = 1;
            }
            else if (j + 1 == i) {
                v[k] = v[i];
                k++;
            }
        }
    }
    return k;
}

int main() {
    int n, v[MAX];
    int i = 0, k;

    scanf("%d", &n);

    while(i < n) {
        scanf("%d", &v[i]);
        i++;
    }

    k = elimina_repet(v, n);
    printf("k = %d\n", k);

    printf("Aqui estão os termos sem repetição: \n");
    for(i = 0; i < k; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
    
    return 0;
}

