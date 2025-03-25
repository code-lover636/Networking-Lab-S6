#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 8088

int main(){
    struct sockaddr_in server_address, client_address;
    socklen_t serverlen = sizeof(server_address);
    char buffer[40];

    int clientfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);
    server_address.sin_family = AF_INET;

    sendto(clientfd, "Hello\n", 10, 0, (struct sockaddr *) &server_address, serverlen);
    recvfrom(clientfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &server_address, &serverlen);
    printf(buffer);

    close(clientfd);
}
