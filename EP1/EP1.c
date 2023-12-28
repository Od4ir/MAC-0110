#include <stdio.h>
#include <stdlib.h>
 
int main() {
int num, x, y, z, x1, y1, z1, w;
int op, dp;
int jog, tent, result; 

printf("\nBem vindx ao JOGO da FORCA numérica!\n");

/*op - opção, jog - jogos, dp - depuração, result - resultado, tent - tentativas*/
op = 1;
jog = dp = result = 0;

while(op != 3) { 
    /*Sendo num = xyz, determina-se os algarismos x, y e z: */
     num = rand() % 1000;
     z = num%10;
     num = num/10; 
     y = num%10;
     num = num/10; 
     x = num%10;
     
     printf("\n[ Depuração = ");
     if (dp == 0) {
         printf ("DESLIGADO");
        }
     else {
         printf ("LIGADO");
        } 
     printf(" / Jogos = %d ]\n", jog);
     printf("  1 . Continuar a jogar\n");
     printf("  2 . Alternar modo depuração e continuar a jogar\n");
     printf("  3 . Parar\n");
     printf(" Escolha uma opção: ");
     scanf("%d", &op);
     printf("\n");
     
     /*Alteração modo de depuração*/
     if (op == 2) {
         if (dp == 0) {
             dp = 1;
            }
         else {
             dp = 0;
            }
        }	
     tent = 6;
     x1 = y1 = z1 = 0;
     
     if (op != 3) {
         if (dp == 1) {
             printf("Número a ser adivinhado: %d %d %d\n", x, y, z);
            }
         while ((tent != 0)&&(x1 + y1 + z1 != 3)) {
             if (tent != 1) {
                 printf("Restam %d tentivas\n", tent);
                }
                else {
                    printf("Resta uma tentativa!\n");
                }
             printf("Sua próxima tentativa (Dígito de 0 a 9): ");
             scanf("%d", &w);
             printf("Você já acertou: ");
             /*verificação se o usuário acertou algum algarismo*/
             if ((w == x)||(x1 == 1)) {
                 printf("%d", x);
                 x1 = 1;
                }
             else {
                 printf("_");
                }
             if ((w == y)||(y1 == 1)) {
                 printf(" %d", y);
                 y1 = 1;
                }
             else {
                 printf(" _");
                }
             if ((w == z)||(z1 == 1)) {
                 printf(" %d\n", z);
                 printf("\n");
                 z1 = 1;
                }
             else {
                 printf(" _\n");
                 printf("\n");
                }
             tent = tent - 1;
             /*Se o usuário acertar todos, x1 = y1 = z1 = 1, logo: */
             if (x1 + y1 + z1 == 3) {
                 printf("\nVocê VENCEU!\n");
                 printf("\n");
                 jog++;
                 result++;
                 tent = 0;
                }
             else {
                 if (tent == 0) {
                     printf("\nVocê PERDEU!\n");
                     printf("\n");
                     jog++;
                     tent = 0;
                    }
                }
            }
        }
    }
printf("Você jogou %d jogos e venceu %d vezes!\n", jog, result);
printf("\n");
}
