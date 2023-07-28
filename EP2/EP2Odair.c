#include <stdio.h>
#define PI 3.14159
#define RAIO_AP 200
#define RAIO_ZA 2000 
#define DELTA_ALARME 60
#define EPS_COS 0.000001
#define EPS 0.01

double pot(double base, int expo);
int iguais(double x, double y);
double raiza(double x, double epsilon);
double dista(double x1, double y1, double x2, double y2); 
double cossena (double theta, double epsilon); 
int localiza ( double xi, double yi, double div1, double xj, double yj, double djv, double xk, double yk, double dkv,double *xv, double *yv); 
int raizeq(double a, double b, double c, double *r1, double *r2);
int intercepta(double x0, double y0, double x1, double y1, double *x, double *y);
double velocidade(double x0, double y0, double x1, double y1, double deltaT); 

int main() {
    FILE *arq;
    char filename[256];
    int n_casos, i_veiculo, local, intercept, alarm, i = 0, j = 1;
    double ant[6][6];
    double delta_t;
    double x0, y0, x1, y1, xv, yv, speed, delta_s;

    printf("================================================\n");
    printf("///           Seja Bem-Vindx Ao              ///\n");
    printf("/// PROGRAMA DE MONITORAMENTO - CIDADE OD4IR ///\n");
    printf("================================================\n\n");

    printf("Por favor, digite o nome do arquivo de entrada: ");
    scanf("%s", filename);
    printf("\n");

    arq = fopen(filename, "r");

    fscanf(arq, "%d", &n_casos);
    if(n_casos == 1) {
        printf("Thank you! Há 1 caso para ser analisado hoje! \n\n");
    }
    else {
        printf("Thank you! Há %d casos para serem analisados hoje! \n\n", n_casos);
    }
    while(n_casos != 0) {
        alarm = 0;
        fscanf(arq, "%d", &i_veiculo);
        while(i != 6) {
            fscanf(arq, "%lf", &ant[i][0]);
            while(j != 5) {
                fscanf(arq, "%lf", &ant[i][j]);
                j++;
            }
            i++;
            j = 1;
            if(i == 3) {
                fscanf(arq, "%lf", &delta_t);
            }
        }
        i = 0;
        printf("================================================\n");
        printf("           || VEICULO ANALISADO: %d ||          \n\n", i_veiculo);

        printf("/// Antenas Posição Pŕevia: ///\n");
        printf("-------------------------------------------------------------------------------------------\n");
        printf("|  ANTENA  |        COORDENADAS        |      H(m)    |   ANGULO(graus)  |  DISTANCIA(m)  |\n");
        printf("-------------------------------------------------------------------------------------------\n");
        while(i != 3) {
            ant[i][5] = ant[i][3]*(cossena(ant[i][4], EPS_COS));
            printf("|    %2.f    |   (%8.2f , %8.2f)   |  %8.2fm   |      %6.2f      |   %8.2fm    |\n", ant[i][0], ant[i][1], ant[i][2], ant[i][3], ant[i][4], ant[i][5]);
            i++;
        }
        printf("-------------------------------------------------------------------------------------------\n");

        local = localiza (ant[0][1], ant[0][2], ant[0][5], ant[1][1], ant[1][2], ant[1][5], ant[2][1], ant[2][2], ant [2][5], &x0, &y0);

        if(local == 0) {
            printf("Sorry, não é possível calcular a posição prévia do veículo %d!\n", i_veiculo);
            printf("Não é possível determinar a situação do veículo %d!\n\n", i_veiculo);
        }
        else {
            printf("/// Localização Pŕevia: ( %.2f, %.2f ) /// \n\n", x0, y0);

            printf("Intervalo de Tempo:.......%.2fs\n\n", delta_t);

            printf("/// Antenas Posição Atual: ///\n");
            printf("-------------------------------------------------------------------------------------------\n");
            printf("|  ANTENA  |        COORDENADAS        |      H(m)    |   ANGULO(graus)  |  DISTANCIA(m)  |\n");
            printf("-------------------------------------------------------------------------------------------\n");
            while(i != 6) {
                ant[i][5] = ant[i][3]*(cossena(ant[i][4], EPS_COS));
                
                printf("|    %2.f    |   (%8.2f , %8.2f)   |  %8.2fm   |      %6.2f      |   %8.2fm    |\n", ant[i][0], ant[i][1], ant[i][2], ant[i][3], ant[i][4], ant[i][5]);
                i++;
            }
            printf("-------------------------------------------------------------------------------------------\n");
            
            local = localiza (ant[3][1], ant[3][2], ant[3][5], ant[4][1], ant[4][2], ant[4][5], ant[5][1], ant[5][2], ant [5][5], &x1, &y1);

            if(local == 0) {
                printf("Não é possível calcular a posição atual do veículo %d!\n", i_veiculo);
                printf("Não é possível determinar a situação do veículo %d!\n\n", i_veiculo);
            }
            else {
                printf("/// Localização Atual: ( %.2f, %.2f ) /// \n", x1, y1);
                printf("\n");

                speed = velocidade(x0, y0, x1, y1, delta_t);
                delta_s = speed*delta_t;

                printf("Distância Percorrida:..... %.2fm\n", delta_s);
                printf("Velocidade Média:......... %.2fm/s\n", speed);
                printf("Distância da Origem........%.2fm\n\n", dista(x1, y1, 0, 0));

                if(iguais(speed, 0)) {
                    printf("VEÍCULO %d ESTACIONADO ", i_veiculo);
                }
                else {
                    printf("VEÍCULO %d EM MOVIMENTO ", i_veiculo);
                }

                if(dista(x1, y1, 0, 0) >= RAIO_ZA) {
                    printf("FORA DA ZONA DE ALERTA\n\n");
                } 
                else {
                    if(dista(x1, y1, 0, 0) <= RAIO_AP) {
                        printf("DENTRO DA AP\n\n");
                        alarm = 1;
                    }
                    else {
                        printf("DENTRO DA ZONA DE ALERTA\n\n");
                        if(!iguais(speed, 0)) {
                            intercept = intercepta(x0, y0, x1, y1, &xv, &yv);
                            if(intercept == 1) {
                                printf("!!! Trajetória Intercepta AP !!!\n\n");
                                printf("Distância do veículo até AP:........%.2fm\n", dista(x1, y1, xv, yv));
                                printf("Interceptação ocorrerá em:..........%.2f s,\n",(dista(x1, y1, xv, yv))/speed);
                                printf("Nas coordenadas:....................(%.2f, %.2f)!\n\n", xv, yv);
                                if((dista(x1, y1, xv, yv))/speed < DELTA_ALARME) {
                                    alarm = 1;
                                }
                            }
                            else {
                                printf("Trajetória NÃO Intercepta AP!\n\n");
                            }
                        }
                    }
                }
            }
        }
        if(alarm == 1) {
            printf("***********************************************\n");
            printf("ALARME! ALARME! ALARME! ALARME! ALARME! ALARME!\n");
            if(dista(x1, y1, 0, 0) <= RAIO_AP) {
                printf("         VEICULO %d ESTA NA AP!!!        \n", i_veiculo);
            }
            else {
            printf("              INVASAO IMINENTE!!!              \n");
            }
            printf("***********************************************\n\n");
        }
        n_casos--;
        i = 0;
    }
    printf("================================================\n\n");
    printf("Fim da analise de hoje! Muito obrigado por usar nosso Sistema de Monitoramento!\n");
    printf("Até breve!\n\n");
    fclose(arq);
    return 0;
}

