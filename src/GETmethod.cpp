#include "Response.hpp"
#include <dirent.h>

static std::string	full_path(){
	char	*path;
	std::string	RootPath;

	path = getcwd(NULL, 0);
	RootPath = path;
	free(path);
	return RootPath;
}

static std::string	RootPath(){
	std::string	RootPath;

	RootPath = full_path();
	if (RootPath[RootPath.size() - 1] != '/')
		RootPath += "/";
	return RootPath;
}

bool	handleAutoIndex(Response &Packet){
	std::string	RequestPath;
	DIR			*dir;
	struct dirent	*ent;
	std::string		IndexFile;

	RequestPath = RootPath() + Packet.getRequest()->getUri();
	if (RequestPath[RequestPath.size() - 1] != '/')
		RequestPath += "/";
	if ((dir = opendir(RequestPath.c_str())) == NULL)
		return false;
	while ((ent = readdir(dir)) != NULL){
		if (ent->d_type == DT_REG){
			IndexFile = ent->d_name;
			if (IndexFile == "index.html"){
				closedir(dir);
				return Packet.FileReader(RequestPath + IndexFile);
			}
		}
	}
	closedir(dir);
	return true;
}

bool	GETmethod(Response &Packet){
	std::string	RequestPath;
	struct stat	fileStat;
	int			fd;

	RequestPath = RootPath() + Packet.getRequest()->getUri();
	std::cout << "RequestPath: " << RequestPath << std::endl;
	if (RequestPath[RequestPath.size() - 1] == '/')
		return handleAutoIndex(Packet);
	else if ((fd = open(RequestPath.c_str(), O_RDONLY)) == -1)
		return false;
	if (fstat(fd, &fileStat) == -1){
		close(fd);
		return false;
	}
	if (S_ISDIR(fileStat.st_mode)){
		close(fd);
		return handleAutoIndex(Packet);
	}
	close(fd);
	return Packet.FileReader(RequestPath);
}

int	main(){
	Response	Packet;
	Request		RequestPacket;

	RequestPacket.setMethod("GET");
	RequestPacket.setUri("index.html");
	Packet.setRequest(RequestPacket);
	if (GETmethod(Packet))
		std::cout << "File Found" << std::endl;
	else
		std::cout << "File Not Found" << std::endl;
	return 0;
}
