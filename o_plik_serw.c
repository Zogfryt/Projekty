#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>

int main(){
WSADATA wsa;
SOCKET s,new_socket;

FILE *fp;
struct sockaddr_in serwer,client;
char *message,odp[2000],ndziala[]="ndziala",dziala[]="aaaaaaa";
int odp_dl,l=0;


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

if((bind(s,(struct sockaddr *)&serwer,sizeof(serwer))) == SOCKET_ERROR){
    printf("Bind error");
    getch();
    return 1;
}
printf("binding correct\n");

if(!listen(s,30))
printf("listening...\n");
else{
printf("error with listening\n");
getch();
return 1;
}

int c=sizeof(struct sockaddr_in);
if((new_socket = accept(s,(struct sockaddr *)&client,&c)) == INVALID_SOCKET){
    printf("accept failed");
    getch();
    return 1;
}
while(1){
l=0;
message="insert the name of the file (write :q to end): ";
send(new_socket,message,strlen(message),0);

int odp_dlr;

if(recv(new_socket,(char *)&odp_dlr,sizeof(int),0) == SOCKET_ERROR){
    printf("receive error");
    getch();
    return 1;
}

if(recv(new_socket,odp,sizeof(char)*odp_dlr+1,0) == SOCKET_ERROR){
    printf("receive error");
    getch();
    return 1;
}

char plik[odp_dlr];

for(int i=0;i<odp_dlr;i++)
plik[i]=odp[i];
plik[odp_dlr-1]='\0';

if(strcmp(plik,":q")==0)
break;

fp=fopen(plik,"r");
if(fp==NULL)
{
send(new_socket,ndziala,8,0);
continue;
}
else
send(new_socket,dziala,8,0);

char znak=getc(fp);
while(znak!=EOF)
{
    if(znak=='\n')
    l++;
    znak=getc(fp);
}
send(new_socket,(char*)&l,sizeof(int),0);

rewind(fp);
for(int i=0;i<l;i++)
{
    fgets(odp,2000,fp);
    odp_dlr=strlen(odp);
    send(new_socket,(char *)&odp_dlr,sizeof(int),0);
    send(new_socket,odp,sizeof(char)*odp_dlr+1,0);
}
fclose(fp);
}
printf("end of transmission");
closesocket(s);
closesocket(new_socket);
WSACleanup();
getch();
return 0;
}
