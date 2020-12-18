#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    int cyfra,l=0;
    if((fp=fopen("test.txt","w+"))==NULL)
    {
        printf("Nie mogê odczytaæ pliku");
        exit(1);
    }
    for(int i=1;i<=1000;i++){
    fprintf(fp, "%d\n",i);
    l++;
    }
    rewind(fp);
    for(int i=0;i<l;i++){
        fscanf(fp,"%d\n",&cyfra);
        printf("%d\n",cyfra);
    }

    fclose(fp);
    return 0;
}
