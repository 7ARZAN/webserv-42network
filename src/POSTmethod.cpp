#include "../includes/Response.hpp"
#include "../includes/handleCGI.hpp"
#include "../includes/multipart.hpp"
#include "../includes/webserver.hpp"


void	Response::POSTFILE(std::string boundary){
	multipart	req;
	int		i = -1;
	std::string 	upload_dir = search_val_table(_RequestPacket->getConfig(), "upload_dir");

	if (upload_dir.empty() == true || access(upload_dir.c_str(), W_OK) == -1){
		setStatusCode(403);
		return;
	}
	if (upload_dir.back() != '/')
		upload_dir += "/";
	req.setboundary(boundary);
	req.parse_mbody(_RequestPacket->getBody());
	std::vector<data_chunk>	chunks = req.get_chunks();
	while (++i < (int) chunks.size()){
		std::map<std::string, std::string>::iterator it = chunks[i].propreties.begin();
		if (chunks[i].propreties.find("filename") != chunks[i].propreties.end()){
			std::ofstream file;
			logx.info("uploading " + upload_dir + it->second);
			file.open(upload_dir + it->second);
			if (file.is_open() == false){
				setStatusCode(403);
				return ;
			}
			file << chunks[i].content;
			file.close();
		}
	}
}

void	Response::POST(){
	multipart	req;
	std::vector<std::string>	boundary;
	std::string	content_type = _RequestPacket->getMetadata("Content-Type");
	std::string	rootpath = search_val_table(_RequestPacket->getConfig(), "root_dir");
	std::string	FilePath = rootpath + _RequestPacket->getUri();
	handleCGI	cgi(this, FilePath);

	if (isCGI(FilePath) == true){
		cgi.execCGI();
		return ;
	}
	if (strncmp(content_type.c_str(), "multipart/form-data", 19) == 0){
		boundary = ohmysplit(content_type.substr(content_type.find("; ") + 2), "=");
		if (boundary[0] == "boundary")
			POSTFILE(boundary[1]);
		else
			setStatusCode(403);
	}
}
