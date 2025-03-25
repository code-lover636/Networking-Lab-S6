#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8095
#define BUFFER_SIZE 1024
#define LOSS_PROBABILITY 30  // 30% chance of ACK loss

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    int ack;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("Cannot bind");
        return 0;
    }

    // Listen for client
    listen(server_fd, 3);
    printf("Server: Waiting for connection...\n");

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    printf("Server: Connection established.\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        if (valread == 0) break;

        ack = atoi(buffer);
        printf("Server: Received packet %d\n", ack);

        // Simulate ACK loss
        if (rand() % 100 < LOSS_PROBABILITY) {
            printf("Server: ACK for packet %d lost!\n\n", ack);
        } else {
            sleep(1);  // Simulate processing delay
            printf("Server: ACK sent for packet %d\n\n", ack);
            memset(buffer,0,BUFFER_SIZE);
            sprintf(buffer, "%d", ack);  // Send ACK
            send(new_socket, buffer, strlen(buffer)+1, 0);
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}

/* 

1. START  

2. Initialize variables  
   2.1. Declare server_fd, new_socket, address, addrlen, buffer, and ack.  
   2.2. Set BUFFER_SIZE to 1024 and PORT to 8095.  
   2.3. Set LOSS_PROBABILITY to 30 (30% chance of ACK loss).  

3. Create a socket  
   3.1. Call socket(AF_INET, SOCK_STREAM, 0) to create a TCP socket.  
   3.2. Assign address.sin_family = AF_INET.  
   3.3. Set address.sin_addr.s_addr = INADDR_ANY (accept connections from any address).  
   3.4. Set address.sin_port = htons(PORT) to bind the socket to the given port.  

4. Bind the socket  
   4.1. Call bind(server_fd, (struct sockaddr *)&address, sizeof(address)).  
   4.2. If binding fails, print "Cannot bind" and exit.  

5. Listen for incoming client connections  
   5.1. Call listen(server_fd, 3).  
   5.2. Print "Server: Waiting for connection...".  

6. Accept a client connection  
   6.1. Call accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen).  
   6.2. Print "Server: Connection established.".  

7. Process incoming packets in a loop  
   7.1. Loop until the connection is closed  
       7.1.1. Clear buffer using memset(buffer, 0, BUFFER_SIZE).  
       7.1.2. Read data from new_socket into buffer.  
       7.1.3. If valread == 0, break the loop (client disconnected).  
       7.1.4. Convert received buffer to an integer and store in ack.  
       7.1.5. Print "Server: Received packet <ack>".  

8. Simulate ACK loss  
   8.1. Generate a random number from 0 to 99 using rand() % 100.  
   8.2. If the random number is less than LOSS_PROBABILITY  
       8.2.1. Print "Server: ACK for packet <ack> lost!".  
   8.3. Else (ACK is sent successfully)  
       8.3.1. Introduce a 1-second processing delay using sleep(1).  
       8.3.2. Print "Server: ACK sent for packet <ack>".  
       8.3.3. Convert ack to a string and store it in buffer.  
       8.3.4. Send buffer to new_socket using send().  

9. Close connections  
   9.1. Close new_socket.  
   9.2. Close server_fd.  

10. STOP

*/