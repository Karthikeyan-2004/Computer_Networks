#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

long factorial(int num) {
    long fact = 1;
    for (int i = 1; i <= num; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    int client_len = sizeof(client_addr);
    int number;
    long result;

    // Creating socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Filling server information
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Server is waiting for a number...\n");

    // Receive number from client
    recvfrom(sockfd, &number, sizeof(number), 0, (struct sockaddr *)&client_addr, &client_len);
    printf("Received number: %d\n", number);

    // Calculate factorial
    result = factorial(number);

    // Send result back to client
    sendto(sockfd, &result, sizeof(result), 0, (struct sockaddr *)&client_addr, client_len);
    printf("Factorial of %d sent back to client: %ld\n", number, result);

    close(sockfd);
    return 0;
}

