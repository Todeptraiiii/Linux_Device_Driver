#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

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

int main()
{
    FILE *fr;
    char str[1000],*str1,str2[50][1000]; int temp = 0 ;
    uint8_t output[50], mem[50][50],mem_len[50]; size_t outputLength;
    

    fr = fopen("test.txt","r");
    if(fr == NULL)
    {
        printf("Lam gi co file dau vao??\n");
    }

    fgets(str,sizeof(str),fr);
    // printf("%s \n",str);
    str1 = strtok(str,"\"Xx_, ");
    while(str1 != NULL)
    {
        strcpy(str2[temp], str1);
        // printf("%s \n",str1);
        str1 = strtok(NULL,"\"Xx_, ");
        
        temp++;
    }
    //Debug
        printf("%d \n",temp);
    for(int i = 0 ; i < temp ; i ++)
    {
        // printf("%s \n",str2[i]);
    }
    //
    for (int i = 0 ; i < temp ; i ++) // luu tru mang
    {
        hexStringToUint8Array(str2[i], output, &outputLength);
        for(int j = 0 ; j < outputLength ; j ++)
        {
            mem[i][j] = output[j];
        }
            mem_len[i] = outputLength;

    }
    // tinh do dai du lieu
    uint32_t dodai = 0, index = 0;
    for(int i = 0 ; i < temp ; i ++)
    {
        dodai = dodai + mem_len[i];
    }
    printf("%d\n",dodai);
    // data pcap
    uint8_t packet_data[dodai];

    for(int i = 0 ; i < temp; i ++)
    {
        for(int j = 0 ; j < mem_len[i]; j ++)
        {
            // printf("0x%x ", mem[i][j]);
            packet_data[index++] = mem[i][j];
        }
    }
    for(int i = 0 ; i < dodai; i ++)
    {
        printf("0x%x ", packet_data[i]);
    }
    fclose(fr);


}