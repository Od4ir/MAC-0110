#include <stdio.h>
#define PI 3.14159
#define RAIO_AP 200
#define RAIO_ZA 2000 
#define DELTA_ALARME 60
#define EPS_COS 0.000001 
#define EPS 0.01

//FUNÇÃO POTENCIAÇÃO//
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
    if(x-y < EPS && y-x < EPS) {
        return 1;
    }
    else {
        return 0;
    }
}

//FUNÇÃO RAIZ QUADRADA//
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

//FUNÇÃO COSSENO//
double cossena (double theta, double epsilon) {
    double cosx = 1;
    theta = (theta*PI)/180;
    int k = 1, fat = 2;
    
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

//FUNÇÃO LOCALIZAÇÃO//
int localiza ( double xi, double yi, double div1, 
double xj, double yj, double djv, 
double xk, double yk, double dkv,
double *xv, double *yv) {
    double x_ok, y_ok, d_ok;
    double a, b, c, d;

    if ((xi == xj)&&(xi == xk)){
        return 0;
    }
    else {
        if ((xi != xj)&&(xi != xk)){
            x_ok = xi;
            y_ok = yi;
            d_ok = div1;
        }
        else {
            if (xi == xj) {
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
        
        if((b - d) == 0) {
            return 0;
        }
        else {
            *yv = (c - a)/(b - d);
            *xv = a + b*(*yv);
            
            return 1;
        }
    }
}

//FUNÇÃO VELOCIDADE//
double velocidade(double x0, double y0, double x1, double y1, double deltaT) {
    double v_media = 0;
    double vx, vy;

    vx = (x0 - x1)/deltaT;
    vy = (y0 - y1)/deltaT;

    v_media = raiza((vx*vx + vy*vy), EPS);
    
    return v_media;
}

//FUNÇÃO DISTÃNCIA 2 PONTOS//
double dista(x1, y1, x2, y2) {
    double dista = raiza(((x1*x1 - x2*x2)-(y1*y1 - y2*y2)), EPS);
    return dista;

}

int main() {
    FILE *arq;
    char nomearquivo[256];
    int n_casos;
    int i_veiculo, ant[6][5];
    int deltat;
    int i = 0, j = 1;

    printf("/// PROGRAMA DE MONITORAMENTO - CIDADE ODAIR ///\n")

    printf("Por favor, digite o nome do arquivo de entrada: ");
    scanf("%s", nomearquivo);
    printf("\n");

    arq = fopen( "nomearquivo.txt", "r" );

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
            fscanf(arq, "%d", &ant[i][0]);

            while(j != 5) {
                fscanf(arq, "%lf", &ant[i][j]);
                j++;
            }
            i++;
            j = 1;
        }

        fscanf(arq, "%lf", &deltat);

        while(i != 6) {
            fscanf(arq, "%d", &ant[i][0]);

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

        while(i =! 3) {
            printf("|ANTENA %lf|", antena[i][0]);
            printf("   Posição:.....(%lf, %lf)\n", ant[i][1], ant[i][2]);
            printf("   H(m):............. %lf\n", ant[i][3]);
            printf("   Ângulo:........... %lf\n", ant[i][4]);
            printf("   Distância:........ %lf\n", (ant[i][3]*cossena(ant[i][4], EPS_COS)));
            printf("\n");
            i++;
        }


        























        n_casos--;
    }


}