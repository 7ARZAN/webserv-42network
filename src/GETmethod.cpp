#include "../includes/Response.hpp"
#include "../includes/webserver.hpp"

std::string	read_file(std::string filename){
	std::ifstream	config_file(filename);
	std::ostringstream fcontent;

	if (!config_file.is_open()){
		std::cerr << "cant open the conf file" << std::endl;
		return ("");
	}
	fcontent << config_file.rdbuf();
	return fcontent.str();
}

std::string	list_dir(std::string path){
	DIR *dir = opendir(path.c_str());
	struct dirent *dirfiles;
	std::string	response;

	if (dir == NULL)
		throw(std::runtime_error("[List Dir]: cant open dir"));
	while ((dirfiles = readdir(dir)) != NULL){
		response += "<a href=" + std::string(dirfiles->d_name) + ">" +
			std::string(dirfiles->d_name) +"</a><br>\n";
	}
	closedir(dir);
	return (response);
}


void	Response::GET(){
	std::string rootPath = search_val_table(_RequestPacket->getConfig(), "root_dir");
	std::string FilePath = rootPath + _RequestPacket->getUri();

	if (isExist(FilePath) == false){
		setStatusCode(404);
		return;
	}
	if (is_dir(FilePath) == true ){
		if (FilePath.back() != '/'){
			setMetadata("Location", _RequestPacket->getUri() + "/");
			setStatusCode(301);
			return;
		}
		if (isExist(FilePath + "index.html") == true)
			FilePath += "index.html";
		else {
			try {
				if (dirlist == false)
					throw (false);
				logx.info("[List Dir]: " + FilePath);
				_Body = list_dir(FilePath);
			}catch(...){
				setStatusCode(404);
			}
			return;
		}
	}
	_Body = read_file(FilePath);
}
