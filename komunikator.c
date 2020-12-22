#include <stdio.h>
#include <winsock2.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL,"");
    WSADATA wsa;
    SOCKET s;
    char *message, odp[2000];
    struct sockaddr_in server;
    int odp_size;

    if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed");
        return 1;
    }
    printf("dzia³a\n");

    if((s=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET)
        printf("nima socketa");
    printf("jest socket\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(9000);

    if(connect(s, (struct sockaddr *)&server, sizeof(server))<0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected");
    message = "dzia³laj please";
    if( send(s, message, strlen(message),0)<0)
    {
        puts("send Failed");
        return 1;
    }
    puts("Data Send\n");

    if((odp_size = recv(s, odp, 2000, 0))== SOCKET_ERROR)
    {
        puts("recv failed");
    }

    puts("Reply received\n");
    odp[odp_size] = '\0';
    puts(odp);
    closesocket(s);
    WSACleanup();
    return 0;
}
