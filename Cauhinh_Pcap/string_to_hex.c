#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void hexStringToUint8Array(const char *hexString, uint8_t *outputArray, size_t *outputLength) 
{
    // Bo qua tien to 0x neu co
    if (hexString[0] == '0' && (hexString[1] == 'x' || hexString[1] == 'X')) 
    {
        hexString += 2;
    }

    size_t hexLength = strlen(hexString);
    *outputLength = hexLength / 2;

    for (size_t i = 0; i < *outputLength; i++) 
    {
        char hexByte[3] = { hexString[2 * i], hexString[2 * i + 1], '\0' };
        outputArray[i] = (uint8_t)strtol(hexByte, NULL, 16);
    }
}

int main() {
    char input[] = "0000008888882f";
    uint8_t output[255];
    size_t outputLength;

    hexStringToUint8Array(input, output, &outputLength);

    // In kết quả
    printf("Chuỗi gốc: %s\n", input);
    printf("Mảng uint8_t: ");
    for (size_t i = 0; i < outputLength; i++) {
        printf("%02X ", output[i]);
    }
    printf("\n");

    return 0;
}
