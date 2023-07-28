#include <stdio.h>

int main() {
    int n, i = 0, j = 0, k = 0, magic = 1;

    printf("Insira a dimensão do quadrado, por favor: ");
    scanf("%d", &n);

    int quad[n][n], soma[2*n + 2];

    //Leitura da matriz:
    while(i != n) {
        while(j != n) {
            scanf("%d", &quad[i][j]);
            j++;
        }
        i++;
        j = 0;
    }
    i = 0;

    //Soma linhas:
    while(i != n) {
        soma[k] = 0;
        while(j != n) {
            soma[k] = soma[k] + quad[i][j];
            j++;
        }
        i++;
        k++; 
        j = 0;
    }
    i = 0; soma[k] = 0;

    //Soma colunas:
    while(j != n) {
        while(i != n) {
            soma[k] = soma[k] + quad[i][j];
            i++;
        }
        j++;
        k++;
        soma[k] = 0;
        i = 0;
    }
    j = 0;

    //Soma diagonais;
    while(j != n) {
        soma[k] = soma[k] + quad[j][j];
        j++;
    }
    k++;
    soma[k] = 0;
    while(j != 0) {
        soma[k] = soma[k] + quad[n - j][j - 1];
        j--;
    }
    i = 1;

    while(( i != k)&&(magic)) {
        if(soma[i] != soma[0]) {
            magic = 0;
        }
        else{
            i++;
        }
    }
    if(magic) {
        printf("É um quadrado mágico!\n");
    }
    else {
        printf("Não é um quadrado mágico!\n");
    }
}    




