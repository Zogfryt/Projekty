
#include <stdio.h>
#include <stdlib.h>
#define Size 3
#define WIN 1
#define NWIN -1
#define REMIS 0

void wypisz(char tab[Size][Size])
{
         for(int i=0; i<Size; i++)
         {
                  for(int j=0; j<Size; j++)
                  {
                           printf("%c ", tab[i][j]);
                  }
                  printf("\n");
         }
}


int ocen(char tab[Size][Size])
{
if(tab[0][0]=='x' && tab[0][1]=='x' && tab [0][2]=='x') return WIN;
if(tab[1][0]=='x' && tab[1][1]=='x' && tab [1][2]=='x') return WIN;
if(tab[2][0]=='x' && tab[2][1]=='x' && tab [2][2]=='x') return WIN;
if(tab[0][0]=='x' && tab[1][0]=='x' && tab [2][0]=='x') return WIN;
if(tab[0][1]=='x' && tab[1][1]=='x' && tab [2][1]=='x') return WIN;
if(tab[0][2]=='x' && tab[1][2]=='x' && tab [2][2]=='x') return WIN;
if(tab[0][0]=='x' && tab[1][1]=='x' && tab [2][2]=='x') return WIN;
if(tab[0][2]=='x' && tab[1][1]=='x' && tab [2][0]=='x') return WIN;

if(tab[0][0]=='o' && tab[0][1]=='o' && tab [0][2]=='o') return NWIN;
if(tab[1][0]=='o' && tab[1][1]=='o' && tab [1][2]=='o') return NWIN;
if(tab[2][0]=='o' && tab[2][1]=='o' && tab [2][2]=='o') return NWIN;
if(tab[0][0]=='o' && tab[1][0]=='o' && tab [2][0]=='o') return NWIN;
if(tab[0][1]=='o' && tab[1][1]=='o' && tab [2][1]=='o') return NWIN;
if(tab[0][2]=='o' && tab[1][2]=='o' && tab [2][2]=='o') return NWIN;
if(tab[0][0]=='o' && tab[1][1]=='o' && tab [2][2]=='o') return NWIN;
if(tab[0][2]=='o' && tab[1][1]=='o' && tab [2][0]=='o') return NWIN;

return REMIS;
}

int nx, ny;

int sprawdz_mozliwosci(char tab[Size][Size], char znak, int glebia)
{
         int ocena = ocen(tab), ile_zajetych_pol = 0;
         if(ocena != REMIS || glebia == 0) { return ocena; }

         int aocena, nopcja;
         if(znak == 'o') { nopcja = WIN + 1; }
         else { nopcja = NWIN - 1; }

         for(int i=0; i<Size; i++)
         {
                  for(int j=0; j<Size; j++)
                  {
                           if(tab[i][j] == ' ')
                           {
                                    tab[i][j] = znak;
                                    if(znak == 'x')
                                    {
                                             aocena = sprawdz_mozliwosci(tab, 'o', glebia - 1);
                                    }
                                    else if(znak == 'o')
                                    {
                                             aocena = sprawdz_mozliwosci(tab, 'x', glebia - 1);
                                    }
                                    tab[i][j] = ' ';
                                    if(znak == 'x' && aocena > nopcja)
                                    {
                                             nopcja = aocena;
                                             if(glebia == 6)
                                             {
                                                      nx = i;
                                                      ny = j;
                                             }
                                    }
                                    else if(znak == 'o' && aocena < nopcja)
                                    {
                                             nopcja = aocena;
                                    }
                           }
                           else { ++ile_zajetych_pol; }
                  }
         }
         if(ile_zajetych_pol > 8) { return ocena; }
         return nopcja;
}



int main()
{

    char tab[Size][Size] = {"   ", "   ", "   "};
    int x, y, stan = REMIS, zajete_pola = 0;
    while(stan == REMIS && zajete_pola < 9)
    {
             printf("Wpisz pozycje 'o':\n");
             scanf("%d %d", &x, &y);
             if(tab[x][y] == ' ')
             {
                      tab[x][y] = 'o';
             }
             else
             {
                      while(tab[x][y] != ' ')
                      {
                               printf("Jeszcze raz inna pozycja'o':\n");
                               scanf("%d %d", &x, &y);
                      }
                      tab[x][y]='o';
             }
             ++zajete_pola;
             sprawdz_mozliwosci(tab, 'x', 6);
             tab[nx][ny] = 'x';
             ++zajete_pola;
             wypisz(tab);
             stan = ocen(tab);
    }
    if(stan == WIN) { printf("Wygral: x"); }
    else if(stan == NWIN) { printf("Wygral: o"); }
    else { printf("REMIS"); }
    return 0;
}

