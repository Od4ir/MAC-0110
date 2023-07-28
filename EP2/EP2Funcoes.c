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
    if(x-y < EPS && y-x < EPS) {
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

/*FUNÇÃO COSSENO*/
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

/*FUNÇÃO LOCALIZAÇÃO*/
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

/*FUNÇÃO RAIZ DE EQUAÇÃO 2º GRAU*/
int raizeq(double a, double b, double c, double *r1, double *r2) {
    double delta;
    delta = b*b - 4*(a*c);

    if (delta < 0) {
        return 0;
    }
    else {
        delta = raiza(delta, EPS);
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


//FUNÇÃO INTERCEPTA//
int intercepta(double x0, double y0, double x1, double y1, double *x, double *y) {
    double a, b, c;
    double intercept;
    double xr1, yr1, xr2, yr2;

    if(x0 == x1) {
        b = 0;
        a = 1;
        c = -x1;
    }
    else {
        a = -1*((y1 - y0)/(x1 - x0));
        b = 1;
        c = a*x0 - y0;

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
                return 1;
            }
            else {
                if(dista(xr1, yr1, x1, y1) < dista(xr2, yr2, x1, raiz1)) {
                    *x = xr1;
                    *y = yr1;
                }
                else {
                    *x = xr2;
                    *y = yr2;
                }
            }
        }
    }
}
