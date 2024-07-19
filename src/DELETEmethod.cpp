#include <iostream>
#include "Response.hpp"

# define STAT_FAIL 1
# define STAT_SUCCESS 0

static int	deletePath(const std::string &fullPath){
	std::string	command;

	command = "/bin/rm -rf " + fullPath;
	if (system(command.c_str()) == -1)
		return (STAT_FAIL);
	return (STAT_SUCCESS);
}

static int	deleteFile(const std::string &fullPath){
	if (remove(fullPath.c_str()) == -1)
		return (STAT_FAIL);
	return (STAT_SUCCESS);
}

static bool	isDirectory(const std::string &fullPath){
	struct stat	sb;

	if (stat(fullPath.c_str(), &sb) == -1)
		return (false);
	if (S_ISDIR(sb.st_mode))
		return (true);
	return (false);
}

static bool	isExist(const std::string &fullPath){
	struct stat	sb;

	if (stat(fullPath.c_str(), &sb) == -1)
		return (false);
	return (true);
}

bool	DELETEmethod(Response &Packet){
	std::string	RequestPath;
	std::string	FilePath;
	std::string	tmp;

	FilePath = Packet.getRequest()->getMetadata("Path");
	if (isExist(FilePath) == false){
		Packet.setStatusCode(404);
		return (true);
	}
	if (isDirectory(FilePath)){
		FilePath += "/";
		if (FilePath[FilePath.size() - 1] != '/'){
			Packet.setStatusCode(409);
			return (true);
		}
		// if (CGI){
		// 	//implement CGI for delete here !! and return
		// }
		// if (deletePath(FilePath) == STAT_SUCCESS && rmdir(FilePath.c_str()) == STAT_SUCCESS){
		// 	Packet.setStatusCode(204);
		// 	return (true);
		// }
	}
	else
	{
		// if (CGI){
		// 	//implement CGI for delete here !! and return
		// 		}
		// if (deleteFile(FilePath) == STAT_SUCCESS && remove(FilePath.c_str()) == STAT_SUCCESS){
		// 	Packet.setStatusCode(204);
		// 	return (true);
		// }
	}
	Packet.setStatusCode(500);
	return (true);
}

int	main(){
	Response	Packet;
	Request		Request;

	Request.setMethod("DELETE");
	Request.setMetadata("Path", "hh");
	Packet.setRequest(Request);
	DELETEmethod(Packet);
	std::cout << Packet.getStatusCode() << std::endl;
	return 0;
}
