#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <vector>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <poll.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include "../lib/libconfpp/includes/libconfpp.h"

#define CONN_TIMEOUT 10
#define EVENT_TIMEOUT 100
#define BUFF_SIZE 1024

typedef enum ws_status {
    READY,
    PENDING,
    READING_BODY,
    BODY_READ
} ws_status;

class Request;
class SessionManager;

typedef struct ws_delivery {
    std::string delivery;
    std::string buffer;
    ws_status status;
    ssize_t left;
    size_t readbuff;
    Request *req;
} ws_delivery;

typedef struct ws_port {
    int nport;
    std::string server_name;
    int main_socket;
    std::vector<struct pollfd> conn_fds;
    std::vector<ws_delivery> responses;
    std::vector<ws_delivery> requests;
    std::vector<time_t> last_interaction;
    time_t req_timeout;
} ws_port;

class ws_connections {
private:
    std::vector<ws_port> ports;
    ws_config config;
    SessionManager *sessionManager;

    ws_port setup_socket(ws_config &config, int table_idx);
    void monitor_connections();
    void close_connection(unsigned int idx, unsigned int port_idx);
    bool pack_request(ws_delivery *delivery, ws_delivery *response, int nport);

public:
    ws_connections(ws_config &config, SessionManager *sessionManager);
    ws_connections() {}
    ws_connections& operator=(ws_connections &x);
    void accept_connections();
    void parse_and_serve(ws_delivery *request, ws_delivery *response, int nport);
};

#endif
