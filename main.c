#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argv<2){
        printf("Please provide a port number.");
    }

    int port = atoi(argv[1]);
    printf("Port: %d", port);

    return 0;
}