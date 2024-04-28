#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <regex.h>
#include <errno.h>

void readHttpRequest(char* Message, int MessangeLength, int socketfd){

    //prepare statements

    char responseSuccess[] = "HTTP/1.0 200 OK\nContent-Length: 12\nContent-Type: text-html\n\nHello World!";
    int responseSuccessLen = strlen(responseSuccess);

    char requestIncorrect[] = "HTTP/1.0 400 Bad Request\nContent-Length: 12\nContent-Type: text-html\n\nBad Request";
    int requestIncorrectLen = strlen(requestIncorrect);

    char URLNotFound[] = "HTTP/1.0 404 Not Found\nContent-Length: 12\nContent-Type: text-html\n\nNot Found";
    int URLNotFoundLen = strlen(URLNotFound);

    char InternalError[] = "HTTP/1.0 500 Internal Server Error\nContent-Length: 12\nContent-Type: text-html\n\n500 Internal Server Error";
    int InternalErrorLen = strlen(InternalError);

    char NotImplemented[] = "HTTP/1.0 501 Not Implemented\nContent-Length: 12\nContent-Type: text-html\n\nNot Implemented";
    int NotImplementedLen = strlen(NotImplemented);


    // check that the header is correctly formed.
    printf("%.*s\n", (int)MessangeLength, Message);
    regex_t regex;

    // Check for POST, PUT and DELETE request.
    char *postRegex = "POST \\/ HTTP\\/[0-9].[0-9]";
    char *putRegex = "PUT \\/ HTTP\\/[0-9].[0-9]";
    char *deleteRegex = "DELETE \\/ HTTP\\/[0-9].[0-9]";
    char *getRegex = "GET \\/ HTTP\\/[0-9].[0-9]";

    if (regcomp(&regex, getRegex, 0) == 0 && regexec(&regex, Message, 0, NULL, 0) == 0) {
        printf("The request is a valid GET request\n");
        send(socketfd, responseSuccess, responseSuccessLen, 0);
        return;
    }

    if (regcomp(&regex, postRegex, 0) == 0 && regexec(&regex, Message, 0, NULL, 0) == 0) {
        printf("The request is a valid POST request\n");
        send(socketfd, NotImplemented, NotImplementedLen, 0);
        return;
    }

    if (regcomp(&regex, putRegex, 0) == 0 && regexec(&regex, Message, 0, NULL, 0) == 0) {
        printf("The request is a valid PUT request\n");
        send(socketfd, NotImplemented, NotImplementedLen, 0);
        return;

    }

    if (regcomp(&regex, deleteRegex, 0) == 0 && regexec(&regex, Message, 0, NULL, 0) == 0) {
        printf("The request is a valid Delete request\n");
        send(socketfd, NotImplemented, NotImplementedLen, 0);
        return;
    }

    //if we reach here then the request is not correctly formatted
    printf("The request does not have a properly formatted header\n");
    send(socketfd, requestIncorrect, requestIncorrectLen, 0);
    close(socketfd);
}



int main(int argc, char *argv[]) {
    int listenchk;
    int acceptchk;
    socklen_t clientAddrLen;
    struct sockaddr clientAddr;
    char buffer[1024];

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
            fprintf(stderr, "printf failed!\n");;
        }

        //handle http request
        readHttpRequest(buffer, readchk, acceptchk);

    }

}