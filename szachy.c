#include <stdio.h>
#define size 8
#define WYGRANA 1800
#define PRZEGRANA -1800
#define PION 6
#define KON 5
#define WIEZA 4
#define GONIEC 3
#define KROLOWA 2
#define KROL 1
#define PUSTE 0
#define KROL_K 7
#define KROLOWA_K 8
#define GONIEC_K 9
#define WIEZA_K 10
#define KON_K 11
#define PION_K 12

int MAX_KIER[13]={0,8,8,4,4,8,3,8,8,4,4,8,3};
int MAX_RANGE[13]={0,2,8,8,8,2,2,2,8,8,8,2,2};
int oc[13]={0,WYGRANA,180,60,100,60,20,PRZEGRANA,-180,-60,-100,-60,-20};
int nx,ny,no,nk;

int WX[13][8]=
{
    {0,0,0,0,0,0,0,0},
    {-1,-1,-1,0,1,1,1,0},
    {-1,-1,-1,0,1,1,1,0},
    {-1,-1,1,1},
    {-1,0,1,0},
    {-1,-2,-2,-1,1,2,2,1},
    {-1,-1,-1},
    {-1,-1,-1,0,1,1,1,0},
    {-1,-1,-1,0,1,1,1,0},
    {-1,-1,1,1},
    {-1,0,1,0},
    {-1,-2,-2,-1,1,2,2,1},
    {1,1,1}
};

int WY[13][8]=
{
    {0,0,0,0,0,0,0,0},
    {-1,0,1,1,1,0,-1},
    {-1,0,1,1,1,0,-1},
    {-1,1,1,-1},
    {0,1,0,-1},
    {-2,-1,1,2,2,1,-1,-2},
    {-1,0,1},
    {-1,0,1,1,1,0,-1},
    {-1,0,1,1,1,0,-1},
    {-1,1,1,-1},
    {0,1,0,-1},
    {-2,-1,1,2,2,1,-1,-2},
    {1,0,-1}

};

