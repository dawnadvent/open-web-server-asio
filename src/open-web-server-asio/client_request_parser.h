#ifndef CLIENT_REQUEST_PARSER_H
#define CLIENT_REQUEST_PARSER_H

#include <QByteArray>
#include "client_request.h"
#include <QStringRef>
#include <vector>

class ClientRequestParser
{
public:
    ClientRequestParser();
    static int parse(std::vector<char> &data, size_t bytes_transferred, ClientRequest &client_request);
    bool proccess_new_data(size_t bytes_transferred, ClientRequest &client_request);

    const int REQUEST_BUFFER_SIZE = 1024;
    std::vector<char> crlf_crlf {'\r', '\n', '\r', '\n'};
    std::vector<char> data_;
    QByteArray previous_request_data_;
    int parse2(std::vector<char> &data, size_t bytes_transferred, ClientRequest &client_request);
};

namespace enums {
enum http_parser_state {
    //GET /index.html HTTP/1.1
    start_state,
    state_GET,
    state_GET_URI_CONTENT,
    state_GET_URI_CONTENT_END,

    state_HTTP_VERSION,

    state_CRLF,
    state_CRLF_x2,

    //Host: localhost:12343
    state_HOST,
    state_HOST_CONTENT,
    state_HOST_CONTENT_END,

    state_CONNECTION,
    state_CONNECTION_KEEP_ALIVE_OR_CLOSE,

    state_UNKNOWN_HEADER,


    //Range: bytes=0-1023
    state_RANGE_R,
    state_RANGE_A,
    state_RANGE_N,
    state_RANGE_G,
    state_RANGE_E,
    state_RANGE_COLON,
    state_RANGE_BYTES_B,
    state_RANGE_BYTES_Y,
    state_RANGE_BYTES_T,
    state_RANGE_BYTES_E,
    state_RANGE_BYTES_S,
    state_RANGE_BYTES_EQUALS,
    state_RANGE_BYTES_EQUALS_FROM,
    state_RANGE_BYTES_EQUALS_FROM_END,
    state_RANGE_BYTES_EQUALS_FROM_DASH,
    state_RANGE_BYTES_EQUALS_UNTIL,
    state_RANGE_BYTES_EQUALS_UNTIL_END
};
}

#endif // CLIENT_REQUEST_PARSER_H
