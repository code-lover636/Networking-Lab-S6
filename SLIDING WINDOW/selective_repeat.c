#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TOTAL_FRAMES 10
#define WINDOW_SIZE 4
#define LOSS_PROBABILITY 20  


int send_frame(int frame_number) {
    printf("Sending frame %d...\n", frame_number);
    sleep(1);  

    if ((rand() % 100) < LOSS_PROBABILITY) {
        printf("Frame %d lost during transmission!\n", frame_number);
        return 0; 
    }

    printf("Frame %d sent successfully.\n", frame_number);
    return 1; 
}


int receive_ack(int frame_number) {
    printf("Waiting for ACK for frame %d...\n", frame_number);
    sleep(1);  

    if ((rand() % 100) < LOSS_PROBABILITY) {
        printf("ACK for frame %d lost!\n", frame_number);
        return 0; 
    }

    printf("ACK for frame %d received.\n", frame_number);
    return 1; 
}

int main() {

    int base = 0;
    int ack_received[TOTAL_FRAMES] = {0};

    while (base < TOTAL_FRAMES) {
        
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (!ack_received[i]) {
                int sent = send_frame(i);
                if (sent) {
                    int ack = receive_ack(i);
                    if (ack) {
                        ack_received[i] = 1;
                    } else {
                        printf("ACK lost for frame %d. Will retry.\n", i);
                    }
                } else {
                    printf("Frame %d will be retransmitted later.\n", i);
                }
            }
        }

        
        while (base < TOTAL_FRAMES && ack_received[base]) {
            base++;
        }

        printf("\n--- Sliding window to base %d ---\n\n", base);
    }

    printf("All frames sent and acknowledged successfully.\n");
    return 0;
}


