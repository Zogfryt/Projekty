#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>

int main(){
WSADATA wsa;
SOCKET s;

FILE *fp;
struct sockaddr_in serwer;
char message[8000],odp[8000],ndziala[8];
int l=0,odp_dl,odp_dlr;


if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
{
    printf("failed");
    getch();
    return 1;
}
printf("Works\n");

if((s=socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET){
    printf("Socket doesn't work");
    getch();
    return 1;
}
printf("socket created\n");

serwer.sin_addr.s_addr = inet_addr("127.0.0.1");
serwer.sin_family = AF_INET;
serwer.sin_port = htons(9000);

if(connect(s,(struct sockaddr *)&serwer, sizeof(serwer)) < 0){
    printf("connection error");
    getch();
    return 1;
}
printf("connection has been established\n");

while(1){
if((odp_dl=recv(s,odp,8000,0)) == SOCKET_ERROR){
    printf("receive error");
    getch();
    return 1;
}
odp[odp_dl]='\0';
printf("\n%s",odp);

fgets(message,8000,stdin);
odp_dlr=strlen(message);
send(s,(char *)&odp_dlr,sizeof(int),0);
send(s,message,sizeof(char)*odp_dlr+1,0);

if(strcmp(message,":q\n")==0)
break;

if(recv(s,ndziala,8,0) == SOCKET_ERROR)
{
    printf("receive error");
    getch();
    return 1;
}

if(strcmp(ndziala,"ndziala")==0)
{
    puts("can't open, try again");
    continue;
}


if(recv(s,(char *)&l,sizeof(int),0) == SOCKET_ERROR){
    printf("receive error");
    getch();
    return 1;
}

printf("\n----------------------------------------------------------\n");
for(int i=0;i<l;i++)
{
    if(recv(s,(char *)&odp_dlr,sizeof(int),0) == SOCKET_ERROR){
        printf("receive error");
        getch();
        return 1;
    }
    if(recv(s,odp,sizeof(char)*odp_dlr+1,0) == SOCKET_ERROR){
        printf("receive error");
        getch();
        return 1;
    }
    if(strcmp(odp,":w")!=0)
    printf("%s",odp);
}
}
printf("end of transmission");
closesocket(s);
WSACleanup();
getch();
return 0;
}
