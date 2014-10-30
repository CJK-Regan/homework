#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>

int main() {
    int clientSocket, serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1) {
        printf("Fail to create socket (errno=%d).\n", errno);
        exit(1);
    }

    struct sockaddr_in serverAddr, clientAddr;

    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = htons(INADDR_ANY);
    bzero(&(serverAddr.sin_zero), 8);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr))!= 0) {
        printf("Fail to bind (errno=%d).\n", errno);
        exit(1);
    }

    if (listen(serverSocket, 10) != 0) {
        printf("Fail to listen.\n");
        exit(1);
    }

    char recvbuff[100], sendbuff[100];
    socklen_t len = sizeof(clientAddr);
    bool closing = false;
    while (!closing && (clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &len)) > 0) {
        int n;
        while((n = recv(clientSocket, recvbuff, 100, 0)) > 0) {
            recvbuff[n] = '\0';
            time_t now;
            time(&now);
            char *ptr = ctime(&now);
            sprintf(sendbuff, "%s%s:%d\n%s", ptr, inet_ntoa(clientAddr.sin_addr), clientAddr.sin_port, recvbuff);
            printf("%s\n", sendbuff);
            send(clientSocket, sendbuff, strlen(sendbuff), 0);
            if (strcmp(recvbuff, "quit") == 0)
                break;
            else if (strcmp(recvbuff, "close") == 0) {
                closing = true;
                break;
            }
        }
        close(clientSocket);
    }
    close(serverSocket);
    printf("Server closed.\n");
}
