#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>

int main() {
    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = htons(INADDR_ANY);

    char buff[100];
    bool quit = false;
    while (!quit) {
        int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != -1) {
            gets(buff);
            if (strcmp(buff, "quit") == 0)
                quit = true;
            send(clientSocket, buff, strlen(buff), 0);
            int n = recv(clientSocket, buff, 100, 0);
            if (n > 0) {
                buff[n] = '\0';
                printf("%s\n", buff);
            }
        }
        else
            break;
        close(clientSocket);
    }
}
