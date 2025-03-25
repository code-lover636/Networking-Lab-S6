#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8085

int main(){
    struct sockaddr_in server_address, client_address;
    int client_len;
    char buffer[40];

    int serverfd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if(bind(serverfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        perror("CANNOT BIND");
        return 0;
    }

    listen(serverfd, 5);
    printf("waiting for connection...\n");
    int clientfd = accept(serverfd, (struct sockaddr * )&client_address, &client_len);
    printf("Connected\n");

    while(1){
        printf(">");
        scanf(" %[^\n]", buffer);
        send(clientfd, buffer, sizeof(buffer), 0);
        read(clientfd, buffer, sizeof(buffer));
        printf("%s\n", buffer);   
        if(strcmp(buffer, "exit") == 0){
            break;
        }
    }

    close(serverfd);
    close(clientfd); 

    
}
