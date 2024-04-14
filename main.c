#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int readchk;

    // get the port from the user and check it works
    if (argc > 2) {
        printf("Only one argument is supported.");
        return -1;
    }

    int port = atoi(argv[1]);

    if (port == 0) {
        printf("Invalid port number.");
        return -1;
    }

    printf("port %s\n", argv[1]);

    //get the address info
    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE;

    int s = getaddrinfo(NULL, argv[1], &hints, &result);
    if (s != 0) {
        printf("error, could not get address info.");
        return -1;
    }

    //attempt to create a socket and bind it.
    int socketfd;
    int bindchk;
    struct addrinfo *rp;
    for ( rp = result; rp != NULL; rp = rp->ai_next) {
        socketfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (socketfd == -1) {
            continue;
        }

        bindchk = bind(socketfd, rp->ai_addr, rp->ai_addrlen);
        if (bindchk == 0) {
            break;
        }

        close(socketfd);

    }

    freeaddrinfo(result);

    if (socketfd == NULL){
        printf("Could not bind");
        return -1;
    }

    int listenchk;
    int acceptchk;
    socklen_t clientaddlen;
    struct sockaddr clientaddr;


    printf("started loot \n");
    // handle incomming connections
    for (;;) {

        printf("started recording \n");
        //started to listen
        listenchk = listen(socketfd, 32);
        if (listenchk != 0) {
            printf("could not listen \n");
            return -1;
        }

        printf("Listening for connection \n");

        //started to accept
        acceptchk = accept(socketfd, &clientaddr, &clientaddlen);
        if(acceptchk == -1){
            printf("couldn't accept client connection \n");
        }

        //buffer stuff
        printf("New fd: %d", acceptchk);
        char buffer[1024];
        readchk = read(acceptchk, buffer, sizeof(buffer));
        if (readchk == -1) {
            printf("error reading from client \n");
            return -1;
        }
        printf("Received message: %s\n", buffer);

        send(readchk, "Hello, world!", 13, 0);


    }

}