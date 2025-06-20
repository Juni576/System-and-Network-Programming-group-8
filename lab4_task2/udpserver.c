#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 9090

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Zero out the server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // Server information
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    server_addr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("🟢 UDP Server is listening on port %d...\n", PORT);

    // Wait to receive a message
    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *) &client_addr, &addr_len);
    printf("📥 Server received: %s\n", buffer);

    // Send response back to client
    char *response = "✅ Hello from UDP Server";
    sendto(sockfd, response, strlen(response), 0,
           (const struct sockaddr *) &client_addr, addr_len);
    printf("📤 Server sent response to client.\n");

    close(sockfd);
    return 0;
}
