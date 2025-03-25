#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8085

int main(){
    struct sockaddr_in server_address;
    int client_len;
    char buffer[40];

    int clientfd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientfd, (struct sockaddr *)&server_address, sizeof(server_address));

    while(1){
        read(clientfd, buffer, sizeof(buffer));
        printf("%s\n", buffer);   
        printf(">");
        scanf(" %[^\n]", buffer);
        send(clientfd, buffer, sizeof(buffer), 0);
        if(strcmp(buffer, "exit") == 0){
            break;
        }
    }


    close(clientfd); 

    
}