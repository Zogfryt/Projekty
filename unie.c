#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <limits.h>
#include <string.h>

union unia
{
    int a;
    double b;
    char c[120];
}unia1;

struct struktura{
double b;
char c[120];
int a;
}struktura1;
int main()
{
    setlocale(LC_ALL,"");
    unia1.a=20;
    unia1.b=4.5;
    strcpy(unia1.c,"let's goooooooooo!!!");
    printf("%d %lf %s\n\n",unia1.a,unia1.b,unia1.c);

    strcpy(unia1.c,"let's goooooooooo!!!");
    unia1.a=20;
    unia1.b=4.5;
    printf("%d %lf %s\n\n",unia1.a,unia1.b,unia1.c);


    unia1.b=4.5;
    strcpy(unia1.c,"let's goooooooooo!!!");
    unia1.a=20;
    printf("%d %lf %s\n\n",unia1.a,unia1.b,unia1.c);
    printf("%d %d\n",sizeof(struktura1), sizeof(unia1));
    printf("struktura zajmuje nieco wiêcej ni¿ powinna przez zjawisko struct pudding");

}
