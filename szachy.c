#include <stdio.h>
#define size 8
#define WYGRANA 100000000
#define PRZEGRANA -10000000
int figury[13]={0,1,2,3,4,5,6,7,8,9,10,11,12};
 // 0-wolne, 1-krol, 2-krolowa, 3-goniec, 4-wieza, 5-kon, 6-pion   7-12-piony przeciwnika w tej samej kolejnosci


void wypisz(int plansza[size][size])
{
    printf("    0   1   2   3   4   5   6   7 \n  --------------------------------\n");
    for(int i=0;i<size;i++)
    {
        printf("%d ",i);
        for(int j=0;j<size;j++)
        {
        if(plansza[i][j]/10 < 1)
           printf("| %d ",plansza[i][j]);
        if(plansza[i][j]/10 == 1)
            printf("| %d",plansza[i][j]);
        }
    printf("|\n  --------------------------------\n");
    }
}
void swap(int plansza[Size][Size], int tx, int ty, int dx, int dy);
{
    int tymcz=plansza[tx][ty];
    int plansza[tx][ty]=plansza[dx][dy];
    int plansza[dx][dy]=tymcz;
}

int komputer(int plansza[size][size],char znak,int glebia)
{
    int px_pom,py_pom,_pom,o_pom,px,py,dx,dy,kierunek,odleg³oœæ;
    int wynik,wmax,wmin,ruch_fig,bita_fig;

    wynik==ocena(plansza);
    if(znak=='')
}

int main()
{
    int plansza[size][size]=
    {
        {4,5,3,1,2,3,5,4},
        {6,6,6,6,6,6,6,6},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {12,12,12,12,12,12,12,12},
        {10,11,9,7,8,9,11,10}
    };
    wypisz(plansza);
    int stan=0,int tx, int ty, int dx, int dy;;
    while(stan != WYGRANA && stan != PRZEGRANA)
    {
        do
        {
        printf("podaj pozycje pionka którego chcesz przesun¹c");
        scanf("%d %d",&tx,&ty);
        }while(plansza[tx][ty]==0 || x>=8 || x<0 || y>=8 || y<0)

        do
        {
        printf("podaj pozycje pionka którego chcesz przesun¹c");
        scanf("%d %d",&dx,&dy);
        }while(plansza[x][y]<7 || dx>=8 || dx<0 || dy>=8 || dy<0)

        swap(plansza,tx,ty,dx,dy);

        komputer(plansza,'k',4);

    }
    return 0;
}
