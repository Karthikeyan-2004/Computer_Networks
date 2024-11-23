#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    int number;
    long result;
    socklen_t addr_len = sizeof(server_addr);

    // Creating socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    // Filling server information
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Input number from user
    printf("Enter a number to calculate factorial: ");
    scanf("%d", &number);

    // Send number to server
    sendto(sockfd, &number, sizeof(number), 0, (const struct sockaddr *)&server_addr, addr_len);

    // Receive result from server
    recvfrom(sockfd, &result, sizeof(result), 0, (struct sockaddr *)&server_addr, &addr_len);
    printf("Factorial of %d is: %ld\n", number, result);

    close(sockfd);
    return 0;
}

