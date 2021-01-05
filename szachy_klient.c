#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>

void wypisz(int plansza[8][8])
{
    printf("    a   b   c   d   e   f   g   h \n  --------------------------------\n");
    for(int i=0;i<8;i++)
    {
        printf("%d ",i+1);
        for(int j=0;j<8;j++)
        {
         if(plansza[i][j]==1)
            printf("| k ");
         if(plansza[i][j]==2)
            printf("| h ");
         if(plansza[i][j]==5)
            printf("| s ");
         if(plansza[i][j]==3)
            printf("| g ");
         if(plansza[i][j]==4)
            printf("| w ");
         if(plansza[i][j]==6)
            printf("| p ");
         if(plansza[i][j]==7)
            printf("| K ");
         if(plansza[i][j]==8)
            printf("| H ");
         if(plansza[i][j]==11)
            printf("| S ");
         if(plansza[i][j]==9)
            printf("| G ");
         if(plansza[i][j]==10)
            printf("| W ");
         if(plansza[i][j]==12)
            printf("| P ");
         if(plansza[i][j]==0)
            printf("|   ");

        }
    printf("|\n  --------------------------------\n");
    }
}

int main()
{
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in klient;
    int plansza[8][8];
    int ruch[4];
    char ty,dy,wiad[3];
    int tx,dx,wys;

    if(WSAStartup(MAKEWORD(2,2),&wsa) != 0){
        printf("failed");
        getch();
        return 1;
    }
    printf("works\n");

    if((s=socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET){
        printf("Socket error");
        getch();
        return 1;
    }
    printf("socket created\n");

    klient.sin_addr.s_addr = inet_addr("127.0.0.1");
    klient.sin_family = AF_INET;
    klient.sin_port = htons(9000);

    if(connect(s, (struct sockaddr *)&klient, sizeof(klient))<0)
    {
        puts("connect error");
        getch();
        return 1;
    }
    puts("Connected\n");

    for(int i=0;i<8;i++)
    if(recv(s,(char*)plansza[i],sizeof(int)*8,0) == SOCKET_ERROR){
        printf("receive error");
        getch();
        return 1;
    }
    wypisz(plansza);

    while(1)
    {
        do
        {
        printf("podaj pozycje pionka ktorego chcesz przesunac oraz pozycje na która chcesz pionek przesunac (np: 3a4b)\n");
        scanf("%d%c%d%c",&tx,&ty,&dx,&dy);
        ruch[0]=tx-1;
        ruch[1]=(int)ty-(int)'a';
        ruch[2]=dx-1;
        ruch[3]=(int)dy-(int)'a';
        }while(plansza[ruch[0]][ruch[1]]==0 || ruch[0]>=8 || ruch[0]<0 || ruch[1]>=8 || ruch[1]<0 || plansza[ruch[0]][ruch[1]]>=7 || (plansza[ruch[2]][ruch[3]]<7 && plansza[ruch[2]][ruch[3]] != 0) || ruch[2]>=8 || ruch[2]<0 || ruch[3]>=8 || ruch[3]<0);

        send(s,(char*)ruch,sizeof(int)*4,0);

        if(recv(s,wiad,3,0)==SOCKET_ERROR){
            puts("receive error");
            getch();
            return 1;
        }
        if(strcmp(wiad,":o")==0)
        {
            printf("jesteœ tam szachowany!!\nJeszcze raz!\n");
            continue;
        }
        if(recv(s,wiad,3,0)==SOCKET_ERROR){
            puts("receive error");
            getch();
            return 1;
        }

        if(strcmp(wiad,":q")==0)
        break;

        system("cls");
        for(int i=0;i<8;i++)
        if(recv(s,(char*)plansza[i],sizeof(int)*8,0) == SOCKET_ERROR){
            printf("receive error");
            getch();
            return 1;
        }
        wypisz(plansza);

        if(recv(s,wiad,3,0)==SOCKET_ERROR){
            puts("receive error");
            getch();
            return 1;
        }
        if(strcmp(wiad,":s")==0)
        printf("szach AI!!\n");

        if(recv(s,wiad,3,0)==SOCKET_ERROR){
            puts("receive error");
            getch();
            return 1;
        }

        if(strcmp(wiad,":q")==0)
        break;
    }
    system("cls");
    for(int i=0;i<8;i++)
    if(recv(s,(char*)plansza[i],sizeof(int)*8,0) == SOCKET_ERROR){
        printf("receive error");
        getch();
        return 1;
    }
    wypisz(plansza);
    if(recv(s,wiad,3,0)==SOCKET_ERROR){
        puts("receive error");
        getch();
        return 1;
    }
    if(strcmp(wiad,":a")==0)
        puts("AI WON");
    else if(strcmp(wiad,":w")==0)
        puts("YOU WON");
    else if(strcmp(wiad,":p")==0)
        puts("pat");
    else
        puts("error");
    closesocket(s);
    WSACleanup();
    getch();
    return 0;
}
