//
// Created by Leo on 5/8/24.
//

#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include <regex.h>
#include <stdbool.h>
#include <ctype.h>

char* generateHttpResponse(char *http_response, char *title, char *body){
    const char* htmlTemplate = "HTTP/1.0 %s\nContent-Length: %d\nContent-Type: text-html\n\n"
                               "<!DOCTYPE html><html><head><title>%s</title></head>"
                               "<body><h1>%s</h1><p>%s</p></body></html>";
    size_t htmlSize = strlen(htmlTemplate) - 8 + strlen(http_response) + 2 * strlen(title) + strlen(body) + 1;

    size_t total = htmlSize + strlen(body);
    char *html = malloc(htmlSize);
    sprintf(html, htmlTemplate, http_response, total, title, title, body);
    return html;
}


char* getFileExtension(char* fileName){
    regex_t fileExtensionRegex;
    const char* FILE_EXTENSION_REGEX = "([^.]*)$";
    int numGroup = 2;
    regmatch_t fileExtensionMatches[2];

    if (regcomp(&fileExtensionRegex, FILE_EXTENSION_REGEX, REG_EXTENDED) !=0){
        // This really shouldn't happen.
        return NULL;
    }

    if (regexec(&fileExtensionRegex, fileName, numGroup, fileExtensionMatches, 0) != 0){
        // no matches :(
        return NULL;
    }

    int startOfMatch = fileExtensionMatches[1].rm_so;
    int endOfMatch = fileExtensionMatches[1].rm_eo;
    char* fileExt = malloc((endOfMatch-startOfMatch) * sizeof(char *));
    if(fileExt == NULL){
        regfree(&fileExtensionRegex);
        return NULL;
    }
    strcpy(fileExt, &fileName[startOfMatch]);
    regfree(&fileExtensionRegex);
    return fileExt;
}

char* getMimeType(char* fileExt){
    if (strcmp(fileExt, "js")==0){
        return "text/javascript";
    }
    if(strcmp(fileExt, "html")==0){
        return "text/html";
    }
    if(strcmp(fileExt, "css")==0){
        return "text/css";
    }
    if(strcmp(fileExt, "mp3")==0){
        return "audio/mpeg";
    }
    if(strcmp(fileExt, "jpg")==0){
        return "image/jpeg";
    }
    if(strcmp(fileExt, "svg")==0){
        return "image/svg";
    }
    if(strcmp(fileExt, "ico")==0){
        return "image/x/icon";
    }
    return NULL;
}

bool isBinaryFile(char* fileExt){
    if(strcmp(fileExt, "mp3")==0){
        return true;
    }
    if(strcmp(fileExt, "jpg")==0){
        return true;
    }
    if(strcmp(fileExt, "jepg")==0){
        return true;
    }
    if(strcmp(fileExt, "svg")==0){
        return true;
    }
    return false;
}


