#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 8088

int main(){
    struct sockaddr_in server_address, client_address;
    socklen_t clientlen = sizeof(client_address);
    char buffer[40];

    int serverfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    server_address.sin_family = AF_INET;

    if(bind(serverfd, (struct sockaddr *) &server_address, sizeof(server_address))<0){
        perror("CANNOT BIND");
        return 0;
    }

    recvfrom(serverfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_address, &clientlen);
    printf(buffer);
    sendto(serverfd, "Hello\n", 10, 0, (struct sockaddr *) &client_address, clientlen);


    close(serverfd);
}
