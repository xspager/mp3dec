#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lookup.h"

typedef struct {
    uint8_t version;
    uint8_t layer;
    uint8_t crc;
    int16_t bitrate;
    int32_t frequency;
    uint8_t mode;
    uint8_t mode_extension;
} meta;

int main(int argc, char *argv[])
{
    char *filename;
    FILE *file;
    union {
        uint8_t bytes[4];
        uint16_t words[2];
        uint32_t header;
    } buffer;
    int bytes_read;
    meta metadata;

    if(argc < 2) {
        printf("MP3 file name missing\n");
        exit(1);
    }
    filename = argv[1];

    file = fopen(filename, "rb");
    if(!file) {
        printf("can't open file %s\n", filename);
        exit(1);
    }
    
    do {
        bytes_read = fread(&buffer.header, sizeof(buffer.header), 1, file);

        // syncword has three all one nibbles: FF F0 00 00
        if((buffer.header & 0x0000F0FF) == 0x0000F0FF) {
            metadata.version = buffer.bytes[1] & 0x8 >> 3; // 0000 1000
            metadata.layer = (buffer.bytes[1] & 0x6) >> 1; // 0000 0110
            metadata.crc = buffer.bytes[1] & 0x1; // 0000 0001
            metadata.bitrate = bitrates[(buffer.bytes[2] & 0xF0) >> 4]; // 1111 0000
            metadata.frequency = frequencies[(buffer.bytes[2] & 0x06) >> 2]; // 0000 1100 
            metadata.mode = buffer.bytes[3] & 0xC0 >> 6; // 1100 0000
            metadata.mode_extension = (buffer.bytes[3] & 0x30) >> 4; // 0011 0000
            break;
        }
    } while(bytes_read > 0);

    if(metadata.version == 1 && metadata.layer == 1) {
        printf("version: %s\n", metadata.version ? "v1":"v2");
        printf("layer: %s\n", layers[metadata.layer]);
        printf("CRC: %s\n", metadata.crc ? "yes": "no");
        printf("bitrate: %i kbps\n", metadata.bitrate);
        printf("frequency: %i kHz\n", metadata.frequency / 1000);
        printf("mode: %s\n", modes[metadata.mode]);
        printf("mode extension: %s %s\n", 
            mode_extensions[metadata.mode_extension][0] ? "Intensity stereo" : "",
            mode_extensions[metadata.mode_extension][1] ? "MS stereo" : ""
        );
    } else
        printf("Not a MP3 file\n");

    fclose(file);

    return 0;
}
