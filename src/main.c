#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <regex.h>
#include <errno.h>
#include <stdbool.h>
#include "helpers.h"
#include "requests.h"


#define BAD_REQUEST "400 Bad Request"

void handleRequest(char* Message, int socketfd){

    // try to handle the request
    if(handle_get_request(Message, socketfd)){
        return;
    }
    if(hande_put_request(Message, socketfd)){
        return;
    }
    if(handle_post_request(Message, socketfd)){
        return;
    }
    if(handle_delete_request(Message, socketfd)){
        return;
    }

    //if we reach here then the message did not match the put, delete, post, or get
    printf("The request does not have a properly formatted header\n");
    char*  requestIncorrect = generateHttpResponse(BAD_REQUEST, "Bad request :(", "Bad Request");
    send(socketfd, requestIncorrect, strlen(requestIncorrect), 0);
    free(requestIncorrect);
    close(socketfd);
}

int main(int argc, char *argv[]) {
    int listenchk;
    int acceptchk;
    socklen_t clientAddrLen;
    struct sockaddr clientAddr;
    char buffer[1024];
    size_t readchk;

    // get the port from the user and check it works
    if (argc > 3) {
        printf("Expected two arguments port and root");
        return -1;
    }

    char* root = argv[2];

    if(chdir(root)!=0){
        printf("Couldn't access or find directory");
        return -1;
    }

    long port = atoi(argv[1]);

    if (port == 0) {
        printf("Invalid port number.");
        return -1;
    }

    printf("port %s\n", argv[1]);

    //get the address info
    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(hints)); hints.ai_family = AF_UNSPEC;
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

    if (result == NULL){
        printf("Could not bind");
        return -1;
    }

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
        acceptchk = accept(socketfd, &clientAddr, &clientAddrLen);
        if(acceptchk == -1){
            printf("couldn't accept client connection \n");
            printf("error code: %s \n", strerror(errno));
        }

        //buffer stuff
        printf("New fd: %d \n", acceptchk);
        readchk = read(acceptchk, buffer, sizeof(buffer));
        if (readchk == -1) {
            printf("error reading from client \n");
            fprintf(stderr, "printf failed!\n");
        }

        //handle http request
        handleRequest(buffer, acceptchk);

    }

}