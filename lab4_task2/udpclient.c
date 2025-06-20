#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 9090

int main() {
    int sockfd;
    char buffer[1024] = {0};
    char *message = "👋 Hello from UDP Client";
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server info
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost

    // Send message to server
    sendto(sockfd, message, strlen(message), 0,
           (const struct sockaddr *) &server_addr, addr_len);
    printf("📤 Client sent message: %s\n", message);

    // Receive response from server
    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *) &server_addr, &addr_len);
    printf("📩 Client received: %s\n", buffer);

    close(sockfd);
    return 0;
}
