#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>

#define BUFFLEN 1000

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
    printf("Listening...\n");

    char recvbuff[BUFFLEN], sendbuff[BUFFLEN];
    socklen_t len = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &len);
    if (clientSocket != -1) {
        printf("Connection established.\n");
        FILE *file = fopen("send.pdf", "rb");
        if (file == NULL)
            printf("File not exist.\n");
        else {
            int filesize = 0;
            while (!feof(file)) {
                int count = fread(sendbuff, 1, BUFFLEN, file);
                send(clientSocket, sendbuff, count, 0);
                if (recv(clientSocket, recvbuff, BUFFLEN, 0) <= 0) {
                    printf("Transfer failed.\n");
                    break;
                }
                filesize += count;
                printf("%d Bytes sent\n", filesize);
            }
            printf("Successfully send file.\n");
        }
        fclose(file);
    }
    close(clientSocket);
    close(serverSocket);
    printf("Server closed.\n");
}
