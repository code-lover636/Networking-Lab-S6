#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, tf;

    printf("Enter the Total number of frames: ");
    scanf("%d", &tf);
    printf("Enter the Window Size: ");
    scanf("%d", &N);

    int i = 1;
    while (i <= tf) {
        int z = 0;
        for (int k = i; k < i + N && k <= tf; k++) {
            printf("Sending Frame %d...\n", k);
        }

        for (int k = i; k < i + N && k <= tf; k++) {
            int f = rand() % 2;
            if (!f) {
                printf("Acknowledgment for Frame %d...\n", k);
                z++;
            }
            else{
                printf("Timeout!! Frame Number : %d Not Received\n", k);
                printf("Retransmitting Window...\n");
                break;
            }
        }
        printf("\n");
        i = i + z;
    }

    printf("Successfully sent all frames\n");
    return 0;
}
