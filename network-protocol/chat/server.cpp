#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAXCLIENT 32
#define BUFLEN 256

struct Client {
    bool used;
    char sendBuffer[BUFLEN];
    int clientSocket;
    pthread_mutex_t m; // This is equivalent to CRITICAL_SECTION on Windows.
    sem_t s; // Semaphore
    sockaddr_in clientAddr;
} client[MAXCLIENT];

void broadcast(char *buff) {
    printf("%s\n", buff);
    for (int i = 0; i < MAXCLIENT; i++)
        if (client[i].used) {
            pthread_mutex_lock(&client[i].m); // EnterCriticalSection(&cs);
            strcpy(client[i].sendBuffer, buff);
            sem_post(&client[i].s); // Semaphore + 1
            pthread_mutex_unlock(&client[i].m); // LeaveCriticalSection(&cs);
        }
}

void *sender(void *ptr) {
    Client *curClient = (Client *)ptr;
    while (true) {
        sem_wait(&curClient->s); // Semaphore - 1
        pthread_mutex_lock(&curClient->m); // EnterCriticalSection(&cs);
        send(curClient->clientSocket, curClient->sendBuffer,
                strlen(curClient->sendBuffer), 0);
        pthread_mutex_unlock(&curClient->m); // LeaveCriticalSection(&cs);
    }
}

void *receiver(void *ptr) {
    pthread_t pid;
    pthread_create(&pid, NULL, sender, ptr);
    Client *curClient = (Client *)ptr;
    char recvBuffer[BUFLEN], sendBuffer[BUFLEN];
    int n;
    while (true) {
        n = recv(curClient->clientSocket, recvBuffer, BUFLEN, 0);
        if (n == 0) {
            sprintf(sendBuffer, "Client (%s:%d) is off.",
                    inet_ntoa(curClient->clientAddr.sin_addr),
                    curClient->clientAddr.sin_port
                    );
            broadcast(sendBuffer);
            break;
        }

        recvBuffer[n] = '\0';
        time_t now;
        time(&now);
        char *ptr = ctime(&now);
        sprintf(sendBuffer, "%s%s:%d\n%s",
                ptr,
                inet_ntoa(curClient->clientAddr.sin_addr),
                curClient->clientAddr.sin_port,
                recvBuffer
                );
        broadcast(sendBuffer);
    }
    curClient->used = false;
    pthread_mutex_destroy(&curClient->m); // Destroy mutex.
    pthread_cancel(pid);
    pthread_exit(NULL);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = htons(INADDR_ANY);
    bzero(&(serverAddr.sin_zero), 8);

    if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr))!= 0) {
        printf("Fail to bind (errno=%d).\n", errno);
        exit(1);
    }

    if (listen(serverSocket, 10) != 0) {
        printf("Fail to listen.\n");
        exit(1);
    }

    int clientId = 0;
    socklen_t len = sizeof(sockaddr_in);
    while (true) {
        while (client[clientId].used) {
            clientId++;
            if (clientId == MAXCLIENT)
                clientId = 0;
        }

        client[clientId].clientSocket = accept(
                serverSocket,
                (sockaddr *)&client[clientId].clientAddr,
                &len
                );
        client[clientId].used = true;

        // Initialize mutex.
        pthread_mutexattr_t mAttr;
        pthread_mutexattr_settype(&mAttr, PTHREAD_MUTEX_RECURSIVE_NP);
        pthread_mutex_init(&client[clientId].m, &mAttr);
        pthread_mutexattr_destroy(&mAttr);

        sem_init(&client[clientId].s, 0, 0); // Initialize semaphore.

        pthread_t pid;
        pthread_create(&pid, NULL, receiver, &client[clientId]);

        printf("Client (%s:%d) enter.\n",
                inet_ntoa(client[clientId].clientAddr.sin_addr),
                client[clientId].clientAddr.sin_port
                );
    }

    close(serverSocket);
    printf("Server closed.\n");
}