int HEUR[13][size][size]={
{
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0}

},
{
    {-4,-2,-2,-1,-1,-2,-2,-4},
    {-2,0,0,0,0,0,0,-2},
    {-2,0,1,1,1,1,0,-2},
    {-1,0,1,1,1,1,0,-1},
    {0,0,1,1,1,1,0,-1},
    {-2,1,1,1,1,1,0,-2},
    {-2,0,1,0,0,0,0,-2},
    {-4,-2,-2,-1,-1,-2,-2,-4}

},
{
    {-6,-8,-8,-10,-10,-8,-8,-6},
    {-6,-8,-8,-10,-10,-8,-8,-6},
    {-6,-8,-8,-10,-10,-8,-8,-6},
    {-6,-8,-8,-10,-10,-8,-8,-6},
    {-4,-6,-6,-8,-8,-6,-6,-4},
    {-2,-4,-4,-4,-4,-4,-4,-2},
    {4,4,0,0,0,0,4,4},
    {4,6,2,0,0,2,4,6}
},
{
   {-4,-2,-2,-2,-2,-2,-2,-4},
   {-2,0,0,0,0,0,0,-2},
   {-2,0,1,2,2,1,0,-2},
   {-2,1,1,2,2,1,1,-2},
   {-2,0,2,2,2,2,0,-2},
   {-2,2,2,2,2,2,2,-2},
   {-2,1,0,0,0,0,1,-2},
   {-4,-2,-2,-2,-2,-2,-2,-4}
},
{
   {0,0,0,0,0,0,0,0},
   {1,2,2,2,2,2,2,1},
   {-1,0,0,0,0,0,0,-1},
   {-1,0,0,0,0,0,0,-1},
   {-1,0,0,0,0,0,0,-1},
   {-1,0,0,0,0,0,0,-1},
   {-1,0,0,0,0,0,0,-1},
   {0,0,0,1,1,0,0,0}
},
{
   {-10,-8,-6,-6,-6,-6,-8,-10},
   {-8,-4,0,0,0,0,-4,-8},
   {-6,0,2,3,3,2,0,-6},
   {-6,1,3,4,4,3,1,-6},
   {-6,0,3,4,4,3,0,-6},
   {-6,1,2,3,3,2,1,-6},
   {-8,-4,0,1,1,0,-4,-8},
   {-10,-8,-6,-6,-6,-6,-8,-10},
},
{
   {0,0,0,0,0,0,0,0},
   {10,10,10,10,10,10,10,10},
   {2,2,4,6,6,4,2,2},
   {1,1,2,5,5,2,1,1},
   {0,0,0,4,4,0,0,0},
   {1,-1,-2,0,0,-2,-1,1},
   {1,2,2,-4,-4,2,2,1},
   {0,0,0,0,0,0,0,0}
},
{
    {4,2,2,1,1,2,2,4},
    {2,0,-1,0,0,0,0,2},
    {2,-1,-1,-1,-1,-1,0,2},
    {0,0,-1,-1,-1,-1,0,1},
    {1,0,-1,-1,-1,-1,0,1},
    {2,0,-1,-1,-1,-1,0,2},
    {2,0,0,0,0,0,0,2},
    {4,2,2,1,1,2,2,4}
},
{
    {-4,-6,-2,0,0,-2,-4,-6},
    {-4,-4,0,0,0,0,-4,-4},
    {2,4,4,4,4,4,4,2},
    {4,6,6,8,8,6,6,4},
    {6,8,8,10,10,8,8,6},
    {6,8,8,10,10,8,8,6},
    {6,8,8,10,10,8,8,6},
    {6,8,8,10,10,8,8,6}
},
{
    {4,2,2,2,2,2,2,4},
    {2,-1,0,0,0,0,-1,2},
    {2,-2,-2,-2,-2,-2,-2,2},
    {2,0,-2,-2,-2,-2,0,2},
    {2,-1,-1,-2,-2,-1,-1,2},
    {2,0,-1,-2,-2,-1,0,2},
    {2,0,0,0,0,0,0,2},
    {4,2,2,2,2,2,2,4}
},
{
   {0,0,0,-1,-1,0,0,0},
   {1,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,1},
   {-1,-2,-2,-2,-2,-2,-2,-1},
   {0,0,0,0,0,0,0,0}
},
{
    {10,8,6,6,6,6,8,10},
    {8,4,0,-1,-1,0,4,8},
    {6,-1,-2,-3,-3,-2,-1,6},
    {6,0,-3,-4,-4,-3,0,6},
    {6,-1,-3,-4,-4,-3,-1,6},
    {6,0,-2,-3,-3,-2,0,6},
    {8,4,0,0,0,0,4,8},
    {10,8,6,6,6,6,8,10}
},
{
    {0,0,0,0,0,0,0,0},
    {-1,-2,-2,4,4,-2,-2,-1},
    {-1,1,2,0,0,2,1,-1},
    {0,0,0,-4,-4,0,0,0},
    {-1,-1,-2,-5,-5,-2,-1,-1},
    {-2,-2,-4,-6,-6,-4,-2,-2},
    {-10,-10,-10,-10,-10,-10,-10,-10},
    {0,0,0,0,0,0,0,0}
},};

