#include <stdio.h>
#include <string.h>

#define FLAG 'F'
#define ESC 'E'

void byteStuffing(char *input, char *output) {
    int i, j = 0;
    
    // Start with the FLAG character
    output[j++] = FLAG;
    
    for (i = 0; i < strlen(input); i++) {
        if (input[i] == FLAG || input[i] == ESC) {
            output[j++] = ESC; // Insert ESC before FLAG or ESC in data
        }
        output[j++] = input[i];
    }
    
    // End with the FLAG character
    output[j++] = FLAG;
    output[j] = '\0';
}

int main() {
    char input[100], output[200];
    printf("Enter the frame data: ");
    scanf("%s", input);

    byteStuffing(input, output);

    printf("Data after byte stuffing: %s\n", output);
    return 0;
}

