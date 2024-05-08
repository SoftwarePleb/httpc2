//
// Created by Leo on 5/8/24.
//

#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <slcurses.h>
#include <regex.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include "helpers.h"

#define REGEX_GROUP_COUNT 3
#define SUCCESS "200 Success"
#define NOT_FOUND "404 Not Found"
#define NOT_IMPLEMENTED "501 Not Implemented"
#define INTERNAL_SERVER_ERROR "500 Internal Server Error"
#define BAD_REQUEST "400 Bad Request"

bool handle_get_request(char *Message, int socketfd){
    regex_t regex;
    regmatch_t pmatch[REGEX_GROUP_COUNT];
    char *getRegex = "^GET \\/([^ ]*) HTTP\\/[0-9]\\.[0-9]\r\n";
    if (regcomp(&regex, getRegex, REG_EXTENDED) == 0 && regexec(&regex, Message, 3, pmatch, 0) == 0) {

        if(pmatch[1].rm_eo == pmatch[1].rm_so){
            printf("we got a valid get but it didn't have a resource");
            char* responseSuccess = generateHttpResponse(SUCCESS, "Successful Connection", "You successfully connected you didn't give a resource url");
            send(socketfd, responseSuccess, strlen(responseSuccess), 0);
            free(responseSuccess);
            close(socketfd);
            return true;
        }

        FILE* file;
        int start = pmatch[1].rm_so;
        int length = pmatch[1].rm_eo;
        char fileName[length - start + 1];
        memcpy(fileName, &Message[start], length - start);
        fileName[length - start] = '\0';
        printf("filename: %s\n", fileName);

        char* fileExt = getFileExtension(fileName);
        printf("fileExtension: %s\n", fileExt);

        bool isBinary = isBinaryFile(fileExt);
        if(isBinary){
            file = fopen(fileName, "rb");
        } else{
            file = fopen(fileName, "r");
        }

        if(file == NULL){
            printf("File Not Found");
            char* URLNotFound = generateHttpResponse(NOT_FOUND, "Couldn't find the file :(", "Couldn't find the file :(");
            send(socketfd, URLNotFound, strlen(URLNotFound), 0);
            free(URLNotFound);
            close(socketfd);
            return true;
        }

        printf("string test");
        fseek(file, 0, SEEK_END);
        size_t fsize = ftell(file);
        fseek(file, 0, SEEK_SET);
        char *fileContent = malloc(fsize);
        size_t bytesRead = fread(fileContent, fsize, 1, file);
        if (bytesRead==0){
            printf("error\n");
            char* internalServerError = generateHttpResponse(INTERNAL_SERVER_ERROR, "Interal Server Error", "Internal Server Error");
            send(socketfd, internalServerError, strlen(internalServerError), 0);
            free(internalServerError);
            return true;
        }
        fclose(file);

        printf("Found file \n");
        printf("file is: %s \n", fileContent);
        printf("The request is a valid GET request\n");

        char headerFormat[100];

        size_t total = sizeof(headerFormat) + fsize;

        char* mime = getMimeType(fileExt);

        sprintf(headerFormat, "HTTP/1.0 200 OK\nContent-Length: %zu\nContent-Type: %s\n\n", total, mime);

        char *response = malloc(fsize + strlen(headerFormat) * sizeof(char *));

        memcpy(response, headerFormat, strlen(headerFormat) + 1);
        memcpy(response + strlen(headerFormat), fileContent, fsize);
        if (send(socketfd, response, strlen(headerFormat)+fsize, 0)==-1){
            printf("sad :(\n");
            int errnum = errno;
            fprintf(stderr, "Value of errno: %d\n", errno);
            fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
        }
        close(socketfd);
        free(response);
        return true;
    }
    return false;

}

bool handle_delete_request(char *Message, int socketfd){
    regex_t regex;
    regmatch_t pmatch[REGEX_GROUP_COUNT];
    char *deleteRegex = "^DELETE \\/([^ ]*) HTTP\\/[0-9]\\.[0-9]\r\n";
    if (regcomp(&regex, deleteRegex, REG_EXTENDED) == 0 && regexec(&regex, Message, 3, pmatch, 0) == 0) {
        printf("The request is a valid POST request\n");
        char* notImplemented = generateHttpResponse(NOT_IMPLEMENTED, "Delete Requests are not implemented.", "Delete Requests are not implemented.");
        send(socketfd, notImplemented, strlen(notImplemented), 0);
        free(notImplemented);
        close(socketfd);
        return true;
    }
    return false;
}

bool hande_put_request(char *Message, int socketfd){
    regex_t regex;
    regmatch_t pmatch[REGEX_GROUP_COUNT];
    char *putRegex = "^PUT \\/([^ ]*) HTTP\\/[0-9]\\.[0-9]\r\n";
    if (regcomp(&regex, putRegex, REG_EXTENDED) == 0 && regexec(&regex, Message, 3, pmatch, 0) == 0) {
        printf("The request is a valid POST request\n");
        char* notImplemented = generateHttpResponse(NOT_IMPLEMENTED, "PUT Requests are not implemented.", "PUT Requests are not implemented.");
        send(socketfd, notImplemented, strlen(notImplemented), 0);
        free(notImplemented);
        close(socketfd);
        return true;
    }
    return false;
}


bool handle_post_request(char *Message, int socketfd){
    regex_t regex;
    regmatch_t pmatch[REGEX_GROUP_COUNT];
    char *postRegex = "^POST \\/([^ ]*) HTTP\\/[0-9]\\.[0-9]\r\n";
    if (regcomp(&regex, postRegex, REG_EXTENDED) == 0 && regexec(&regex, Message, 3, pmatch, 0) == 0) {
        printf("The request is a valid POST request\n");
        char* notImplemented = generateHttpResponse(NOT_IMPLEMENTED, "Post Requests are not implemented.", "Post Requests are not implemented.");
        send(socketfd, notImplemented, strlen(notImplemented), 0);
        free(notImplemented);
        close(socketfd);
        return true;
    }
    return false;
}

