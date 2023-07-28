#include <stdio.h>

/* Compara-se v[0] com todo mundo v[1], v[2], v[3]..., 
se v[3], por exemplo, for menor que v[0], v[0] assume 
o valor de v[3] e v[3] assume o valor de v[0]; Dessa 
forma, o primeiro elemento será o menor, depois partimos 
para a comparação de v[1] com todo mundo e assim vai... */

void selection_sort( int V[MAX], int n) {
  int i, j, aux ;

  for(i = 0; i < n - 1; i++) {
    for(j = i + 1; j < n; j++) {
      if(V[i] > V[j]) {
        aux = V[i] ;
        V[i] = V[j] ;
        V[j] = aux ;
      }
    }
  }  
}

/* Nesse método, são feitas comparações em pares do tipo: 
v[i] e v[i+1], e trocando suas posições se não estiverem em
ordem crescente. Assim, ao final da primeira iteração, o maior
elemento estará ocupando a última posição. Na próxima, o segundo
maior vai para a penúltima e assim por diante... A versão better
para caso já esteja ordenado e realiza uma comparação a menos
a cada iteração (já que o último elemento é o maior). Note a dife-
rença no for (j < n) e (j < n - passada)*/

void bubble_sort(int V[MAX], int n) {
  int passada, j, aux ;

  for(passada = 1; passada < n; passada++)
    for(j = 0; j < n - 1; j++) {
        if(V[j] > V[j+1]) {
            aux = V[j+1] ;
            V[j+1] = V[j] ;
            V[j] = aux ;
        }
    }
}

void bubble_sort_bettter( int V[MAX], int n){
  int passada, j, aux, trocou = 1;

  for(passada = 1; (passada < n)&&(trocou); passada++) {
        trocou = 0 ;
    
        /*Se não houve nenhuma troca, então já está ordenado,
        por isso temos a variável trocou*/
       
        for(j=0; j < n - passada; j++) {                                         
            if(V[j] > V[j+1]) {
                aux = V[j+1] ;
                V[j+1] = V[j] ;
                V[j] = aux ;
                trocou = 1 ;
            }
        }
    } 
}

/* Bom, é o mais complicadinho pelo jeito. É selecionado o elemento
v[i] primeiramente e tenta-se encaixar esse elemento na sequência de
0 até i - 1 (Perceba que no caso i = 0, ocorre apenas uma simples 
troca, se for necessário, de v[0] com v[1]) de forma que a sequência
"nova" esteja ordenada e assim por diante, até o último elemento. */

void insertion_sort(int x[], int n) {
  int i, j, aux ;
  for(i = 1; i < n; i++) {
        /* para cada elemento x[i] no vetor, fazer: */
        j = i - 1 ; 
        /* o trecho de 0 a i-1 está ordenada */

        /* Queremos agora encontrar a posição na qual
       x[i] será inserida. Vamos fazer essa busca
       da posição i-1 para trás. Enquanto fazemos essa
       busca, já vamos deslocando cada elemento
       com o qual comparamos para uma posição posterior */

        aux = x[i] ;
    
        /* no while seguinte, quando j<0, a primeira
       condição fica falsa e a segunda condição nem
       é testada. Assim, não há problema de acesso
       a um indice negativo ... */

        while (j >= 0 && x[j]>aux) {
            x[j+1] = x[j] ;
            j=j-1 ;
        }

        /* acabamos de abrir um espaço na posição j+1
       para encaixar x[i] */
       
        x[j+1] = aux ;
        i = i+1 ;
    }
}
