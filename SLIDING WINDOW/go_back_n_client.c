#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8087
#define NUM_PACKETS 10
#define WINDOW 5
#define LOSS_PROBABILITY 50

int main() {
    struct sockaddr_in server_address;
    char buffer[40];
    int base = 0, next_seq_num = 0;

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
        // Send all packets in the window
        for (int i = base; i < NUM_PACKETS && i < base + WINDOW; i++) {
            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "%d", i);

            if (rand() % 100 >= LOSS_PROBABILITY) {
                printf("Sending packet %d\n", i);
                send(clientfd, buffer, sizeof(buffer), 0);
            } else {
                printf("Packet %d lost during send\n", i);
            }
        }

        // Wait for ACK of base
        memset(buffer, 0, sizeof(buffer));
        int bytes = read(clientfd, buffer, sizeof(buffer));
        if (bytes <= 0) {
            printf("Timeout: ACK for packet %d not received. Resending window...\n", base);
            // Go back and resend all packets from base in next iteration
        } else {
            int ack = atoi(buffer);
            if (ack == base) {
                printf("Acknowledgement %d received\n", ack);
                base++;
            } else {
                printf("Out-of-order ACK %d received (ignored in GBN)\n", ack);
            }
        }
    }

    close(clientfd);
    return 0;
}
