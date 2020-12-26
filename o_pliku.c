#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>

int main(){
WSADATA wsa;
SOCKET s;

FILE *fp;
struct sockaddr_in serwer;
char message[2000],odp[2000];
int l=0,odp_dl;


WSAStartup(MAKEWORD(2,2),&wsa);
s=socket(AF_INET,SOCK_STREAM,0);

serwer.sin_addr.s_addr = inet_addr("127.0.0.1");
serwer.sin_family = AF_INET;
serwer.sin_port = htons(9000);

connect(s,(struct sockaddr *)&serwer, sizeof(serwer));

odp_dl=recv(s,odp,2000,0);
odp[odp_dl]='\0';
puts(odp);

fgets(message,2000,stdin);
send(s,message,2000,0);

recv(s,(char *)&l,sizeof(int),0);
printf("%d",l);
getch();
return 0;
}
