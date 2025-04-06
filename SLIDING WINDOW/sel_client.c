#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8086
#define NUM_PACKETS 10
#define WINDOW 5
#define LOSS_PROBABILITY 50

int main() {
    struct sockaddr_in server_address;
    char buffer[40];
    int ackFrame[NUM_PACKETS] = {0};
    int base = 0;

    srand(time(NULL));

    int clientfd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientfd, (struct sockaddr *)&server_address, sizeof(server_address));

    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    setsockopt(clientfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv));

    while (base < NUM_PACKETS) {
        // Send packets in window
        for (int i = base; i < NUM_PACKETS && i < base + WINDOW; i++) {
            if (!ackFrame[i]) {
                memset(buffer, 0, sizeof(buffer));
                sprintf(buffer, "%d", i);

                if (rand() % 100 >= LOSS_PROBABILITY) {
                    printf("Sending packet %d\n", i);
                    send(clientfd, buffer, sizeof(buffer), 0);
                } else {
                    printf("Frame %d lost during send\n", i);
                }
            }
        }

        // Try receiving ACKs for packets in window
        for (int i = base; i < NUM_PACKETS && i < base + WINDOW; i++) {
            if (!ackFrame[i]) {
                memset(buffer, 0, sizeof(buffer));
                int bytes = read(clientfd, buffer, sizeof(buffer));
                if (bytes <= 0) {
                    printf("Timeout: ACK for packet %d not received\n", i);
                } else {
                    int ack = atoi(buffer);
                    if (ack >= 0 && ack < NUM_PACKETS && !ackFrame[ack]) {
                        ackFrame[ack] = 1;
                        printf("Acknowledgement %d received\n", ack);
                    }
                }
            }
        }

        // Slide the window
        while (base < NUM_PACKETS && ackFrame[base]) {
            base++;
        }
    }

    close(clientfd);
    return 0;
}