void wypisz(int plansza[size][size])
{
    //system("cls");
    printf("    0   1   2   3   4   5   6   7 \n  --------------------------------\n");
    for(int i=0;i<size;i++)
    {
        printf("%d ",i);
        for(int j=0;j<size;j++)
        {
         if(plansza[i][j]==KROL)
            printf("| k ");
         if(plansza[i][j]==KROLOWA)
            printf("| h ");
         if(plansza[i][j]==KON)
            printf("| s ");
         if(plansza[i][j]==GONIEC)
            printf("| g ");
         if(plansza[i][j]==WIEZA)
            printf("| w ");
         if(plansza[i][j]==PION)
            printf("| p ");
         if(plansza[i][j]==KROL_K)
            printf("| K ");
         if(plansza[i][j]==KROLOWA_K)
            printf("| H ");
         if(plansza[i][j]==KON_K)
            printf("| S ");
         if(plansza[i][j]==GONIEC_K)
            printf("| G ");
         if(plansza[i][j]==WIEZA_K)
            printf("| W ");
         if(plansza[i][j]==PION_K)
            printf("| P ");
         if(plansza[i][j]==PUSTE)
            printf("|   ");

        }
    printf("|\n  --------------------------------\n");
    }
}
int ocena(int plansza[size][size])
{
    int w=0;
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        w-=(oc[plansza[i][j]] + HEUR[plansza[i][j]][i][j]);
    return w;

}
int komputer(int plansza[size][size],char znak,int glebia)
{
    int dx,dy,kierunek,odleglosc;
    int wynik,wmax,wmin,ruch_fig,bita_fig;

    wynik=ocena(plansza);
    if( glebia == 0 || wynik > WYGRANA || wynik < PRZEGRANA) {return wynik;}

    if(znak == 'k')
    {
        wypisz(plansza);
        wmax=100*PRZEGRANA;
        for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            if(plansza[i][j]>6 && plansza[i][j]<13)
                for(kierunek =0; kierunek< MAX_KIER[plansza[i][j]];kierunek++)
                    for(odleglosc = 1; odleglosc <MAX_RANGE[plansza[i][j]]; odleglosc++)
                    {
                        dx=(odleglosc -1)*WX[plansza[i][j]][kierunek];
                        dy=(odleglosc -1)*WY[plansza[i][j]][kierunek];
                        if( odleglosc >=2 && plansza[i+dx][j+dy] != PUSTE)
                            break;
                        dx=odleglosc*WX[plansza[i][j]][kierunek];
                        dy=odleglosc*WY[plansza[i][j]][kierunek];
                        if(i+dx < 8 && i+dx >=0 && j+dy >=0 && j+dy < 8)
                            if(plansza[i+dx][j+dy] <= 6)
                            if(plansza[i][j]!=12 || (plansza[i+dx][j+dy] == PUSTE && dy ==0) || (plansza[i+dx][j+dy] != PUSTE && dy !=0))
                            {
                                if(plansza[i][j]==12 && i==1 && plansza[i+1][j]==PUSTE && dy==0)
                                {

                                    for(int z=1;z<=2;z++)
                                    {
                                    ruch_fig = plansza[i][j];
                                    bita_fig = plansza[i+z][j+dy];
                                    plansza[i+z][j+dy] = plansza[i][j];
                                    plansza[i][j]=PUSTE;
                                    wynik=komputer(plansza,'g',glebia -1);
                                    plansza[i+z][j+dy]=bita_fig;
                                    plansza[i][j]=ruch_fig;
                                    if(wynik > wmax)
                                    {
                                        wmax=wynik;
                                        if(glebia == 4)
                                        {
                                        printf("%d\n",wmax);
                                        nx = i;
                                        ny = j;
                                        nk = kierunek;
                                        no = odleglosc;
                                        }

                                    }
                                    }
                                }else{
                                 ruch_fig = plansza[i][j];
                                    bita_fig = plansza[i+dx][j+dy];
                                    plansza[i+dx][j+dy] = plansza[i][j];
                                    plansza[i][j]=PUSTE;
                                    if(plansza[i+dx][j+dy] == 12 && i+dx == 7)
                                       plansza[i+dx][j+dy]=KROLOWA_K;
                                    wynik=komputer(plansza,'g',glebia -1);
                                    plansza[i+dx][j+dy]=bita_fig;
                                    plansza[i][j]=ruch_fig;
                                    if(wynik > wmax)
                                    {
                                        wmax=wynik;
                                        if(glebia == 4)
                                        {
                                        printf("%d\n",wmax);
                                        nx = i;
                                        ny = j;
                                        nk = kierunek;
                                        no = odleglosc;
                                        }

                                    }
                                }
                          }
                    }
                    return wmax;
    }
    else
    {
        wmin=100*WYGRANA;
        for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            if(plansza[i][j]>0 && plansza[i][j]<7)
                for(kierunek =0; kierunek< MAX_KIER[plansza[i][j]];kierunek++)
                    for(odleglosc = 1; odleglosc <MAX_RANGE[plansza[i][j]]; odleglosc++)
                    {
                        dx=(odleglosc -1)*WX[plansza[i][j]][kierunek];
                        dy=(odleglosc -1)*WY[plansza[i][j]][kierunek];
                        if( odleglosc >=2 && plansza[i+dx][j+dy] != PUSTE)
                            break;
                        dx=odleglosc*WX[plansza[i][j]][kierunek];
                        dy=odleglosc*WY[plansza[i][j]][kierunek];
                        if(i+dx < 8 && i+dx >=0 && j+dy >=0 && j+dy < 8)
                            if(plansza[i+dx][j+dy]==0 || plansza[i+dx][j+dy] >=7)
                            if(plansza[i][j]!=6 || (plansza[i+dx][j+dy] == PUSTE && dy ==0) || (plansza[i+dx][j+dy] != PUSTE && dy !=0))
                            {
                                if(plansza[i][j]==6 && plansza[i-1][j]==PUSTE && dy==0 && i==6)
                                {
                                    for(int z=1;z<=2;z++)
                                    {
                                ruch_fig = plansza[i][j];
                                bita_fig = plansza[i-z][j+dy];
                                plansza[i-z][j+dy] = plansza[i][j];
                                plansza[i][j]=PUSTE;
                                wynik=komputer(plansza,'k',glebia -1);
                                plansza[i-z][j+dy]=bita_fig;
                                plansza[i][j]=ruch_fig;
                                if(wynik < wmin)
                                    wmin=wynik;
                                    }
                                }

                            else{
                                ruch_fig = plansza[i][j];
                                bita_fig = plansza[i+dx][j+dy];
                                plansza[i+dx][j+dy] = plansza[i][j];
                                plansza[i][j]=PUSTE;
                                if(plansza[i+dx][j+dy] == 6 && i+dx == 0)
                                    plansza[i+dx][j+dy]=KROLOWA;
                                wynik=komputer(plansza,'k',glebia -1);
                                plansza[i+dx][j+dy]=bita_fig;
                                plansza[i][j]=ruch_fig;
                                if(wynik < wmin)
                                    wmin=wynik;
                                }

                             }
                    }
    return wmin;
     }
}

