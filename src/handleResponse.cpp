#include "Response.hpp"
#include "tools.hpp"

static int	checkRequestFormat(const Request &request){
	return 200;
}

static bool	isRedirect(Response &Packet){
	std::string	uri = Packet.getRequest()->getUri();

	if (uri == "/")
		return true;
	if (uri[uri.size() - 1] == '/')
		return true;
	return false;
}

void	handleResponse(int fd, Response &Packet){
	int	status;

	status = checkRequestFormat(*Packet.getRequest());
	// if (status != 200){
	// 	Packet.setStatusCode(status);
	// 	Packet.sendResponse(fd);
	// 	return ;
	// }
	// if (isRedirect(Packet)){
	// 	Packet.setStatusCode(301);
	// 	Packet.sendResponse(fd);
	// 	return ;
	// }
	// if (Packet.getRequest()->getMethod() == "GET")
	// 	GETmethod(Packet);
	// else if (Packet.getRequest()->getMethod() == "POST")
	// 	POSTmethod(Packet);
	// else if (Packet.getRequest()->getMethod() == "DELETE")
	// 	DELETEmethod(Packet);
	// else
	// 	Packet.setStatusCode(405);
	Packet.sendResponse(fd);
}
