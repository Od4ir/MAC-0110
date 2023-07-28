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
int localiza ( double xi, double yi, double div1, double xj, double yj, double djv, double xk, double yk, double dkv,double *xv, double *yv) {
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
        }
        
        *yv = (c - a)/(b - d);
        *xv = a + b*(*yv);
    }
    return 1;
}

int main() {
    double xi, yi, div1;
    double Hi, thetai;
    double xj, yj, djv;
    double Hj, thetaj;
    double xk, yk, dkv;
    double Hk, thetak;
    double xv, yv;
    int local;
    
    printf("Coordenadas Antena 1: \n");
    scanf("%lf", &xi);
    scanf("%lf", &yi);
    scanf("%lf", &Hi);
    scanf("%lf", &thetai);
    
    div1 = raiza((Hi*Hi*pot(cossena(thetai, EPS_COS),2)), EPS);
    
    printf("%lf\n", div1);
    
    printf("Coordenadas Antena 2: \n");
    scanf("%lf", &xj);
    scanf("%lf", &yj);
    scanf("%lf", &Hj);
    scanf("%lf", &thetaj);
    
    djv = raiza((Hj*Hj*pot(cossena(thetaj, EPS_COS),2)), EPS);
    
    printf("%lf\n", djv);
    
    printf("Coordenadas Antena 3: \n");
    scanf("%lf", &xk);
    scanf("%lf", &yk);
    scanf("%lf", &Hk);
    scanf("%lf", &thetak);
    
    dkv = raiza((Hk*Hk*pot(cossena(thetak, EPS_COS),2)), EPS);
    
    printf("%lf\n", dkv);
    
    local = localiza(xi, yi, div1, xj, yj, djv, 
    xk, yk, dkv, &xv, &yv);
    printf("Local: %d\n", local);
    
    printf("XV: %lf\n", xv);
    printf("YV: %lf\n", yv);

    double angle, result, theta;
    int ok;
    
    scanf("%lf", &angle);
    result = cossena(angle, EPS_COS);
    printf("Função cossena: %.3lf\n", result);
    
    angle = (angle*PI)/180;
    theta = cos(angle);
    
    printf("Angle em radianos: %.3lf\n", angle);
    printf("Função cos: %.3lf\n", theta);
    
    ok = iguais(result, theta);
    printf("%d", ok);
    return 0;
}