int main()
{
    int plansza[size][size]=
    {
        {10,11,9,7,8,9,11,10},
        {12,12,12,12,12,12,12,12},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {6,6,6,6,6,6,6,6},
        {4,5,3,1,2,3,5,4}
    };
    printf("%d\n",ocena(plansza));
    wypisz(plansza);
    int stan=0,tx,ty,dx,dy;
    while(1)
    {
        do
        {
        printf("podaj pozycje pionka ktorego chcesz przesunac\n");
        scanf("%d %d",&tx,&ty);
        }while(plansza[tx][ty]==0 || tx>=8 || tx<0 || ty>=8 || ty<0);

        do
        {
        printf("podaj pozycje pionka na ktora chcesz przesunac\n");
        scanf("%d %d",&dx,&dy);
        }while((plansza[dx][dy]<7 && plansza[dx][dy] != 0) || dx>=8 || dx<0 || dy>=8 || dy<0);
        plansza[dx][dy]=plansza[tx][ty];
        plansza[tx][ty]=PUSTE;
        if(plansza[dx][dy]==6 && dx == 0)
        plansza[dx][dy]=KROLOWA;
        stan=komputer(plansza,'k',4);
        if(stan>WYGRANA || stan < PRZEGRANA)
            break;
        plansza[nx+no*WX[plansza[nx][ny]][nk]][ny+no*WY[plansza[nx][ny]][nk]]=plansza[nx][ny];
        //printf("%d %d %d %d\n",nx,ny,nk,no);
        plansza[nx][ny]=PUSTE;
        stan=komputer(plansza,'g',2);
        if(stan>WYGRANA || stan < PRZEGRANA)
            break;
        system("cls");
        wypisz(plansza);
    }
    wypisz(plansza);
    if(stan > WYGRANA)
        printf("AI WON!!");
    else if(stan < PRZEGRANA)
        printf("YOU WON!!");
    else
    printf("nie dziala");
    return 0;
}
