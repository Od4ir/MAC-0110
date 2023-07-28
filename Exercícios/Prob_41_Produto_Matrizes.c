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

int main () {
  int m, n1, n2, p;
  int A[MAX][MAX], B[MAX][MAX];
  int C[MAX][MAX];
  int i, j;

  printf("Digite as dimensões das matriz: \n");
  printf("Matriz A: \n");
  scanf("%d %d", &m, &n1);
  printf("Matriz B: \n");
  scanf("%d %d", &n2, &p);

  if(n1 != n2) {
    printf("Não é possível calcular Matriz AxB");
  }
  else {
    printf("Digite a Matriz A: \n");
    lermatriz(m, n1, A);

    printf("Digite a Matriz B: \n");
    lermatriz(n2, p, B);

    for(i = 0; i < m; i++) {
      for(j = 0; j < p; j++) {
        C[i][j] = 0;
        for(int k = 0; k < n1; k++) {
          C[i][j] = C[i][j] + A[i][k]*B[k][j];
        }
      }
    }

    imp_mat(m, p, C);
    return 0;
  } 
}