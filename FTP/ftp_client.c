#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8000
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};
    char filename[BUFFER_SIZE] = {0};

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Enter the filename to request: ");
    scanf("%s", filename);

    
    send(client_socket, filename, strlen(filename), 0);

    

    printf("File content received:\n");
    while (recv(client_socket, buffer, BUFFER_SIZE, 0) > 0)
    {
        printf("%s", buffer);
        memset(buffer, 0, BUFFER_SIZE);
    }

    printf("\n");
    close(client_socket);

    return 0;
}

/*
Algorithm: Handling a Client Request  

1. START  
2. Initialize a buffer and filename array  
3. Receive the requested filename from the client using recv()  
4. Open the requested file in read mode using fopen()  
5. If the file does not exist:  
   5.1. Send an error message "File not found" to the client  
   5.2. Print an error message and return  
6. If the file exists:  
   6.1. Read the file contents line by line using fgets()  
   6.2. Send each line to the client using send()  
   6.3. Clear the buffer after each send operation  
7. Print a message indicating that the file was sent  
8. Close the file  
9. Close the client socket  
10. STOP  

Algorithm: File Transfer using TCP (Client)  

1. START  
2. Create a socket using socket(AF_INET, SOCK_STREAM, 0)  
3. Check if the socket creation was successful. If not, print an error and exit  
4. Define the server address structure:  
   4.1. Set sin_family to AF_INET  
   4.2. Set sin_port to htons(PORT)  
   4.3. Set sin_addr.s_addr to inet_addr("127.0.0.1")  
5. Connect to the server using connect()  
6. Check if the connection was successful. If not, print an error and exit  
7. Prompt the user to enter the filename  
8. Send the filename to the server using send()  
9. Receive the file contents from the server using recv() in a loop  
10. Print the received file contents  
11. Close the client socket  
12. STOP
*/