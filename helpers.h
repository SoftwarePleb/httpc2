//
// Created by Leo on 5/8/24.
//

#ifndef HTTP_HELPERS_H
#define HTTP_HELPERS_H

char* generateHttpResponse(char *httpResponse, char *title, char *body);
char* getFileExtension(char* fileName);
char* getMimeType(char * fileExt);
bool isBinaryFile(char *fileExt);

#endif //HTTP_HELPERS_H
