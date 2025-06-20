#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char *msg = "Hello from Client 1";

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);  // change to Server IP
  
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    send(sock, msg, strlen(msg), 0);
    read(sock, buffer, 1024);
    printf("Client received: %s\n", buffer);
    close(sock);
    return 0;
}
