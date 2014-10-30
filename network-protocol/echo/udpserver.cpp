#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock == -1) {
        printf("Fail to create socket (errno=%d).\n", errno);
        exit(1);
    }

    struct sockaddr_in serverAddr, clientAddr;

    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = htons(INADDR_ANY);

    if (bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        printf("Fail to bind (errno=%d).\n", errno);
        exit(1);
    }

    char recvbuff[101], sendbuff[101];
    socklen_t len = sizeof(clientAddr);
    bool closing = false;
    while (!closing) {
        int n = recvfrom(sock, recvbuff, 100, 0, (struct sockaddr *)&clientAddr, &len);
        recvbuff[n] = '\0';
        time_t now;
        time(&now);
        char *ptr = ctime(&now);
        sprintf(sendbuff, "%s%s:%d\n%s", ptr, inet_ntoa(clientAddr.sin_addr), clientAddr.sin_port, recvbuff);
        printf("%s\n", sendbuff);
        sendto(sock, sendbuff, strlen(sendbuff), 0, (struct sockaddr *)&clientAddr, len);
        if (strcmp(recvbuff, "close") == 0) {
            closing = true;
            break;
        }
    }
    close(sock);
    printf("Server closed.\n");
}
