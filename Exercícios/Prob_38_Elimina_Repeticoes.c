#include <stdio.h>
#define MAX 256

void bubble_sort(int V[MAX], int n) {
    int iter, i = 1, trocou = 1, aux;

    for(iter = 1; (iter < n)&&(trocou); iter++) {
        i = 0;
        trocou = 0;
        while(i < n - iter) {
            if(V[i] > V[i + 1]) {
                aux = V[i + 1];
                V[i + 1] = V[i];
                V[i] = aux;
                trocou = 1;
            }
            i++;
        }
    }
}

int elimina_repet(int V[MAX, int n]) {
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

int main () {
    int n, i, j, k = 1;
    int v[MAX];
    int num, achou = 0;

    printf("Digite o número de termos: \n");
    scanf("%d", &n);
    printf("Digite os termos: \n");
    scanf("%d", &num);
    v[0] = num;

    for(i = 1; i < n; i++) {
        scanf("%d", &num);
        for(j = i - 1; (j >= 0)&&(!achou); j--) {
            if(v[j] == num) {
                achou = 1;
            }
            else if(j == 0) {
                v[k] = num;
                k++;
            }
        }
        achou = 0;
    } 

    printf("k = %d\n", k);
    printf("Aqui estão os termos sem repetição: \n");
    for(i = 0; i < k; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    bubble_sort(v, k);

    printf("Aqui estão os termos sem repetição e ordenados: \n");
    for(i = 0; i < k; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}
    /*int n, i, j, k = 0;
    scanf("%d", &n);

    int v[n];
    int srv[n];

    //Leitura do Vetor:
    for(int i = 0; i < n; i++) {
        scanf("%d", v[i]);
    }

    for(i = 0; i < n; i++) {
        for(j = 1; i + j < n; j++) {
            if(v[i] != v[i + j]) {
                srv[k] = v[i];
            }
        }
    }

    for() */





