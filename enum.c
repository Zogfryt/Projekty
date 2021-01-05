#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

enum kolor {zielony,czerwony,niebieski,fioletowy,czarny,bialy,ekri,lososiowy};

int main()
{
    system("chcp 65001");
    system("cls");
    enum kolor koszulka,buty,skarpetki,spodnie;
    srand(time(NULL));
    koszulka=rand()%8;


    switch (koszulka)
    {
    case zielony:
        printf("Ubierz zieloną koszulke");
        break;
    case czerwony:
        printf("Ubierz czerwoną koszulke");
        break;
    case niebieski:
        printf("Ubierz niebieską koszulke");
        break;
    case fioletowy:
        printf("Ubierz fioletową koszulke");
        break;
    case czarny:
        printf("ubierz czarną koszulke");
        break;
    case bialy:
        printf("Ubierz białą koszulke");
        break;
    case ekri:
        printf("Ubierz koszulke koloru ekri");
        break;
    case lososiowy:
        printf("Ubierz lososiową koszulke");
        break;
    }

    buty=rand()%8;
        switch (buty)
    {
    case zielony:
        printf(", zielone buty");
        break;
    case czerwony:
        printf(", czerwone buty");
        break;
    case niebieski:
        printf(", niebieskie buty");
        break;
    case fioletowy:
        printf(", fioletowe buty");
        break;
    case czarny:
        printf(", czarne buty");
        break;
    case bialy:
        printf(", białe buty");
        break;
    case ekri:
        printf(", buty koloru ekri");;
        break;
    case lososiowy:
        printf(", łososiowe buty");
        break;
    }

    spodnie=rand()%8;
        switch (spodnie)
    {
    case zielony:
        printf(", zielone spodnie");
        break;
    case czerwony:
        printf(", czerwone spodnie");
        break;
    case niebieski:
        printf(", niebieskie spodnie");
        break;
    case fioletowy:
        printf(", fioletowe spodnie");
        break;
    case czarny:
        printf(", czarne spodnie");
        break;
    case bialy:
        printf(", białe spodnie");
        break;
    case ekri:
         printf(", spodnie koloru ekri");
        break;
    case lososiowy:
         printf(", łososiowe spodnie");
        break;
    }

    skarpetki=rand()%8;
            switch (skarpetki)
    {
    case zielony:
        printf(", zielone skarpetki");
        break;
    case czerwony:
        printf(", czerwone skarpetki");
        break;
    case niebieski:
        printf(", niebieskie skarpetki");
        break;
    case fioletowy:
        printf(", fioletowe skarpetki");
        break;
    case czarny:
        printf(", czarne skarpetki");
        break;
    case bialy:
        printf(", białe skarpetki");
        break;
    case ekri:
         printf(", skarpetki koloru ekri");
        break;
    case lososiowy:
         printf(", łososiowe skarpetki");
        break;
    }


    return 0;
}
