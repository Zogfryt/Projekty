#include <stdio.h>
#include <stdlib.h>

struct el_drzewa{
    double w;
    struct el_drzewa *prawy;
    struct el_drzewa *lewy;
};

void wstaw(struct el_drzewa **pocz, double war)
{
    struct el_drzewa *nowy, *ws=*pocz, *nastepny;
    nowy=malloc(sizeof(struct el_drzewa));
    nowy->w=war;
    nowy->lewy=nowy->prawy=0;
    if(ws==0) *pocz=nowy;
    else{
        while(1)
        {
            if(war < ws->w)
            {
                if(ws->lewy==0)
                {
                    ws->lewy=nowy;
                    break;
                }
                else
                ws=ws->lewy;
            }
            else
            {
                if(ws->prawy==0)
                {
                    ws->prawy=nowy;
                    break;
                }
                else
                ws=ws->prawy;
            }
        }
    }
}

void wypisz(struct el_drzewa *pocz)
{
    if(pocz==0) return;
    wypisz(pocz->lewy);
    printf("%lf ",pocz->w);
    wypisz(pocz->prawy);
}

struct el_drzewa *szukana(struct el_drzewa *pocz,double war)       //rekurencyjny sposób
{
if(pocz==0 || pocz->w == war)
    return pocz;
if(war < pocz->w)
    return szukana (pocz->lewy,war);
return szukana (pocz->prawy,war);
};

struct el_drzewa *szukana_v2(struct el_drzewa *pocz, double war)     //szybszy odpowiednik iteracyjny;
{
    while(pocz !=0 && pocz->w != war)
        if(pocz->w < war)
        pocz=pocz->prawy;
        else
        pocz=pocz->lewy;
    return pocz;
};
int main()
{
    struct el_drzewa *ws=0,*szuk=0;
    double x,s;
    scanf("%lf",&x);
    wstaw(&ws,x);
    scanf("%lf",&x);
    wstaw(&ws,x);
    scanf("%lf",&x);
    wstaw(&ws,x);
    //wypisz(ws);
    scanf("%lf",&s);
    szuk=szukana(ws,s);
    if(szuk!=0)
    printf("\n%lf\n",szuk->w);
    return 0;
}
