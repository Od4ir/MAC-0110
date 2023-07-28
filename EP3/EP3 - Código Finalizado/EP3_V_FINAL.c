#include <stdio.h>
#include <stdlib.h>
#define MAX 256
#define MAXX 255

int *load_image_from_file(char *filename, int *w, int *h);
void save_image_to_file(char *filename, int *I, int w, int h);
int *binarize(int *I, int w, int h, int t);
int *invert_image(int *I, int w, int h);
int *bordear(int *I, int w, int h, int d);
int *filter_image(int *I, int w, int h, int d, int tipo);
void selection_sort( int *V, int n);
int *zerarbordas(int *I, int w, int h);
int *label_components(int *I, int w, int h, int *ncc);

int main() {
    char arq_name[MAX];
    int *I, *R, w, h;
    char opcao, volta = 1, leu = 0;
    int limiar, tipo, tamanhofiltro, i, ncc;
    int fezmallocI = 0, fezmallocR = 0;

    printf("///------------------------------------------------///\n");
    printf("///                  Olá Usuárix!                  ///\n");
    printf("///    Bem vindx ao Manipulador de Imagens Od4ir   ///\n");
    printf("///------------------------------------------------///\n");

    while(volta) {
        printf(">>>          Por favor, escolha uma opção:         <<<\n\n");
        printf("> L - Ler um arquivo de imagem;\n");
        if(leu) {
            printf("> S - Salvar a imagem em um arquivo;\n");
            printf("> M - Manter a imagem anterior a transformação;\n");
            printf("> B - Binarizar a imagem-entrada;\n");
            printf("> C - Calcular Contorno da imagem;\n");
            printf("> F - Filtrar a imagem;\n");
            printf("> I - Inverter a imagem;\n");
            printf("> R - Rotular a imagem;\n");
        }
        printf("> Q - Quit (terminar o programa);\n\n");

        printf("---> ");
        scanf(" %c", &opcao);

        if((opcao == 'Q')||(opcao == 'q')) {
            volta = 0;
            if(fezmallocI) {
                free(I);
                I = NULL;
            }
            if(fezmallocR) {
                free(R);
                R = NULL;
            }
            printf("Programa Encerrado!\n");
        }
        else if((opcao == 'L')||(opcao == 'l')) {
            printf("Ok! Vamos LER um arquivo!\n");
            if(fezmallocI) {
                free(I);
                I = NULL; 
            }
            if(fezmallocR) {
                free(R);
                R = NULL;
            }
            printf("Digite o nome do arquivo: ");
            scanf("%s", arq_name);
            I = load_image_from_file(arq_name, &w, &h);
            fezmallocI = 1;
            leu = 1;
            printf("Tamanho da Imagem: %d x %d\n", w, h);
        }
        else if((opcao == 'S')||(opcao == 's')) {
            printf("OK! Vamos SALVAR o arquivo!\n");
            printf("Digite o nome do arquivo: ");
            scanf("%s", arq_name);

            if((fezmallocI)&&(!fezmallocR)) {
                save_image_to_file(arq_name, I, w, h);
            }
            else if(fezmallocR) {
                save_image_to_file(arq_name, R, w, h);
            }
            else {
                printf("Não foi possível salvar o arquivo! \n");
            }
        }
        else if((opcao == 'M')||(opcao == 'm')) {
            if(fezmallocR) {
                free(R);
                R = NULL;
                fezmallocR = 0;
            }
            printf("Imagem anterior mantida!\n");
        }
        else if((opcao == 'B')||(opcao == 'b')) {
            printf("Ok! vamos BINARIZAR a imagem!\n");
            printf("Digite o limiar: ");
            scanf("%d", &limiar);
            if(fezmallocR) {
                free(I);
                I = NULL;
                I = R;
            }
            R = binarize(I, w, h, limiar); fezmallocR = 1;
        }
        else if((opcao == 'C')||(opcao == 'c')) {
            printf("Ok! vamos CALCULAR O CONTORNO da imagem!\n"); 
            if(fezmallocR) {
                free(I);
                I = NULL;
                I = R;
            }
            R = filter_image(I, w, h, 3, 1); fezmallocR = 1;

            for(i = 0; i < w*h; i++) {
                R[i] = I[i] - R[i];
            }
            printf("Contorno Calculado! \n");
        }
        else if((opcao == 'I')||(opcao == 'i')) {
            printf("Ok! vamos INVERTER a imagem!\n");
            if(fezmallocR) {
                free(I);
                I = NULL;
                I = R;
            }
            R = invert_image(I, w, h); fezmallocR = 1;
        }
        else if((opcao == 'F')||(opcao == 'f')) {
            printf("Ok! vamos FILTRAR a imagem!\n");
            printf("Digite o tipo de filtro: \n");
            printf("> 1 - Mínimo\n> 2 - Médio\n> 3 - Máximo\n ---> ");
            scanf("%d", &tipo);
            printf("Digite o tamanho do filtro: ");
            scanf("%d", &tamanhofiltro);

            if(fezmallocR) {
                free(I);
                I = NULL;
                I = R;
            }

            R = filter_image(I, w, h, tamanhofiltro, tipo);
            fezmallocR = 1;
            printf("Imagem Filtrada! \n");
        }
        else if((opcao == 'R')||(opcao == 'r')) {
            printf("Ok! vamos ROTULAR a imagem!\n");
            if(fezmallocR) {
                free(I);
                I = NULL;
                I = R;
            }
            R = label_components(I, w, h, &ncc);
            printf("Número de componentes conexos: %d\n", ncc);
        }
        printf("------------------------------------------------------\n");
    }
    return 0;
}

