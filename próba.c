
#include <stdio.h>
#include <stdlib.h>
#define W_PLANSZY 10
#define WYGRANA 1
#define PRZEGRANA -1
#define NIKT_NIE_WYGRAL 0

void wypisz(char plansza[W_PLANSZY][W_PLANSZY])
{
    printf(" 0 1 2 3 4 5 6 7 8 9\n");
         for(int i=0; i<W_PLANSZY; i++)
         {
             printf("%d",i);
                  for(int j=0; j<W_PLANSZY; j++)
                  {
                           printf("%c ", plansza[i][j]);
                  }
                  printf("\n");
         }
}

int kto_wygral(char wygrany)
{
         if(wygrany == 'x') { return WYGRANA; }
         else if(wygrany == 'o'){ return PRZEGRANA; }
         return NIKT_NIE_WYGRAL;
}

int ocen(char plansza[W_PLANSZY][W_PLANSZY])
{
    int l=0;
    char symbol_gracza='x';
         if(symbol_gracza=='x')
         for(int i=0;i<W_PLANSZY;i++)
            for(int j=0;j<W_PLANSZY;j++)
            {
                if(plansza[i][j]=='x')
                {
                    l=1;
                    for(int z=1;z<5;z++) //ukos w dó³-lewo
                    {
                        if(plansza[i+z][j+z]!='x' || i+z >= W_PLANSZY || j+z >= W_PLANSZY)
                        break;
                        l++;
                    }

                    if(l==5)
                    return WYGRANA;
                    else l=1;

                    for(int z=1;z<5;z++) //ukos w dó³-prawo
                    {
                        if(plansza[i+z][j-z]!='x' || i+z >= W_PLANSZY || j-z < 0)
                        break;
                        l++;
                    }
                    if(l==5)
                    return WYGRANA;
                    else l=1;


                    for(int z=1;z<5;z++) //dó³
                    {
                        if(plansza[i-z][j]!='x' || i-z < 0)
                        break;
                        l++;
                    }

                    if(l==5)
                    return WYGRANA;
                    else l=1;


                    for(int z=1;z<5;z++) //prawo
                    {
                        if(plansza[i][j+z]!='x' || j+z >= W_PLANSZY)
                        break;
                        l++;
                    }

                    if(l==5)
                    return WYGRANA;
                }

            }

         symbol_gracza='o';
         if(symbol_gracza=='o')
         for(int i=0;i<W_PLANSZY;i++)
            for(int j=0;j<W_PLANSZY;j++)
            {
                if(plansza[i][j]=='o')
                {
                    l=1;
                    for(int z=1;z<5;z++) //ukos w dó³-lewo
                    {
                        if(plansza[i+z][j+z]!='o' || i+z >= W_PLANSZY || j+z >= W_PLANSZY)
                        break;
                        l++;
                    }
                    if(l==5)
                    return PRZEGRANA;
                    else l=1;

                    for(int z=1;z<5;z++) //ukos w dó³-prawo
                    {
                        if(plansza[i+z][j-z]!='o' || i+z >= W_PLANSZY || j-z < 0)
                        break;
                        l++;
                    }

                    if(l==5)
                    return PRZEGRANA;
                    else l=1;


                    for(int z=1;z<5;z++) //dó³
                    {
                        if(plansza[i-z][j]!='o' || i-z < 0)
                        break;
                        l++;
                    }

                    if(l==5)
                    return PRZEGRANA;
                    else l=1;


                    for(int z=1;z<5;z++) //prawo
                    {
                        if(plansza[i][j+z]!='o' || j+z >= W_PLANSZY)
                        break;
                        l++;
                    }

                    if(l==5)
                    return PRZEGRANA;
                }

            }
            return NIKT_NIE_WYGRAL;



}

int naj_wiersz, naj_kolumna;

int blisko(char plansza[W_PLANSZY][W_PLANSZY], int i, int j)
{
    if(plansza[i][j+1]!=' ' && j+1 < W_PLANSZY)
        return 1;
    if(plansza[i+1][j]!=' ' && i+1 < W_PLANSZY)
        return 1;
    if(plansza[i][j-1]!=' ' && j-1 >= 0)
        return 1;
    if(plansza[i-1][j]!=' ' && i-1 >= 0)
        return 1;
    if(plansza[i+1][j+1]!=' ' && j+1 < W_PLANSZY && i+1 < W_PLANSZY)
        return 1;
    if(plansza[i-1][j+1]!=' ' && j+1 < W_PLANSZY && i-1 >= 0)
        return 1;
    if(plansza[i-1][j-1]!=' ' && j-1 >= 0 && i-1 >= 0)
        return 1;
    if(plansza[i+1][j-1]!=' ' && i+1 < W_PLANSZY && j-1 >= 0)
        return 1;
    return 0;

}

