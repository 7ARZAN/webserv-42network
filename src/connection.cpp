#include "../includes/webserver.hpp"
#include <string.h>
#include "../includes/connection.hpp"
#include "RequestParsing.hpp"

// todo update this
ws_connections &ws_connections::operator=(ws_connections &x){
	if (this == &x)
		return (*this);
	size_t i = -1;
	i = -1;
	while (++i < x.ports.size()){
		this->ports.push_back(x.ports[i]);
	}
	return (*this);
}

ws_connections::ws_connections(){}

ws_port ws_connections::setup_socket(ws_config &config, int table_idx){
	ws_port			cport;
	struct sockaddr_in 	address;
	std::string 		port = config.search_val(config[table_idx]->table_name, "port");
	unsigned int		maxconn_n;

	if (port.empty() == true){
		cport.nport = -1;
		return (cport);
	}
	// registering port number, cause we will need this
	cport.nport = atoi(port.c_str());
	if (cport.nport > 0xffff || cport.nport < 0)
		throw (std::range_error("port out of bounds"));

	// creating a main socket for the port
	cport.main_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (cport.main_socket < 0)
		throw (std::runtime_error("can't create a socket"));

	// setting the socket to be non blocking, we need to get as much conections as we need
	if (fcntl(cport.main_socket, F_SETFL, fcntl(cport.main_socket, F_GETFL, 0) | O_NONBLOCK) < 0)
		throw (std::runtime_error("the socket cant be non blocking"));

	// binding our socket to the port
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(cport.nport);
	if(bind(cport.main_socket, (struct sockaddr *) &address, sizeof(address)) < 0)
		throw std::runtime_error("can't bind socket with port " + std::to_string(cport.nport));

	maxconn_n = SOMAXCONN;
	std::string max_connections = config.search_val(config[table_idx]->table_name, "max_connections");
	if (max_connections != "") {
		maxconn_n = atoi(max_connections.c_str());
		if (maxconn_n > SOMAXCONN)
			throw (std::runtime_error("unvalid max connections for port " 
				+ std::to_string(cport.nport)));
	}

	if (listen(cport.main_socket, maxconn_n) < 0)
		throw (std::runtime_error("can't listen to port" + std::to_string(cport.nport)));

	std::string req_timeout = config.search_val(config[table_idx]->table_name, "req_timeout");
	if (req_timeout.empty() != true && atoi(req_timeout.c_str()) > 1)
		cport.req_timeout = atoi(req_timeout.c_str());
	else 
		cport.req_timeout = CONN_TIMEOUT;

	cport.server_name = config[table_idx]->table_name;
	return (cport);

}

ws_connections::ws_connections(ws_config &config){
	int i = -1;			// iterates over the config
	ws_port cport;

	while (++i < (int) config.size()){
		try {
			cport = setup_socket(config, i);
			if (cport.nport == -1)
				continue;
		}catch (std::exception &e){
			throw std::runtime_error(e.what());
		}
		std::cout << "Serving HTTP on 0.0.0.0 port " << cport.nport 
			<< " <" << cport.server_name << "> (http://localhost:"
			<< cport.nport << ")" << std::endl;
		ports.push_back(cport);
	}
	if (ports.size() < 1)
		throw (std::runtime_error("Server can't listen to any port"));
}

void ws_connections::close_connection(unsigned int idx, unsigned int port_idx){
	if ((idx + 1) > ports.size() || (port_idx + 1)> ports[idx].conn_fds.size()){
		return ;
	}
	std::cout << "connection closed " << ports[idx].conn_fds[port_idx].fd << std::endl;
	close(ports[idx].conn_fds[port_idx].fd);
	ports[idx].conn_fds.erase(ports[idx].conn_fds.begin() + port_idx);
	ports[idx].requests.erase(ports[idx].requests.begin() + port_idx);
	ports[idx].responses.erase(ports[idx].responses.begin() + port_idx);
	ports[idx].last_interaction.erase(ports[idx].last_interaction.begin() + port_idx);
}