/*FUNÇÃO POTENCIAÇÃO*/
double pot(double base, int expo) {
    double pot = 1;
    while (expo != 0) {
        pot = pot * base;
        expo--;
    }
    return pot;
}
/*FUNÇÃO IGUAIS*/
int iguais(double x, double y) {
    if((x-y < EPS)&&(y-x < EPS)) {
        return 1;
    }
    else {
        return 0;
    }
}
/*FUNÇÃO RAIZ QUADRADA*/
double raiza(double x, double epsilon) {
    double raiz1, raiz2, raiz0 = x, mod = 1;
    if(iguais(x, 0)) {
        return 0;
    }
    else { 
        while((mod > epsilon)&&(x > 1)) {
            raiz1 = 0.5*(raiz0 + x/raiz0);
            raiz2 = 0.5*(raiz1 + x/raiz1);
            mod = raiz2 - raiz1;
            if(mod < 0) {
                mod = mod*(-1);
            }
            raiz0 = raiz2;
        }
        return raiz0;
    }
}
/*FUNÇÃO DISTÃNCIA 2 PONTOS*/
double dista(double x1, double y1, double x2, double y2) {
    double dista = raiza((x1 - x2)*(x1 - x2)+(y1 - y2)*(y1 - y2), EPS);
    return dista;
}
/*FUNÇÃO COSSENO*/
double cossena (double theta, double epsilon) {
    double cosx = 1;
    int k = 1, fat = 2, f = 3; 
    theta = (theta*PI)/180;
    while((pot(theta,2*k)/fat) >= epsilon) {
        cosx = cosx + (pot(-1,k)*(pot(theta,2*k)/fat));
        k++;
        fat = fat*(f)*(f + 1);
        f = f + 2;
    }
    cosx = cosx + (pot(-1,k)*(pot(theta,2*k)/fat)); 
    return cosx;
}
/*FUNÇÃO LOCALIZAÇÃO*/
int localiza ( double xi, double yi, double div1, double xj, double yj, double djv, double xk, double yk, double dkv,double *xv, double *yv) {
    double x_ok, y_ok, d_ok, a, b, c, d;
    if (iguais(xi, xj)&&iguais(xi, xk)){
        return 0;
    }
    else {
        if ((!iguais(xi, xj))&&(!iguais(xi, xk))) { 
            x_ok = xi;
            y_ok = yi;
            d_ok = div1;
        }
        else {
            if (iguais(xi, xj)) {
                x_ok = xk; xk = xi;
                y_ok = yk; yk = yi;
                d_ok = dkv; dkv = div1;
            }
            else {
                x_ok = xj; xj = xi;
                y_ok = yj; yj = yi;
                d_ok = djv; djv = div1;
            }
        }
        a = (pot(x_ok, 2) + pot(y_ok, 2) - pot(d_ok, 2)) - (pot(xj, 2) + pot(yj,2) - pot(djv, 2));
        a = a/(2*(x_ok - xj));
        
        b = (yj - y_ok)/(x_ok - xj);
        
        c = (pot(x_ok, 2) + pot(y_ok, 2) - pot(d_ok, 2)) - (pot(xk, 2) + pot(yk,2) - pot(dkv, 2));
        c = c/(2*(x_ok - xk));

        d = (yk - y_ok)/(x_ok - xk);

        if(iguais((b - d), 0)) {
            return 0;
        }
        else {
            *yv = (c - a)/(b - d);
            *xv = a + b*(*yv);
            return 1;
        }
    }
}
/*FUNÇÃO RAIZ DE EQUAÇÃO 2º GRAU*/
int raizeq(double a, double b, double c, double *r1, double *r2) {
    double delta = b*b - 4*(a*c);
    if (delta < 0) {
        return 0;
    }
    else {
        delta = raiza(delta, EPS);
        *r1 = (-b + delta)/(2*a);
        *r2 = (-b - delta)/(2*a);
        if (iguais(delta, 0)) {
            return 1;
        }
        else {
            return 2;
        }
    }
}
/*FUNÇÃO INTERCEPTA*/
int intercepta(double x0, double y0, double x1, double y1, double *x, double *y) {
    double a, c, alpha, xr1, xr2, yr1, yr2; /*b não é utilizado (ax +by + c = 0) pois b = 1 no caso em que importa; */
    int intercept;

    /*Fazendo (x1 - x0, y1 - y0) temos um vetor (vetor no sentido de vetor geométrico, não de array) que aponta para o sentido da trajetória,
    e fazendo (xi - x1, yi - y1), com xi e yi sendo as coordenadas do ponto de intersecção da reta da trajetória com a circunferencia, temos 
    um outro vetor que sai da posição atual e aponta para o ponto de intersecção. Se ambos os vetores tiverem mesmo sentido, 
    alpha = (x1 - x0)/(xi - x1) vai ter sinal positivo, loco, ocorre interceptação caso a trajetória continue. Se alpha tiver sinal negativo,
    os vetores tem sentidos opostos, logo, mesmo que a trajetória continue, não ocorrerá interceptação. */

    /*Caso em que a reta é paralela ao eixo y: */
    if (iguais(x0, x1)) {
        if((x1 >= RAIO_AP)||(x1 <= -RAIO_AP)) {
            return 0;
        }
        else {
            *x = x0;
            *y = raiza(RAIO_AP*RAIO_AP - x0*x0, EPS);
            /*Para garantir que seja o ponto mais próximo de (x1,y1): */
            if(y1 < 0) {
                *y = -(*y);
            }
            alpha = (y1 - y0)/(*y - y1);
            if(alpha > 0) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
    else {
        a = -1*((y1 - y0)/(x1 - x0));
        c = -a*x0 - y0;
        intercept = raizeq((a*a + 1), (2*a*c), (c*c - RAIO_AP*RAIO_AP) , &xr1, &xr2);
        yr1 = -a*xr1 - c;
        yr2 = -a*xr2 - c;

        if(intercept != 0) { 
            if(dista(xr1, yr1, x1, y1) < dista(xr2, yr2, x1, y1)) {
                *x = xr1;
                *y = yr1;
            }
            else {
                *x = xr2;
                *y = yr2;
            }
            alpha = (x1 - x0)/(*x - x1);
            if(alpha >= 0) {
                return 1;
            }
            else {
                return 0;
            }
        }
        else {
            return 0;
        }
    }
}
/*FUNÇÃO VELOCIDADE*/
double velocidade(double x0, double y0, double x1, double y1, double deltaT) {
    double v_media = 0;
    double vx, vy;
    vx = (x0 - x1)/deltaT;
    vy = (y0 - y1)/deltaT;
    v_media = raiza((vx*vx + vy*vy), EPS);
    return v_media;
}