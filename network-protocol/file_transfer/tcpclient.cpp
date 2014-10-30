#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>

#define BUFFLEN 1000

int main() {
    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = htons(INADDR_ANY);

    char buff[BUFFLEN];
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != -1) {
        printf("Connection established.\n");
        FILE *file = fopen("recv.pdf", "wb");
        int n;
        while ((n = recv(clientSocket, buff, BUFFLEN, 0)) > 0) {
            fwrite(buff, 1, n, file);
            send(clientSocket, "ack", 3, 0);
        }
        printf("Successfully receive file.\n");
        close(clientSocket);
    }
}
