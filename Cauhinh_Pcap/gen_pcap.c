#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pcap/pcap.h>

// Định nghĩa các header của file pcapng
#define PCAP_MAGIC_NUMBER 0xa1b2c3d4
#define PCAP_VERSION_MAJOR 2
#define PCAP_VERSION_MINOR 4
#define PCAP_LINKTYPE_ETHERNET 1

typedef struct pcap_hdr_s {
    uint32_t magic_number;   /* magic number */
    uint16_t version_major;  /* major version number */
    uint16_t version_minor;  /* minor version number */
    int32_t  thiszone;       /* GMT to local correction */
    uint32_t sigfigs;        /* accuracy of timestamps */
    uint32_t snaplen;        /* max length of captured packets, in octets */
    uint32_t network;        /* data link type */
} pcap_hdr_t;

typedef struct pcaprec_hdr_s {
    uint32_t ts_sec;         /* timestamp seconds */
    uint32_t ts_usec;        /* timestamp microseconds */
    uint32_t incl_len;       /* number of octets of packet saved in file */
    uint32_t orig_len;       /* actual length of packet */
} pcaprec_hdr_t;

void create_hdr_pcap(FILE *fp) // ham tao header file
{
    pcap_hdr_t file_header;
    file_header.magic_number = PCAP_MAGIC_NUMBER;
    file_header.version_major = PCAP_VERSION_MAJOR;
    file_header.version_minor = PCAP_VERSION_MINOR;
    file_header.thiszone = 0;
    file_header.sigfigs = 0;
    file_header.snaplen = 65535;
    file_header.network = PCAP_LINKTYPE_ETHERNET;
    fwrite(&file_header, sizeof(pcap_hdr_t), 1, fp);
}

void create_data_pseudo(uint32_t length, uint32_t ts ,FILE *fp)
{
    // Tạo một gói tin giả từ dữ liệu cho sẵn
    pcaprec_hdr_t packet_header;
    packet_header.ts_sec = ts; // Thời gian timestamp, thoi gian goi tin bat duoc
    packet_header.ts_usec = ts;
    packet_header.incl_len = length; // Độ dài của gói tin
    packet_header.orig_len = length;

    fwrite(&packet_header, sizeof(pcaprec_hdr_t), 1, fp); 
}

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
    FILE *fw = fopen("cauhinh.pcap", "wb");
    if (fw == NULL) {
        perror("fopen");
        return 1;
    }
    FILE *fr = fopen("test.txt","r");
    if(fr == NULL)
    {
        printf("Lam gi co file dau vao??\n");
    }

    char str[1000],*str1,str2[100][1000]; int temp = 0 ;
    uint8_t output[50], mem[50][50],mem_len[50]; size_t outputLength;

    fgets(str,sizeof(str),fr);
    str1 = strtok(str,"\"X_,");
    while(str1 != NULL)
    {
        strcpy(str2[temp], str1);
        str1 = strtok(NULL,"\"X_,");
        temp++;
    }
    
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

    create_hdr_pcap(fw);
    // printf("%ld\n",sizeof(pcap_hdr_t));
    create_data_pseudo(dodai,2,fw);

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
        // printf("0x%x ", packet_data[i]);
    }
    // printf("%d \n",dodai);

    // uint8_t b = 0x01;
    // uint8_t packet_data[42] = 
    // {
    //     0x00, 0x00, 0x00, 0x00, 0x19, 0x59, 0x84, 0x78,
    //     0x01, 0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88,
    //     0x04, 0x01, 0x00, 0x02, 0x00, 0x00, 0x01, 0x00,
    //     0x01, 0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88,
    //     0x00, 0x00, 0x00, 0x00, 0x19, 0x59, 0x84, 0x78,
    //     01, 0x3F
    // };

    fwrite(packet_data, sizeof(packet_data), 1, fw);
    // printf("%ld \n",sizeof(packet_data));
    // printf("%x \n",packet_data[0]);

    fclose(fw); fclose(fr);
    printf("File .pcapng đã được tạo thành công!\n");

    return 0;
}
