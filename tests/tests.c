//
// Created by Leo on 5/9/24.
//
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../src/helpers.h"
#include "../src/requests.h"

#define SUCCESS "200 Success"
#define NOT_FOUND "404 Not Found"
#define NOT_IMPLEMENTED "501 Not Implemented"
#define INTERNAL_SERVER_ERROR "500 Internal Server Error"

int main(int argc, char *argv[]) {

    //tests for helpers
    char* testSuccess = generateHttpResponse(SUCCESS, "Success Test Response", "Success Test Response");
         "HTTP/1.0 200 Success\nContent-Length: 234\nContent-Type: text-html\n\n"
                         "<!DOCTYPE html><html><head><title>%s</title></head>"
                         "<body><h1>%s</h1><p>%s</p></body></html>";

    char* correctSuccess = "HTTP/1.0 200 Success\nContent-Length: 234\nContent-Type: text-html\n\n<!DOCTYPE html><html><head><title>Success Test Response</title></head><body><h1>Success Test Response</h1><p>Success Test Response</p></body></html>";


    printf("%s\n", testSuccess);
    printf("%s\n", correctSuccess);

    printf("test %d\n", strcmp(testSuccess, correctSuccess)==0);

    assert(strcmp(testSuccess, correctSuccess)==0);


    printf("%s\n", testSuccess);
    //assert(testSuccess, );

    //assert();
    return 0;


}