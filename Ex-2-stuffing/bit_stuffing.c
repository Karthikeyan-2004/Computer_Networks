#include <stdio.h>
#include <string.h>

void bitStuffing(char *input, char *output) {
    int i, j = 0;
    int consecutiveOnes = 0;

    for (i = 0; i < strlen(input); i++) {
        output[j++] = input[i];

        if (input[i] == '1') {
            consecutiveOnes++;
            if (consecutiveOnes == 5) { // Insert '0' after five consecutive '1's
                output[j++] = '0';
                consecutiveOnes = 0;
            }
        } else {
            consecutiveOnes = 0;
        }
    }
    output[j] = '\0';
}

int main() {
    char input[100], output[200];
    printf("Enter the binary data: ");
    scanf("%s", input);

    bitStuffing(input, output);

    printf("Data after bit stuffing: %s\n", output);
    return 0;
}

