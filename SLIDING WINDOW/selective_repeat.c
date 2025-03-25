#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10
#define LOSS_PROBABILITY 20

int send_frame(int frame_number) {
    printf("Sending frame %d...\n", frame_number);
    sleep(1);

    if ( (rand() % 100) < LOSS_PROBABILITY) {
        printf("Frame %d lost during transmission!\n", frame_number);
        return 0;
    }

    printf("Frame %d sent successfully.\n", frame_number);
    return 1;
}

int receive_ack(int frame_number) {
    printf("Receiving acknowledgment for frame %d...\n", frame_number);
    sleep(1);

    if ( (rand() % 100) < LOSS_PROBABILITY) {
        printf("Acknowledgment for frame %d lost!\n", frame_number);
        return 0;
    }

    printf("Acknowledgment for frame %d received.\n", frame_number);
    return 1;
}

int main() {
    int sent_frames[TOTAL_FRAMES] = {0};
    int ack_received[TOTAL_FRAMES] = {0};
    int base = 0;

    while (base < TOTAL_FRAMES) {

        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++)
            if (!sent_frames[i])
                sent_frames[i] = send_frame(i);

        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++)
            if (sent_frames[i] && !ack_received[i])
                ack_received[i] = receive_ack(i);

        while (base < TOTAL_FRAMES && ack_received[base]) {
            base++;
        }
    }

    printf("All frames sent and acknowledged successfully.\n");
}


/*

1. START  

2. Initialize constants and variables  
   2.1. Set WINDOW_SIZE to 4.  
   2.2. Set TOTAL_FRAMES to 10.  
   2.3. Set LOSS_PROBABILITY to 20 (20% chance of frame or ACK loss).  
   2.4. Declare sent_frames[TOTAL_FRAMES] initialized to 0.  
   2.5. Declare ack_received[TOTAL_FRAMES] initialized to 0.  
   2.6. Declare base = 0.  

3. Define function send_frame(frame_number)  
   3.1. Print "Sending frame <frame_number>...".  
   3.2. Introduce a delay of 1 second using sleep(1).  
   3.3. Generate a random number between 0 and 99 using rand() % 100.  
   3.4. If the random number is less than LOSS_PROBABILITY  
       3.4.1. Print "Frame <frame_number> lost during transmission!".  
       3.4.2. Return 0 (frame lost).  
   3.5. Print "Frame <frame_number> sent successfully.".  
   3.6. Return 1 (frame sent).  

4. Define function receive_ack(frame_number)  
   4.1. Print "Receiving acknowledgment for frame <frame_number>...".  
   4.2. Introduce a delay of 1 second using sleep(1).  
   4.3. Generate a random number between 0 and 99 using rand() % 100.  
   4.4. If the random number is less than LOSS_PROBABILITY  
       4.4.1. Print "Acknowledgment for frame <frame_number> lost!".  
       4.4.2. Return 0 (ACK lost).  
   4.5. Print "Acknowledgment for frame <frame_number> received.".  
   4.6. Return 1 (ACK received).  

5. Implement sliding window mechanism  
   5.1. While base is less than TOTAL_FRAMES  
       5.1.1. Send frames within the window  
           5.1.1.1. For each i from base to base + WINDOW_SIZE (within TOTAL_FRAMES)  
               5.1.1.2. If sent_frames[i] is 0, call send_frame(i) and store result in sent_frames[i].  
       5.1.2. Receive ACKs for sent frames  
           5.1.2.1. For each i from base to base + WINDOW_SIZE (within TOTAL_FRAMES)  
               5.1.2.2. If sent_frames[i] is 1 and ack_received[i] is 0, call receive_ack(i) and store result in ack_received[i].  
       5.1.3. Slide window forward  
           5.1.3.1. While base is less than TOTAL_FRAMES and ack_received[base] is 1, increment base.  

6. Print "All frames sent and acknowledged successfully.".  

7. STOP
*/