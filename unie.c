#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

enum kolor {zielony,czerwony,niebieski,fioletowy,czarny,bialy,ekri,lososiowy};

int main()
{
    setlocale(LC_ALL,"");
    enum kolor koszulka,buty,skarpetki,spodnie;
    koszulka=rand()%8;


    switch (koszulka)
    {
    case zielony:
        printf("Ubierz zielona koszulkê");
        break;
    case czerwony:
        printf("Ubierz czerwon¹ koszulkê");
        break;
    case niebieski:
        printf("Ubierz niebiesk¹ koszulkê");
        break;
    case fioletowy:
        printf("Ubierz fioletow¹ koszulkê");
        break;
    case czarny:
        printf("ubierz czarn¹ koszulkê");
        break;
    case bialy:
        printf("Ubierz bia³¹ koszulke");
        break;
    case ekri:
        printf("Ubierz koszulkê koloru ekri");
        break;
    case lososiowy:
        printf("Ubierz lososiow¹ koszulkê");
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
        printf(", bia³e buty");
        break;
    case ekri:
        printf(", buty koloru ekri");;
        break;
    case lososiowy:
        printf(", ³ososiowe buty");
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
        printf(", bia³e spodnie");
        break;
    case ekri:
         printf(", spodnie koloru ekri");
        break;
    case lososiowy:
         printf(", ³ososiowe spodnie");
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
        printf(", bia³e skarpetki");
        break;
    case ekri:
         printf(", skarpetki koloru ekri");
        break;
    case lososiowy:
         printf(", ³ososiowe skarpetki");
        break;
    }


    return 0;
}
