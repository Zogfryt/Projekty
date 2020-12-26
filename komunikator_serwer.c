#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    WSADATA wsa;
    SOCKET s, new_socket;
    int c, odp_size;
    struct sockaddr_in serwer, client;
    char *message,odp[2000],message2[2000];

    if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed");
        return 1;
    }
    printf("works\n");

    if((s=socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Socket doesn't work");
        return 1;
    }
    printf("Socket works\n");

    serwer.sin_family=AF_INET;
    serwer.sin_addr.s_addr = inet_addr("127.0.0.1");
    serwer.sin_port = htons(9000);

    if( bind(s,(struct sockaddr *)&serwer,sizeof(serwer)) == SOCKET_ERROR)
    {
        printf("BIND FAILED");
        return 1;
    }


    puts("bind done\n");
    listen(s,30);
    puts("waiting for connection...");
    c = sizeof(struct sockaddr_in);
    new_socket = accept(s, (struct sockaddr *)&client,&c);
    if(new_socket == INVALID_SOCKET)
    printf("accept failed");
    puts("connection accepted");
    message = "Hello Client, I have received your connection.\n";
    send(new_socket, message, strlen(message),0);
    while(1)
    {
    if((odp_size=recv(new_socket, odp, 2000, 0)) == SOCKET_ERROR)
    puts("error");
    puts("Reply received\n");
    odp[odp_size]='\0';
    if(strcmp(odp,":q\n")==0){
        send(new_socket,odp,2000,0);
        break;
    }
    puts(odp);
    printf("write an answer (:q to end connection): ");
    fgets(message2,2000,stdin);
    send(new_socket, message2, strlen(message2),0);
    }
    printf("end of transmission");
    getch();
    closesocket(s);
    WSACleanup();
    return 0;
}
