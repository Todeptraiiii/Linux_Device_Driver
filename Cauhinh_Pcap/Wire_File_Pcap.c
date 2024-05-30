#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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

int main() 
{
    FILE *fp = fopen("output.pcap", "wb");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }
    create_hdr_pcap(fp);
    // printf("%ld\n",sizeof(pcap_hdr_t));
    create_data_pseudo(42,2,fp);

    uint8_t packet_data[42] = 
    {
        0x00, 0x00, 0x00, 0x00, 0x19, 0x59, 0x84, 0x78,
        0x01, 0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88,
        0x04, 0x01, 0x00, 0x02, 0x00, 0x00, 0x01, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88,
        0x00, 0x00, 0x00, 0x00, 0x19, 0x59, 0x84, 0x78,
        0x01, 0x00
    };

    fwrite(packet_data, sizeof(packet_data), 1, fp);
    // printf("%ld \n",sizeof(packet_data));

    fclose(fp);
    printf("File .pcapng đã được tạo thành công!\n");

    return 0;
}