int sprawdz_mozliwosci(char plansza[W_PLANSZY][W_PLANSZY], char symbol_gracza, int glebia)
{
         int ocena_wygranej = ocen(plansza), ile_zajetych_pol = 0;
         if(ocena_wygranej != NIKT_NIE_WYGRAL || glebia == 0) { return ocena_wygranej; }

         int aktualna_ocena, najlepsza_opcja;
         if(symbol_gracza == 'o') { najlepsza_opcja = WYGRANA + 1; }
         else { najlepsza_opcja = PRZEGRANA - 1; }

         for(int i=0; i<W_PLANSZY; i++)
         {
                  for(int j=0; j<W_PLANSZY; j++)
                  {
                           if(plansza[i][j] == ' ' && blisko(plansza,i,j))
                           {
                                    plansza[i][j] = symbol_gracza;

                                    if(symbol_gracza == 'x')
                                    {
                                             aktualna_ocena = sprawdz_mozliwosci(plansza, 'o', glebia - 1);

                                    }
                                    else if(symbol_gracza == 'o')
                                    {
                                             aktualna_ocena = sprawdz_mozliwosci(plansza, 'x', glebia - 1);

                                    }
                                    plansza[i][j] = ' ';
                                    if(symbol_gracza == 'x' && aktualna_ocena > najlepsza_opcja)
                                    {
                                             najlepsza_opcja = aktualna_ocena;
                                             if(glebia == 4)
                                             {
                                                      naj_wiersz = i;
                                                      naj_kolumna = j;
                                             }
                                    }
                                    else if(symbol_gracza == 'o' && aktualna_ocena < najlepsza_opcja)
                                    {
                                             najlepsza_opcja = aktualna_ocena;
                                    }
                           }
                           if(plansza[i][j]!=' ') { ++ile_zajetych_pol; }
                  }
         }
         if(ile_zajetych_pol > 99) { return ocena_wygranej; }
       //  printf("%c%d: %d\n",symbol_gracza,glebia,najlepsza_opcja);
         return najlepsza_opcja;
}

void wyczysc(char plansza[W_PLANSZY][W_PLANSZY])
{
         for(int i=0; i<W_PLANSZY; i++)
         {
                  for(int j=0; j<W_PLANSZY; j++)
                  {
                           plansza[i][j] = ' ';
                  }
         }
}

int main()
{
    //printf("wygrany w x i o: %d\n", ocen(plansza));
    //sprawdz_mozliwosci(plansza, 'x');
    //printf("naj opcja: %d\n",najlepsza_opcja);
    char plansza[W_PLANSZY][W_PLANSZY] = {"          ","          ", "          ","          ","          ","          ","          ","          ","          ","          "};
    wyczysc(plansza);
    int wiersz, kolumna, stan_gry = NIKT_NIE_WYGRAL, zajete_pola = 0;
    while(stan_gry == NIKT_NIE_WYGRAL && zajete_pola < 100)
    {
             printf("Wpisz w ktorym wierszu i kolumnie chcesz postawic 'o':\n");
             scanf("%d %d", &wiersz, &kolumna);
             if(plansza[wiersz][kolumna] == ' ')
             {
                      plansza[wiersz][kolumna] = 'o';
             }
             else
             {
                      while(plansza[wiersz][kolumna] != ' ')
                      {
                               printf("Wpisz w ktorym pustym wierszu i pustej kolumnie chcesz postawic 'o':\n");
                               scanf("%d %d", &wiersz, &kolumna);
                      }
             }
             ++zajete_pola;
             sprawdz_mozliwosci(plansza, 'x', 4);
             plansza[naj_wiersz][naj_kolumna] = 'x';
             ++zajete_pola;
             wypisz(plansza);
             stan_gry = ocen(plansza);
    }
    if(stan_gry == PRZEGRANA) { printf("KONIEC GRY WYGRAL: o"); }
    else if(stan_gry == WYGRANA) { printf("KONIEC GRY WYGRALO: x"); }
    else { printf("KONIEC GRY REMIS"); }
    return 0;
}
