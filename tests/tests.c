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

void testGenerateHttpResponse(){
//tests for helpers.h

    // Tests for generateHttpResponse
    // Test success response
    char* testSuccess = generateHttpResponse(SUCCESS, "Success Test Response", "Success Test Response");
    char* correctSuccess = "HTTP/1.0 200 Success\nContent-Length: 235\nContent-Type: text-html\n\n<!DOCTYPE html><html><head><title>Success Test Response</title></head><body><h1>Success Test Response</h1><p>Success Test Response</p></body></html>";
    assert(strcmp(testSuccess, correctSuccess)==0);

    char* test404 = generateHttpResponse(NOT_FOUND, "Test 404 Response", "Test 404 Response");
    char* correct404 = "HTTP/1.0 404 Not Found\nContent-Length: 221\nContent-Type: text-html\n\n<!DOCTYPE html><html><head><title>Test 404 Response</title></head><body><h1>Test 404 Response</h1><p>Test 404 Response</p></body></html>";
    assert(strcmp(test404, correct404)==0);

    char* test501 = generateHttpResponse(NOT_IMPLEMENTED, "Test 501 response", "Test 501 response");
    char* correct501 = "HTTP/1.0 501 Not Implemented\nContent-Length: 227\nContent-Type: text-html\n\n<!DOCTYPE html><html><head><title>Test 501 response</title></head><body><h1>Test 501 response</h1><p>Test 501 response</p></body></html>";
    assert(strcmp(test501, correct501)==0);

    char* test500 = generateHttpResponse(INTERNAL_SERVER_ERROR, "test 500 error", "test 500 error");
    char* correct500 = "HTTP/1.0 500 Internal Server Error\nContent-Length: 221\nContent-Type: text-html\n\n<!DOCTYPE html><html><head><title>test 500 error</title></head><body><h1>test 500 error</h1><p>test 500 error</p></body></html>";
    assert(strcmp(test500, correct500)==0);
}

void testGetFileExtension(){
    char* testExt = getFileExtension("File.jpg");
    char* correctExt = "jpg";
    assert(strcmp(testExt, correctExt) == 0);

    testExt = getFileExtension("File.JPG");
    correctExt = "jpg";
    assert(strcmp(testExt, correctExt) == 0);

    testExt = getFileExtension("FileFile.File.JPG");
    correctExt = "jpg";
    assert(strcmp(testExt, correctExt) == 0);

}

void  testGetMimeType(){
    char* fileExt = getMimeType("jpg");
    char* correctMime = "image/jpeg";
    assert(strcmp(fileExt, correctMime)==0);

    fileExt = getMimeType("sdfasdf");
    correctMime = NULL;
    assert(NULL == fileExt);

}

void testIsBinaryFile(){
    bool isBinaryTest  = isBinaryFile("html");
    bool isBinary = false;
    assert(isBinaryTest == isBinary);

    isBinaryTest  = isBinaryFile("jpg");
    isBinary = true;
    assert(isBinaryTest == isBinary);
}

void testToLower(){
    char* testString = toLower("ADS$");
    char* correctString = "ads$";
    assert(strcmp(testString, correctString) == 0);

    testString = toLower("AAA");
    correctString = "aaa";
    assert(strcmp(testString, correctString) == 0);
}

int main(int argc, char *argv[]) {
    //test helper functions.
    testGenerateHttpResponse();
    testGetFileExtension();
    testGetMimeType();
    testIsBinaryFile();
    testToLower();
    printf("wohoo all tests passed.");
    return 0;
}