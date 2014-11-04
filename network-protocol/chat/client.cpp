#include <cstdio>
#include <cstring>
#include <netdb.h>
#include <pthread.h>
#include <unistd.h>

#define BUFLEN 256

int clientSocket;

void *thread(void *ptr) {
    char buffer[BUFLEN];
    int n;
    while (true) {
        n = recv(clientSocket, buffer, BUFLEN, 0);
        if (n == 0) {
            printf("Disconnected.\n");
            break;
        }
        buffer[n] = '\0';
        printf("%s\n", buffer);
    }
    pthread_exit(NULL);
}

int main() {
    sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = htons(INADDR_ANY);

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(clientSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) != -1) {
        pthread_t pid;
        pthread_create(&pid, NULL, thread, NULL);
        char buffer[BUFLEN];
        while (true) {
            gets(buffer);
            if (strcmp(buffer, "exit") == 0)
                break;
            send(clientSocket, buffer, strlen(buffer), 0);
        }
        close(clientSocket);
    }
    else
        printf("Connection failed.\n");
}
