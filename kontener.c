#include <stdio.h>
#include <stdlib.h>

struct el_listy
{
    double w;
    struct el_listy *nast;
};

void dopisz(struct el_listy **pocz, double war)
{
    struct el_listy *nowy, *ww=*pocz;
    nowy=malloc(sizeof(struct el_listy));
    nowy->w=war;
    nowy->nast=0;
    if(ww==0) *pocz=nowy;
    else{
        while (ww->nast) ww=ww->nast;
        ww->nast=nowy;
    }
}

void wypisz(struct el_listy *pocz)
{
    while(pocz){
        printf("%lf ",pocz->w);
        pocz=pocz->nast;
    }
    printf("\n");
}

void wstaw(struct el_listy **pocz, double war)
{
    struct el_listy *nowy, *ww=*pocz;
    nowy=malloc(sizeof(struct el_listy));
    nowy->w=war;
    if(ww==0 || war < ww->w)
    {
        nowy->nast = ww;
        *pocz=nowy;
    }else{
    while(ww->nast!=0 && war > ww->nast->w) ww=ww->nast;
    nowy->nast=ww->nast;
    ww->nast=nowy;
    }
}

void usun_element(struct el_listy **pocz, double war)
{
    struct el_listy *pom, *ww=*pocz;
    if(ww==0) return;
    if(war == ww->w)
    {
        pom=ww;
        *pocz=ww->nast;
        free(pom);
    }else{
    while (ww->nast!=0 && war != ww->nast->w) ww=ww->nast;
    if(ww->nast!=0 && war == ww->nast->w){
        pom=ww->nast;
        ww->nast = ww->nast->nast;
        free(pom);
    }
    }
}

struct el_listy *kopiuj_liste(struct el_listy *pocz)
{
    struct el_listy *nowy, *poprzedni, *lista2=0;
    while(pocz){
        nowy=malloc(sizeof(struct el_listy));
        nowy->w=pocz->w;
        if(lista2==0) lista2=nowy;
        else poprzedni->nast=nowy;
        poprzedni=nowy;
        pocz=pocz->nast;
    }
    if(lista2) nowy->nast =0;
    return lista2;
    }

    struct el_listy *dodaj_listy(struct el_listy *pocz1, struct el_listy *pocz2)
    {
     struct el_listy *kop1, *kop2, *pom;
     kop1 = kopiuj_liste(pocz1);
     kop2 = kopiuj_liste(pocz2);
     if(kop1==0) return kop2;
     pom=kop1;
     while(pom->nast) pom = pom->nast;
     pom->nast = kop2;
     return kop1;
    }

    void szukaj(struct el_listy *pocz, double war)
    {
        int i=0;
        if(pocz==0){
            printf("pusta tablica, nic nie znajdziesz\n");
            return;
        }
        while(pocz)
        {
            if(war==pocz->w)
                printf("znajduje si� na miejscu %d \n",i);
            pocz=pocz->nast;
        }
    }

    struct el_listy *szukana(struct el_listy *pocz, double szukana)
    {
        while(pocz!=0 && szukana != pocz->w)
            pocz=pocz->nast;
        return pocz;
    };
int main()
{
    double x,s=5;
    struct el_listy *ws=0,*ws1=0,*suma=0;
    scanf("%lf",&x);
    wstaw(&ws,x);
    scanf("%lf",&x);
    wstaw(&ws,x);
    scanf("%lf",&x);
    wstaw(&ws,x);
    scanf("%lf",&s);
    wypisz(ws);
    if(suma!=0)
    printf("%lf",suma->w);
    return 0;
}