int *load_image_from_file(char *filename, int *w, int *h) {
    FILE *f;
    char line[MAX];
    int max, i;
    int *I;

    f = fopen(filename, "r");

    fscanf(f, "%[^\n]\n", line);
    fscanf(f, "%d", &(*w));
    fscanf(f, "%d", &(*h));
    fscanf(f, "%d", &max);

    I = malloc(sizeof(int)*(*w)*(*h));

    for(i = 0; i < (*w)*(*h); i++) {
        fscanf(f, "%d", &I[i]);
    }

    printf("Arquivo lido! \n");
    fclose(f);
    return I;
}

void save_image_to_file(char *filename, int *I, int w, int h) {
    FILE *f;
    int i, j;

    f = fopen(filename, "a");
    fprintf(f, "P2\n");
    fprintf(f, "%d ", w);
    fprintf(f, "%d\n", h);
    fprintf(f, "%d\n", MAXX);

    for(i = 0; i < h; i++) {
        for(j = 0; j < w; j++) {
            fprintf(f, "%d ", I[i*w + j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Arquivo salvo! \n");
}

int *invert_image(int *I, int w, int h) {
    int *R;
    int i;

    R = malloc(sizeof(int)*w*h);

    for(i = 0; i < w*h; i++) {
        R[i] = MAXX - I[i];
    }
    printf("Imagem Invertida! \n");
    return R;
}

int *binarize(int *I, int w, int h, int t) {
    int *R;
    int i = 0;

    R = malloc(sizeof(int)*w*h);

    for(i = 0; i < w*h; i++) {
        if(I[i] >= t) {
            R[i] = MAXX;
        }
        else {
            R[i] = 0;
        }
    }
    printf("Imagem Binarizada! \n");
    return R;
}

int *filter_image(int *I, int w, int h, int d, int tipo) {
    int *Ifilt, *V, *R;
    int num;
    int i, j, i1, j1, k = 0, l = 0;
    num = (d - 1)/2;

    //V - Vetor dos pontos da matriz d x d;
    V = malloc(sizeof(int)*d*d);
    R = malloc(sizeof(int)*w*h);

    Ifilt = bordear(I, w, h, d);

    for(i = num; i < num + h; i++) {
        for(j = num; j < num + w; j++) {
            for(i1 = i - num; i1 <= i + num; i1++) {
                for(j1 = j - num; j1 <= j + num; j1++) {
                    V[k] = Ifilt[i1*(2*num + w) + j1];
                    k++;
                    if(k == d*d) {
                        selection_sort(V, d*d);
                        if(tipo == 1) {
                            R[l] = V[0];
                        }
                        else if(tipo == 2) {
                            R[l] = V[(d*d - 1)/2];
                        }
                        else if(tipo == 3) {
                            R[l] = V[d*d - 1];
                        }
                        l++;
                        k = 0;
                    }
                } 
            }
        }
    }

    free(V);
    V = NULL;
    k = 0;   

    free(Ifilt);
    Ifilt = NULL;

    return R;
}

int *bordear(int *I, int w, int h, int d) {
    int num, i, j, i1, j1;
    int *Ic;

    //num - Número de linhas e colunas a se aumentar;
    //Ic - Imagem Cópia com linhas e colunas aumentadas;

    num = (d - 1)/2;
    Ic = malloc(sizeof(int)*(w + 2*num)*(h + 2*num));

    for(i = 0; i < (w + 2*num)*(h + 2*num); i++) {
        Ic[i] = 0;
    }

    //Linhas de cima:
    for(i = 0; i <= num; i++) {
        for(j = 0; j < w; j++) {
            Ic[i*(w + 2*num) + (j + num)] = I[j];
        }
    }
    //Linhas de baixo:
    for(i = h + 2*num - 1; i > (h + 2*num - 2 - num); i--) {
        for(j = 0; j < w; j++) {
            Ic[i*(w + 2*num) + (j + num)] = I[(h - 1)*w + j];
        }
    }

    //Coluna esquerda:
    for(j = 0; j <= num; j++) {
        for(i = 0; i < h; i++) {
            Ic[(i + num)*(w + 2*num) + j] = I[i*w];
        }
    }

    //Coluna direita:
    for(j = w + 2*num - 1; j > (w + 2*num - 2 - num); j--) {
        for(i = 0; i < h; i++) {
            Ic[(i + num)*(w + 2*num) + j] = I[i*w + (w - 1)];
        }
    }

    //Cantos de cima:
    for(i = 0; i < num; i++) {
        for(j = 0; j < num; j++) {
            Ic[i*(2*num + w) + j] = I[0];
        }
        for(j = num + w; j < (2*num + w); j++) {
            Ic[i*(2*num + w) + j] = I[w - 1];
        }
    }

    //Cantos de baixo:
    for(i = num + h; i < (2*num + h); i++) {
        for(j = 0; j < num; j++) {
            Ic[i*(2*num + w) + j] = I[(h - 1)*w];
        }
        for(j = num + w; j < (2*num + w); j++) {
            Ic[i*(2*num + w) + j] = I[(h - 1)*w + (w -1)];
        }
    }

    //Meio:
    for(i = 1, i1 = num + 1; (i < h - 1)&&(i1 < num + h - 1); i++, i1++) {
        for(j = 1, j1 = num + 1; (j < w - 1)&&(j1 < num + w - 1); j++, j1++) {
                Ic[i1*(2*num + w)+ j1] = I[i*w + j];
        }
    }
    return Ic;
}

int *zerarbordas(int *I, int w, int h) { 
    int *Izero;
    int i, j;

    Izero = malloc(sizeof(int)*(w + 2)*(h + 2));

    for(i = 0; i < h + 2; i++) {
        for(j = 0; j < w + 2; j++) {
            Izero[i*(w + 2) + j] = 0;
        }
    }

    for(i = 1; i < h + 1; i++) {
        for(j = 1; j < w + 1; j++) {
            Izero[i*(w + 2) + j] = I[(i - 1)*w + (j - 1)];
        }
    }
    return Izero;
}

void selection_sort( int *V, int n) {
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

int *label_components(int *I, int w, int h, int *ncc) {
    int *Izero, *R;
    int i, j, i1, j1, k = 1;
    int cont = 0, aux, num = 0, contando;
    int *Vlin, *Vcol;

    Vlin = malloc(sizeof(int)*w*h);
    Vcol = malloc(sizeof(int)*w*h);
    R = malloc(sizeof(int)*w*h);

    for(i = 0; i < w*h; i++) {
        R[i] = 0;
    }

    Izero = zerarbordas(I, w, h);

    for(i = 1; i < h + 1; i++) {
        for(j = 1; j < w + 1; j++) {
            if(Izero[i*(w + 2) + j] != 0) {
                aux = -1;
                Vlin[aux + 1] = i;
                Vcol[aux + 1] = j;
                if(R[(i - 1)*w + (j - 1)] == 0) {
                    R[(i - 1)*w + (j - 1)] = k;
                    k++;
                }
                aux++;
                for(cont = aux; cont <= aux; cont++) { 
                    for(i1 = Vlin[cont] - 1; i1 <= Vlin[cont] + 1; i1++) {
                        for(j1 = Vcol[cont] - 1; j1 <= Vcol[cont] + 1; j1++) {
                            if((i1 != 0)&&(i1 != h + 1)&&(j1 != 0)&&(j1 != w + 1)) { 
                                if(R[(i1 - 1)*w + (j1 - 1)] == 0) {
                                    if(Izero[i1*(w + 2) + j1] != 0)  {    
                                        aux++;
                                        Vlin[aux] = i1;
                                        Vcol[aux] = j1;
                                        R[(i1 - 1)*w + (j1 - 1)] = k - 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    *ncc = k - 1;
    j = 0;
    if(*ncc <= 127) {
        for(i = 1; i < *ncc; i++) {
            for(j = 0; j < w*h; j++) {
                if(R[j] == i) {
                    R[j] = i*(255/(*ncc));
                }
            }
        }
    }

    free(Vlin); free(Vcol); free(Izero);
    Vlin = NULL; Vcol = NULL; Izero = NULL;
    return R;
}