void parse_and_serve(ws_delivery *request, ws_delivery *response){
	Request	hello;

	hello.appendRequestPacket(request->delivery);
	hello.parseRequest();
	response->delivery = "hello there";
	response->status = READY;
	std::cout << response->delivery << "\n";
}

// extracts the request from the buffer and packs it into the 
// delivery
// RETURN VALUE
// returns true if there's a request, if not it returns false
bool ws_connections::pack_request(ws_delivery *delivery, ws_delivery *response, int sock_fd){
	if (delivery == NULL)
		return (false);
	size_t	intersection = 0;
	while((intersection = delivery->buffer.find("\r\n\r\n")) != std::string::npos){
		delivery->delivery = delivery->buffer.substr(0, intersection);
		delivery->buffer.erase(0, intersection + 4);
		delivery->status = READY;
		try {
			parse_and_serve(delivery, response);
		}catch(size_t post_body_len){
			std::string post_body;
			post_body.reserve(post_body_len + 1);
			if (read(sock_fd, (char *) post_body.c_str(), post_body_len) < 1)
				return (false);
			delivery->buffer += post_body;
			delivery->delivery += std::string("\r\n\r\n") + delivery->buffer;
			delivery->buffer.erase();
			delivery->status = READY;
			parse_and_serve(delivery, response);
		}
	}
	return (true);
}

void ws_connections::monitor_connections(){
	// listening to all the sockets
	char buffer[1024];
	int i = -1;
	while (++i < (int) ports.size()){
		int j = -1;
		poll(&ports[i].conn_fds[0], ports[i].conn_fds.size(), 100);
		while (++j < (int) ports[i].conn_fds.size()){
			bzero(buffer, 1024);
			if (time(0) - ports[i].last_interaction[j] >  ports[i].req_timeout){
				close_connection(i, j);
				j--;
				continue;
			}
			else if (ports[i].conn_fds[j].revents & POLLHUP 
					|| ports[i].conn_fds[j].revents & POLLERR){
				close_connection(i, j);
				j--;
			}
			else if (ports[i].conn_fds[j].revents & POLLIN){
				if (read(ports[i].conn_fds[j].fd, buffer, 1024) < 1){
					close_connection(i, j);
					j--;
				}else {
					//std::cout << "messge recv : " << buffer << std::endl;
					ports[i].requests[j].buffer += std::string(buffer);
					ports[i].last_interaction[j] = time(NULL);
					if(pack_request(&ports[i].requests[j], &ports[i].responses[j],
								ports[i].conn_fds[j].fd) == false)
						close_connection(i, j);
					ports[i].requests[j].status = PENDING;
				}
			} else if (ports[i].conn_fds[j].revents & POLLOUT){
				if (ports[i].responses[j].status == READY){
					write(ports[i].conn_fds[j].fd,
							ports[i].responses[j].delivery.c_str() ,
							ports[i].responses[j].delivery.size());
				}
			}
		}
	}
}

void ws_connections::accept_connections(){
	int			i = -1;
	int			csocket;
	ws_delivery		delivery;
	struct pollfd		tmpcont;
	struct sockaddr_in	incomm_conn;
	socklen_t		addr_len;

	while (true){
		i = -1;
		while (++i < (int) ports.size()){
			csocket = accept(ports[i].main_socket, (struct sockaddr *) &incomm_conn
					, &addr_len);
			if (csocket != -1){
				std::cout << "connection accepted from " <<
					inet_ntoa(incomm_conn.sin_addr) << std::endl;
				// tmp socket
				tmpcont.fd = csocket;
				tmpcont.events = POLLIN | POLLOUT;
				// tmp delivery
				delivery.delivery = std::string("");
				delivery.buffer = std::string("");
				delivery.status = PENDING;
				// setting socket metadata
				ports[i].conn_fds.push_back(tmpcont);
				ports[i].requests.push_back(delivery);
				ports[i].responses.push_back(delivery);
				ports[i].last_interaction.push_back(time(0));
			}
		}
		monitor_connections();
	}
}
