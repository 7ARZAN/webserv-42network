#include "../includes/webserver.hpp"
#include <string.h>
#include "../includes/connection.hpp"
#include "../includes/RequestParsing.hpp"
#include "../includes/Response.hpp"



void	init_socket(ws_port &cport, std::string port){
	// registering port number, cause we will need this
	cport.nport = atoi(port.c_str());
	if (cport.nport > 0xffff || cport.nport < 1)
		throw (std::range_error("port out of bounds"));
	// creating a main socket for the port
	cport.main_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (cport.main_socket < 0)
		throw (std::runtime_error("can't create a socket"));

	// setting the socket to be non blocking, we need to get as much conections as we need
	if (fcntl(cport.main_socket, F_SETFL, fcntl(cport.main_socket, F_GETFL, 0) | O_NONBLOCK) < 0)
		throw (std::runtime_error("the socket cant be non blocking"));
}

void socket_listen(ws_port &cport, ws_config &config, int table_idx){
	struct sockaddr_in 	address;
	unsigned int		maxconn_n;				// number of max connections

	// binding our socket to the port
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(cport.nport);
	if (bind(cport.main_socket, (struct sockaddr *) &address, sizeof(address)) < 0)
		throw std::runtime_error("can't bind socket with port " + std::to_string(cport.nport));

	maxconn_n = SOMAXCONN;
	std::string max_connections = config.search_val(config[table_idx]->table_name, "max_connections");
	if (max_connections != "") {
		maxconn_n = atoi(max_connections.c_str());
		if (maxconn_n > SOMAXCONN || maxconn_n < 1)
			throw (std::runtime_error("unvalid max connections for port " 
				+ std::to_string(cport.nport)));
	}

	if (listen(cport.main_socket, maxconn_n) < 0)
		throw (std::runtime_error("can't listen to port" + std::to_string(cport.nport)));


}

ws_port ws_connections::setup_socket(ws_config &config, int table_idx){
	ws_port			cport;

	try {
		// if (config.search_val(config[table_idx]->table_name, "port").empty()){
		// 	cport.nport = -1;
		// 	return cport;
		// }
		init_socket(cport, config.search_val(config[table_idx]->table_name, "port"));
		socket_listen(cport, config, table_idx);
	}catch(std::exception& x){
		throw (std::runtime_error(x.what()));
	}
	
	std::string req_timeout = config.search_val(config[table_idx]->table_name, "req_timeout");
	if (req_timeout.empty() != true && atoi(req_timeout.c_str()) > 1)
		cport.req_timeout = atoi(req_timeout.c_str());
	else 
		cport.req_timeout = CONN_TIMEOUT;

	cport.server_name = config[table_idx]->table_name;
	return (cport);
}
