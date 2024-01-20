#include "iman.h"

void iman(char* token) 
{
   // website name
    char* website = "man.he.net";

    // DNS resolution
    struct hostent *host_info;

    host_info = gethostbyname(website);

    char *ip_address;

    struct in_addr addr;
    
    memcpy(&addr, host_info->h_addr_list[0], sizeof(struct in_addr));
    ip_address = inet_ntoa(addr);

    const char* PORT = "80";

    // Create a socket
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(website, PORT, &hints, &servinfo);

    // Connect to the server
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            continue;
        }
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            continue;
        }
        break;
    }

    freeaddrinfo(servinfo);

    // Send an HTTP GET request for the man page
    char request[1024];
    snprintf(request, sizeof(request), "GET /?topic=%s&section=all HTTP/1.1\r\nHOST: man.he.net\r\n\r\n", token);
    
    // send(sockfd, request, strlen(request), 0);
    if(send(sockfd, request, strlen(request), 0) == -1)
    {
        printf("No such command\n");
    }



    // Receive and print the response
    char buffer[4096];
    ssize_t bytes_received;
    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }


    // Close the socket
    close(sockfd);

    return;
}
