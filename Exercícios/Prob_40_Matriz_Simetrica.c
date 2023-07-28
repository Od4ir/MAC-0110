#include <stdio.h>
#define MAX 256

void lermatriz(int m, int n, int M[MAX][MAX]) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &M[i][j]);
        }
    }
}

void imp_mat(int m, int n, int M[MAX][MAX]) {
    int i, j ;
    for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++)
        printf("%d ", M[i][j]) ;
      printf("\n") ;
    }
}

int main() {
    int n, mat[MAX][MAX];
    int i = 0, j = 0;
    int simetria = 1;

    printf("Digite n: \n");
    scanf("%d", &n);

    printf("Digite a matriz; \n");
    lermatriz(n, n, mat);
    int k = 1;

    for(i = 0; (i < n - 1)&&(simetria); i++) {
        for(j = i + 1; (j < n)&&(simetria); j++) {
            if(mat[i][j] != mat[j][i]) {
                simetria = 0;
            }
        }
    }

    if(simetria) {
        printf("É Simétrica\n");
    }
    else {
        printf("Não é simétrica!\n");
    }
}