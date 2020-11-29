
#include <stdio.h>
#include <stdlib.h>
#define Size 10
#define WIN 2000000000
#define NWIN -2000000000
#define REMIS 0

void wypisz(char tab[Size][Size])
{
    printf("   0   1   2   3   4   5   6   7   8   9\n");
         for(int i=0; i<Size; i++)
         {
             printf("------------------------------------------\n%d",i);
                  for(int j=0; j<Size; j++)
                  {
                           printf("| %c ", tab[i][j]);
                  }
                  printf("\n");
         }
         printf("\n");
}

int ocen(char tab[Size][Size])
{
    int l=0;
    int lmin[3]={0,0,0};
    char symbol_gracza='x';
         if(symbol_gracza=='x')
         for(int i=0;i<Size;i++)
            for(int j=0;j<Size;j++)
            {
                if(tab[i][j]=='x')
                {
                    l=1;
                    if(i<6 && j<6)
                    {
                    for(int z=1;z<5;z++) //ukos w dó³-lewo
                    {
                        if(tab[i+z][j+z]!='x')
                        break;
                        l++;
                    }

                    if(l==5)
                    return WIN;
                    else l=1;
                    }

                    if(i<6 && j>3){
                    for(int z=1;z<5;z++) //ukos w dó³-prawo
                    {
                        if(tab[i+z][j-z]!='x')
                        break;
                        l++;
                    }
                    if(l==5)
                    return WIN;
                    else l=1;
                    }

                    if(i<6){
                    for(int z=1;z<5;z++) //dó³
                    {
                        if(tab[i+z][j]!='x')
                        break;
                        l++;
                    }

                    if(l==5)
                    return WIN;
                    else l=1;
                    }

                    if(j<6){
                    for(int z=1;z<5;z++) //prawo
                    {
                        if(tab[i][j+z]!='x')
                        break;
                        l++;
                    }

                    if(l==5)
                    return WIN;
                    }
                }

            }

         symbol_gracza='o';
         if(symbol_gracza=='o')
         for(int i=0;i<Size;i++)
            for(int j=0;j<Size;j++)
            {
                if(tab[i][j]=='o')
                {
                    l=1;
                    for(int z=1;z<5;z++) //ukos w dó³-lewo
                    {
                        if(tab[i+z][j+z]!='o')
                        break;
                        l++;
                    }
                    if(l==5)
                    return NWIN;
                    else if (l>=2)
                        lmin[l-2]++;
                    l=1;



                    for(int z=1;z<5;z++) //ukos w dó³-prawo
                    {
                        if(tab[i+z][j-z]!='o')
                        break;
                        l++;
                    }

                    if(l==5)
                    return NWIN;
                    else if (l>=2)
                    lmin[l-2]++;
                    l=1;

                    for(int z=1;z<5;z++) //dó³
                    {
                        if(tab[i+z][j]!='o')
                        break;
                        l++;
                    }

                    if(l==5)
                    return NWIN;
                    else if (l>=2)
                        lmin[l-2]++;
                    l=1;

                    for(int z=1;z<5;z++) //prawo
                    {
                        if(tab[i][j+z]!='o')
                        break;
                        l++;
                    }

                    if(l==5)
                    return NWIN;
                    else if (l>=2)
                    lmin[l-2]++;
                    l=1;
                }

            }
            return -1*(lmin[0]+100*lmin[1]+10000*lmin[2]);



}

int nx, ny;

int blisko(char tab[Size][Size], int i, int j)
{
    if(tab[i][j+1]!=' ' && j+1 < Size)
        return 1;
    if(tab[i+1][j]!=' ' && i+1 < Size)
        return 1;
    if(tab[i][j-1]!=' ' && j-1 >= 0)
        return 1;
    if(tab[i-1][j]!=' ' && i-1 >= 0)
        return 1;
    if(tab[i+1][j+1]!=' ' && j+1 < Size && i+1 < Size)
        return 1;
    if(tab[i-1][j+1]!=' ' && j+1 < Size && i-1 >= 0)
        return 1;
    if(tab[i-1][j-1]!=' ' && j-1 >= 0 && i-1 >= 0)
        return 1;
    if(tab[i+1][j-1]!=' ' && i+1 < Size && j-1 >= 0)
        return 1;
    return 0;

}

int sprawdz_mozliwosci(char tab[Size][Size], char znak, int glebia)
{
         int ocena = ocen(tab), ile_zajetych_pol = 0;
         if(ocena == NWIN || ocena == WIN ||  glebia == 0) { return ocena; }

         int aocena, nopcja;
         if(znak == 'o') { nopcja = WIN + 1000; }
         else { nopcja = NWIN - 1000; }

         for(int i=0; i<Size; i++)
         {
                  for(int j=0; j<Size; j++)
                  {
                           if(tab[i][j] == ' ' && blisko(tab,i,j))
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
                                             if(glebia == 4)
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
                           if(tab[i][j]!=' ') { ++ile_zajetych_pol; }
                  }
         }
         if(ile_zajetych_pol > 99) { return ocena; }
         return nopcja;
}

void wyczysc(char tab[Size][Size])
{
         for(int i=0; i<Size; i++)
         {
                  for(int j=0; j<Size; j++)
                  {
                           tab[i][j] = ' ';
                  }
         }
}

int main()
{
    char tab[Size][Size];
    wyczysc(tab);
    int x, y, stan = REMIS, zajete_pola = 0;
    while(stan != WIN && stan != NWIN && zajete_pola < 100)
    {
             printf("Podaj kolumne i wiersz dla 'o':\n");
             scanf("%d %d", &x, &y);
             if(tab[x][y] == ' ')
             {
                      tab[x][y] = 'o';
             }
             else
             {
                      while(tab[x][y] != ' ')
                      {
                               printf("Podaj jeszcze raz kolumne i wiersz dla 'o':\n");
                               scanf("%d %d", &x, &y);
                      }
                      tab[x][y] = 'o';
             }
             ++zajete_pola;
             sprawdz_mozliwosci(tab, 'x', 4);
             tab[nx][ny] = 'x';
             ++zajete_pola;
             wypisz(tab);
             stan = ocen(tab);
    }
    if(stan == NWIN) { printf("WYGRAL: o"); }
    else if(stan == WIN) { printf("WYGRALO: x"); }
    else { printf("REMIS"); }
    getchar();
    return 0;
}
