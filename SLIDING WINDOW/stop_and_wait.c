#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {

    int packet = 1;

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

/*

1. START  

2. Initialize variables  
   2.1. Set packet = 1 (starting packet number).  

3. Process packets in a loop  
   3.1. While packet is less than or equal to 5  
       3.1.1. Print "Sender: Sending packet <packet>...".  
       3.1.2. Introduce a delay of 1 second using sleep(1).  
       3.1.3. Generate a random number from 0 to 9 using rand() % 10.  
       3.1.4. If the random number is less than 7 (70% success probability)  
           3.1.4.1. Print "Receiver: ACK for packet <packet> received.".  
           3.1.4.2. Increment packet by 1 (move to next packet).  
       3.1.5. Else (ACK lost)  
           3.1.5.1. Print "Receiver: ACK for packet <packet> lost! Retransmitting...".  
           3.1.5.2. Introduce a delay of 3 seconds using sleep(3) before retransmission.  

4. Print "All packets sent successfully!".  

5. STOP

*/