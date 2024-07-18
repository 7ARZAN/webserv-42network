#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <poll.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include "../lib/libconfpp/includes/libconfpp.h"

#define CONN_TIMEOUT 10			// in seconds

typedef enum ws_status {
	READY,
	PENDING
} ws_status;

typedef struct ws_delivery {
	std::string	delivery;
	std::string	buffer;
	ws_status	status;
} ws_delivery;

typedef struct ws_port{
	int				nport;				// port number
	std::string			server_name;			// server name <table name>
	int 				main_socket;			// main socket fd
	std::vector<struct pollfd>	conn_fds;
	std::vector<ws_delivery>	responses;
	std::vector<ws_delivery>	requests;
	std::vector<time_t>		last_interaction;
	time_t				req_timeout;
}ws_port;


class ws_connections{
	private :
		std::vector<ws_port>	ports;

		ws_port setup_socket(ws_config &config, int table_idx);
		void monitor_connections();
		void close_connection(unsigned int idx, unsigned int port_idx);
		bool pack_request(ws_delivery *delivery, ws_delivery *response, int sock_fd);
	public :
		ws_connections(ws_config &config);
		ws_connections();
		ws_connections& operator=(ws_connections &x);
		void accept_connections();
};

#endif
