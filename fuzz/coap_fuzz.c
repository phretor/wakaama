#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdbool.h>
#include <strings.h>

#include "../core/er-coap-13/er-coap-13.h"

#define MAX_PKT_LEN 1024


size_t
read_bytes(uint8_t* buffer, FILE* s, size_t maxlen)
{
    int ch = EOF;
    size_t pos = 0; 

    while ((ch = fgetc(s)) != '\n' && ch != EOF && !feof(s) && pos < maxlen)
        buffer[pos++] = ch;

    return pos;
}


int main(int argc, char const* argv[])
{
    uint8_t * buffer;
    size_t length = read_bytes(buffer, stdin, MAX_PKT_LEN);

    static coap_packet_t message[1];
    static coap_packet_t response[1];

    coap_parse_message(message, buffer, (uint16_t)length);

    return 0;
}
