#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct date{
unsigned int Dzien:5;
unsigned int Miesiac:4;
unsigned int rok:11;
}data;

struct wybor{
unsigned int opcja1:1;
unsigned int opcja2:1;
unsigned int opcja3:1;
}wybor1;

void przydziel(int* x){
wybor1.opcja3=*x/4;
*x=*x%4;
wybor1.opcja2=*x/2;
*x=*x%2;
wybor1.opcja1=*x;
}
int main()
{
    time_t czas;
    struct tm *ptr;
    int *x;
    x=malloc(sizeof(int));
    time(&czas);
    ptr=localtime(&czas);
    data.Dzien=ptr->tm_mday;
    data.Miesiac=ptr->tm_mon+1;
    data.rok=ptr->tm_year+1900;
    do{
    printf("Podaj sume tego co ma byc wyswietlone (1-dzien,2-miesiac,4-rok)\n[np 5=1+4 wyswietli dzien i rok]\n");
    scanf("%d",x);
    }while(*x>7 || *x<0);
    przydziel(x);
    free(x);
    if(wybor1.opcja1==1)
        printf("%d ",data.Dzien);
    if(wybor1.opcja2==1)
        printf("%d ",data.Miesiac);
    if(wybor1.opcja3==1)
        printf("%d",data.rok);

    return 0;
}
