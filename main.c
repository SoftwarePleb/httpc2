#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <regex.h>
#include <errno.h>

char* readHttpRequest(char* Message, int MessangeLength){

    printf("%.*s\n", (int)MessangeLength, Message);
    char* headerRegex = "GET \\/ HTTP\\/[0-9].[0-9]";


    regex_t regex;
    regmatch_t pmatch[1];
    if(regcomp(&regex, headerRegex, 0)!=0){
        printf("Error, coulnd't compile expression");
    }

    int regexcheck = regexec(&regex, Message, 0, NULL, 0);

    if(regexcheck == 0){
        printf("foudnd ya");
    }

    if(regexcheck == REG_NOMATCH){
        printf("error didn't find string");
    }

    return headerRegex;

}

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

    if (result == NULL){
        printf("Could not bind");
        return -1;
    }

    int listenchk;
    int acceptchk;
    socklen_t clientaddlen;
    struct sockaddr clientaddr;
    char buffer[1024];
    char testResponse[] = "HTTP/1.1 200 OK\nContent-Length: 12\nContent-Type: text-html\n\nHello World!";
    printf("TestRes: %s", testResponse);
    int testResponselen = strlen(testResponse);
    char* testHttpParser;


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
        printf("New fd: %d \n", acceptchk);
        readchk = read(acceptchk, buffer, sizeof(buffer));
        if (readchk == -1) {
            printf("error reading from client \n");
        }

        testHttpParser = readHttpRequest(buffer, readchk);

        printf("\n");

        send(acceptchk, testResponse, testResponselen, 0);


        printf("\n");

        close(readchk);


    }

}