#include "../includes/webserver.hpp"
#include <string.h>
#include "../includes/connection.hpp"
#include "../includes/RequestParsing.hpp"
#include "../includes/Response.hpp"

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

ws_connections::ws_connections(ws_config &config){
	int i = -1;			// iterates over the config
	ws_port cport;
	std::string dir;

	this->config = config;
	while (++i < (int) config.size()){
		if (config[i]->table_name == "default" ||
			config.search_val(config[i]->table_name, "port").empty())
			continue;
		try {
			cport = setup_socket(config, i);
			dir = config.search_val(config[i]->table_name, "root_dir");
			if (dir.empty() == true || access(dir.c_str(), R_OK) == -1){
				throw (std::runtime_error("root directory either is not set or doesn't exist"));
			}
			if (cport.nport == -1)
				continue;
		}catch (std::exception &e){
			throw std::runtime_error(e.what());
		}
		std::string portnum = config.search_val(config[i]->table_name, "port");
		logx.info("Serving HTTP on 0.0.0.0 port " + portnum +
			" <" + cport.server_name + "> (http://localhost:" + portnum);
		ports.push_back(cport);
	}
	if (ports.size() < 1)
		throw (std::runtime_error("Server can't listen to any port"));
}

void ws_connections::close_connection(unsigned int idx, unsigned int port_idx){
	if ((idx + 1) > ports.size() || (port_idx + 1)> ports[idx].conn_fds.size()){
		return ;
	}
	logx.info("connection closed on " + ports[idx].server_name);
	close(ports[idx].conn_fds[port_idx].fd);
	ports[idx].conn_fds.erase(ports[idx].conn_fds.begin() + port_idx);
	ports[idx].requests.erase(ports[idx].requests.begin() + port_idx);
	ports[idx].responses.erase(ports[idx].responses.begin() + port_idx);
	ports[idx].last_interaction.erase(ports[idx].last_interaction.begin() + port_idx);
}

void ws_connections::parse_and_serve(ws_delivery *request, ws_delivery *response, int nport){
	if (request->req == NULL)
		request->req = new Request(request, response, config.search_table_port(nport));
	try {
		if (request->status == READY || request->status == BODY_READ){
			request->req->parseRequest();
		}
	}catch (Response &resp){
		response->delivery = resp.RenderResponse();
		response->status = READY;
		return;
	}
	if (request->status == READY){
		Response resp(request->req);
		resp.handleResponse();
		response->delivery = resp.RenderResponse();
		response->status = READY;
	}
}

// extracts the request from the buffer and packs it into the 
// delivery
// RETURN VALUE
// returns true if there's a request, if not it returns false
bool ws_connections::pack_request(ws_delivery *delivery, ws_delivery *response, int nport){
	if (delivery == NULL)
		return (false);
	if (delivery->status == READING_BODY && delivery->left < 1){
		delivery->status = BODY_READ;
		parse_and_serve(delivery, response, nport);
		return (true);
	}
	size_t	intersection = 0;
	while((intersection = delivery->buffer.find("\r\n\r\n")) != std::string::npos){
		delivery->delivery = delivery->buffer.substr(0, intersection + 4);
		delivery->buffer.erase(0, intersection + 4);
		delivery->status = READY;
		parse_and_serve(delivery, response, nport);
		if (delivery->left > 0 )
			return (true);
	}
	return (true);
}

void ws_connections::monitor_connections(){
	// listening to all the sockets
	char buffer[1025];
	int i = -1;
	while (++i < (int) ports.size()){
		int j = -1;
		poll(&ports[i].conn_fds[0], ports[i].conn_fds.size(), EVENT_TIMEOUT);
		while (++j < (int) ports[i].conn_fds.size()){
			bzero(buffer, 1025);
			// basically timout the user
			if ((time(0) - ports[i].last_interaction[j] >  ports[i].req_timeout)
				|| ports[i].conn_fds[j].revents & POLLHUP ){
				Response resp(504);
				ports[i].responses[j].delivery = resp.RenderResponse();
				ports[i].responses[j].status = READY;
				close_connection(i, j--);
			}
			else if (ports[i].conn_fds[j].revents & POLLIN){
				if (read(ports[i].conn_fds[j].fd, buffer, 1024) < 1){
					close_connection(i, j--);
				}else {
					ports[i].requests[j].buffer += std::string(buffer);
					if (ports[i].requests[j].left > 0)
						ports[i].requests[j].left -= strlen(buffer);
					ports[i].last_interaction[j] = time(NULL);
					pack_request(&ports[i].requests[j], &ports[i].responses[j], ports[i].nport);
				}
			} else if (ports[i].conn_fds[j].revents & POLLOUT 
				&& ports[i].responses[j].status == READY){
				write(ports[i].conn_fds[j].fd,
						ports[i].responses[j].delivery.c_str() ,
						ports[i].responses[j].delivery.size());
				close_connection(i, j--);
			}
		}
	}
}

void ws_connections::accept_connections(){
	int			i = -1;
	int			csocket;
	ws_delivery		delivery;
	struct pollfd		tmpcont;
	struct sockaddr_in	iconn;
	socklen_t		addr_len;

	while (true){
		i = -1;
		while (++i < (int) ports.size()){
			csocket = accept(ports[i].main_socket, (struct sockaddr *) &iconn , &addr_len);
			if (csocket != -1){
				logx.info( "connection accepted from " + 
						std::string(inet_ntoa(iconn.sin_addr)));
				// tmp socket
				tmpcont.fd = csocket;
				tmpcont.events = POLLIN | POLLOUT;
				// tmp delivery
				delivery.status = PENDING;
				delivery.left = 0;
				delivery.req = NULL;
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
