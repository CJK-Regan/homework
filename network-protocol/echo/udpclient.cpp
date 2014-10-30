#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock == -1) {
        printf("Fail to create socket (errno=%d).\n", errno);
        exit(1);
    }

    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char buff[100];
    bool quit = false;
    socklen_t len = sizeof(serverAddr);
    while (!quit) {
        gets(buff);
        if (strcmp(buff, "quit") == 0 || strcmp(buff, "close") == 0)
            quit = true;
        sendto(sock, buff, strlen(buff), 0, (struct sockaddr *)&serverAddr, len);
        int n = recvfrom(sock, buff, 100, 0, (struct sockaddr *)&serverAddr, &len);
        buff[n] = '\0';
        printf("%s\n", buff);
    }
    close(sock);
}
