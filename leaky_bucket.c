#include <stdio.h>
#include <stdlib.h>

#define NUM_PACKETS 10
#define BUCKET_CAPACITY 20
#define LEAK_RATE 2

int main(){
    int packet, bucket = 0;
    for(int i=0; i<NUM_PACKETS; i++){
        packet = rand() % 6;
        sleep(1);

        if((packet + bucket) <= BUCKET_CAPACITY){
            printf("Adding %d packet to bucket\n", packet);
            bucket += packet;
        }
        else{
            printf("Overflow!!! Dropping %d packets.\n", (bucket + packet) - BUCKET_CAPACITY);
        }

        //leak
        if(bucket >= LEAK_RATE){
            printf("Leaking %d packets\n", LEAK_RATE);
            bucket -= LEAK_RATE;
        } else{
            printf("Leaking %d packets\n", bucket);
            bucket = 0;
        }

        printf("Current bucket size: %d\n", bucket);
    }
}

