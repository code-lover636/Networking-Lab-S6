#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8089

int main(){
    struct sockaddr_in server_address, client_address;
    socklen_t serverlen = sizeof(server_address);
    char buffer[1024] = {0};

    int clientfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    server_address.sin_family = AF_INET;

    sendto(clientfd, "TIME", 4, 0, (struct sockaddr *)&server_address, serverlen);
    recvfrom(clientfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_address, &serverlen);
    printf(buffer);

    close(clientfd);
}
