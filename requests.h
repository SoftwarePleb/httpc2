//
// Created by Leo on 5/8/24.
//

#ifndef HTTP_REQUESTS_H
#define HTTP_REQUESTS_H


#include <stdbool.h>

bool handle_get_request(char *Message, int socketfd);
bool handle_delete_request(char *Message, int socketfd);
bool hande_put_request(char *Message, int socketfd);
bool handle_post_request(char *Message, int socketfd);


#endif //HTTP_REQUESTS_H
