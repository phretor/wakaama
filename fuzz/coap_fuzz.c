#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>

#include "../core/er-coap-13/er-coap-13.h"

#define MAX_PKT_LEN 1024

size_t
read_bytes(uint8_t* buffer, FILE* s, size_t maxlen)
{
    size_t pos = 0; 

    while (!feof(s) && pos < maxlen) {
        fread((buffer + (pos++ * sizeof(uint8_t))), sizeof(uint8_t), 1, s);
    }

    pos--;

    //printf("%d bytes read \n", pos);

    return pos;
}


size_t
read_file(uint8_t* buffer, char const* fpath, size_t maxlen)
{
    //printf("Reading from %s\n", fpath);

    size_t pos = 0;
    FILE* fd;

    if ((fd = fopen(fpath, "rb")) != NULL) {
        pos = read_bytes(buffer, fd, maxlen);
        fclose(fd);
    }

    return pos;
}


int main(int argc, char const* argv[])
{
    uint8_t * buffer = (uint8_t *)malloc(MAX_PKT_LEN * sizeof(uint8_t));

    size_t length = read_file(buffer, argv[1], MAX_PKT_LEN);

    static coap_packet_t message[1];
    static coap_packet_t response[1];

    coap_parse_message(message, buffer, (uint16_t)length);

    return 0;
}
