#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8086
#define LOSS_PROBABILITY 30

int main() {
    struct sockaddr_in server_address, client_address;
    socklen_t client_len = sizeof(client_address);
    char buffer[40];

    srand(time(NULL));

    int serverfd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("CANNOT BIND");
        return 0;
    }

    listen(serverfd, 5);
    printf("Waiting for connection...\n");

    int clientfd = accept(serverfd, (struct sockaddr *)&client_address, &client_len);
    printf("Connected\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        if (read(clientfd, buffer, sizeof(buffer)) <= 0) break;

        printf("Received packet %s\n", buffer);

        if (rand() % 100 < LOSS_PROBABILITY) {
            printf("Acknowledgement lost for packet %s\n", buffer);
        } else {
            printf("Acknowledgement sent for packet %s\n", buffer);
            send(clientfd, buffer, sizeof(buffer), 0);
        }
    }

    close(clientfd);
    close(serverfd);
    return 0;
}
