#include <stdio.h>
#include <winsock2.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL,"");
    WSADATA wsa;
    SOCKET s;
    char *message, odp[2000],message2[2000];
    struct sockaddr_in server;
    int odp_size;

    if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed");
        return 1;
    }
    printf("works\n");

    if((s=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET)
        printf("no socketa");
    printf("is socket\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(9000);

    if(connect(s, (struct sockaddr *)&server, sizeof(server))<0)
    {
        puts("connect error");
        getch();
        return 1;
    }

    puts("Connected");
   /* message = "dzialaj please";
    if( send(s, message, strlen(message),0)<0)
    {
        puts("send Failed");
        return 1;
    }
    puts("Data Send\n"); */

    if((odp_size = recv(s, odp, 2000, 0))== SOCKET_ERROR)
    {
        puts("recv failed");
    }

    puts("Reply received\n");
    odp[odp_size] = '\0';
    puts(odp);
    while(1)
    {
    printf("write a reply: ");
    fgets(message2,2000,stdin);
    send(s, message2, strlen(message2),0);
    if((odp_size=recv(s, odp, 2000, 0)) == SOCKET_ERROR)
    puts("error");
    puts("Reply received\n");
    odp[odp_size]='\0';
    if(strcmp(odp,":q\n")==0)
    break;
    puts(odp);
    }
    closesocket(s);
    WSACleanup();
    return 0;
}
