#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {

    int packet = 1, ack_received;

    while (packet <= 5) {
        printf("Sender: Sending packet %d...\n", packet);
        
        sleep(1);  

        if (rand() % 10 < 7) {
            printf("Receiver: ACK for packet %d received.\n\n", packet);
            packet++;  
        } else {
            printf("Receiver: ACK for packet %d lost! Retransmitting...\n\n", packet);
            sleep(3);  
        }
    }

    printf("All packets sent successfully!\n");
}