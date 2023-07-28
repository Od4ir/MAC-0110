#include <stdio.h>
#define PI 3.14159
#define RAIO_AP 200
#define RAIO_ZA 2000 
#define DELTA_ALARME 60
#define EPS_COS 0.000001 
#define EPS 0.01

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
    double raiz1, raiz2, raiz0 = x;
    double mod = 1;
    
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

/*FUNÇÃO DISTÃNCIA 2 PONTOS*/
double dista(double x1, double y1, double x2, double y2) {
    double dista = raiza(((x1*x1 - x2*x2)+(y1*y1 - y2*y2)), EPS);
    return dista;
}

/*FUNÇÃO COSSENO*/
double cossena (double theta, double epsilon) {
    double cosx = 1;
    int k = 1;
    int fat = 2; 
    theta = (theta*PI)/180;
    
    if(theta == PI/2) {
        cosx = 0;
    }
    else {
        while((pot(theta,2*k)/fat) >= epsilon) {
            cosx = cosx + (pot(-1,k)*(pot(theta,2*k)/fat));
            k++;
            fat = fat*(k + 1)*(k + 2);
        }
        cosx = cosx + (pot(-1,k)*(pot(theta,2*k)/fat)); 
    }
    return cosx;
}

/*FUNÇÃO LOCALIZAÇÃO*/
int localiza ( double xi, double yi, double div1, 
double xj, double yj, double djv, 
double xk, double yk, double dkv,
double *xv, double *yv) {
    double x_ok, y_ok, d_ok;
    double a, b, c, d;

    if (iguais(xi, xj)&&iguais(xi, xk)){
        return 0;
    }
    else {
        if ((xi != xj)&&(xi != xk)){
            x_ok = xi;
            y_ok = yi;
            d_ok = div1;
        }
        else {
            if (iguais(xi, xj)) {
                x_ok = xk;
                y_ok = yk;
                d_ok = dkv;
                xk = xi;
                yk = yi;
                dkv = div1;
            }
            else {
                x_ok = xj;
                y_ok = yj;
                d_ok = djv;
                xj = xi;
                yj = yi;
                djv = div1;
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
    double delta;
    delta = b*b - 4*(a*c);

    if (delta < 0) {
        return 0;
    }
    else {
        delta = raiza(delta, EPS);
        if (iguais(delta, 0)) {
            delta = 0;
        }
        *r1 = (-b + delta)/(2*a);
        *r2 = (-b - delta)/(2*a);

        if (delta == 0) {
            return 1;
        }
        else {
            return 2;
        }
    }
}


/*FUNÇÃO INTERCEPTA*/
int intercepta(double x0, double y0, double x1, double y1, double *x, double *y) {
    double a, b, c;
    double intercept;
    double xr1, yr1, xr2, yr2;

    if (iguais(x0, x1)) {
        if(iguais(x1*x1, RAIO_AP*RAIO_AP)) {
            return 0;
        }
        else {
            *x = x0;
            *y = raiza(RAIO_AP*RAIO_AP - x0*x0, EPS);
            return 1;
        }
    }
    else {
        a = -1*((y1 - y0)/(x1 - x0));
        b = 1;
        c = -a*x0 - y0;

        intercept = raizeq(a, b, c, &xr1, &xr2);

        if(intercept == 0) {
            return 0;
        } 
        else {
            yr1 = a*xr1 + c;
            yr2 = a*xr2 + c;

            if(intercept == 1) {
                *x = xr1;
                *y = yr1;
            }
            else {
                if(dista(xr1, yr1, x1, y1) < dista(xr2, yr2, x1, y1)) {
                    *x = xr1;
                    *y = yr1;
                }
                else {
                    *x = xr2;
                    *y = yr2;
                }
            }
            return 1;
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


int main() {
    FILE *arq;
    char filename[256];
    int n_casos;
    int i_veiculo;
    double ant[6][6];
    double delta_t;
    int i = 0, j = 1;
    double x0, y0, x1, y1, speed, delta_s;

    printf("/// PROGRAMA DE MONITORAMENTO - CIDADE ODAIR ///\n\n");

    printf("Por favor, digite o nome do arquivo de entrada: ");
    scanf("%s", filename);
    printf("\n");

    arq = fopen(filename, "r");

    fscanf(arq, "%d", &n_casos);
    if(n_casos == 1) {
        printf("Há 1 caso para ser analisado hoje! \n");
    }
    else {
        printf("Há %d casos para serem analisados hoje! \n", n_casos);
    }

    while(n_casos != 0) {
        fscanf(arq, "%d", &i_veiculo);
        while(i != 3) {
            fscanf(arq, "%lf", &ant[i][0]);
            
            while(j != 5) {
                fscanf(arq, "%lf", &ant[i][j]);
                j++;
            }
            i++;
            j = 1;
        }

        fscanf(arq, "%lf", &delta_t);

        while(i != 6) {
            fscanf(arq, "%lf", &ant[i][0]);

            while(j != 5) {
                fscanf(arq, "%lf", &ant[i][j]);
                j++;
            }
            i++;
            j = 1;
        }
        i = 0;

        printf("  | VEÍCULO ANALISADO : %d |  \n", i_veiculo);
        printf("\n");

        printf("Antenas Posição Pŕevia: \n");
        while(i != 3) {
            ant[i][5] = ant[i][3]*(cossena(ant[i][4], EPS_COS));

            printf("|ANTENA %f|", ant[i][0]);
            printf("   Posição:.....(%.2f, %.2f)\n", ant[i][1], ant[i][2]);
            printf("   H(m):............. %.2f\n", ant[i][3]);
            printf("   Ângulo:........... %.2f\n", ant[i][4]);
            printf("   Distância:........ %.2f\n", ant[i][5]);
            printf("\n");

            i++;
        }

        localiza (ant[0][1], ant[0][2], ant[0][5], 
        ant[1][1], ant[1][2], ant[1][5], 
        ant[2][1], ant[2][2], ant [2][5], 
        &x0, &y0);

        printf("Localização Pŕevia:...... ( %.2f, %.2f )\n", x0, y0);
        printf("\n");

        printf("Intervalo de Tempo:...... %.2f", delta_t);
        printf("\n");

        printf("Antenas Posição Atual: \n");
        while(i != 6) {
            ant[i][5] = ant[i][3]*(cossena(ant[i][4], EPS_COS));

            printf("|ANTENA %.2f|", ant[i][0]);
            printf("   Posição:.....(%.2f, %.2f)\n", ant[i][1], ant[i][2]);
            printf("   H(m):............. %.2f\n", ant[i][3]);
            printf("   Ângulo:........... %.2f\n", ant[i][4]);
            printf("   Distância:........ %.2f\n", ant[i][5]);
            printf("\n");

            i++;
        }

        localiza (ant[3][1], ant[3][2], ant[3][5], 
        ant[4][1], ant[4][2], ant[4][5], 
        ant[5][1], ant[5][2], ant [5][5], 
        &x1, &y1);

        printf("Localização Atual:...... ( %.2f, %.2f )\n", x1, y1);
        printf("\n");

        speed = velocidade(x0, y0, x1, y1, delta_t);
        delta_s = speed*delta_t;

        printf("Distância Percorrida:... %.2f\n", delta_s);
        printf("Velocidade Média:....... %.2f\n", speed);
        printf("\n");
        printf("Distância da Origem:.... %.2f\n", dista(x1, y1, 0, 0));
        printf("\n");



        n_casos--;
        i = 0;
    }
    fclose(arq);
return 0;


}
