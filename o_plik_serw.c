#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>

int main(){
WSADATA wsa;
SOCKET s,new_socket;

FILE *fp;
struct sockaddr_in serwer,client;
char *message,odp[2000];
int odp_dl,l,b=0;

WSAStartup(MAKEWORD(2,2),&wsa);
s=socket(AF_INET,SOCK_STREAM,0);

serwer.sin_addr.s_addr = inet_addr("127.0.0.1");
serwer.sin_family = AF_INET;
serwer.sin_port = htons(9000);

message="insert the name of the file: ";

bind(s,(struct sockaddr *)&serwer,sizeof(serwer));
listen(s,30);
int c=sizeof(struct sockaddr_in);
new_socket = accept(s,(struct sockaddr *)&client,&c);
send(new_socket,message,strlen(message),0);

odp_dl=recv(new_socket,odp,2000,0);
char plik[odp_dl-1];
//for(int i=0;i<odp_dl;i++)
//plik[i]=odp[i];
snprintf(plik,sizeof(plik),"%s",odp);
fp=fopen(plik,"r");
char znak=getc(fp);
while(znak!=EOF)
{
    if(znak=='\n')
    l++;
    getc(fp);
}
send(new_socket,(char*)&l,sizeof(int),0);
getch();

return 0;
}
