#include "../includes/Response.hpp"
#include "../includes/handleCGI.hpp"
#include "../includes/webserver.hpp"

std::string	read_file(std::string filename){
	std::ifstream		conffile(filename);
	std::ostringstream	fcontent;

	if (!conffile.is_open()){
		logx.error("cant open the " + filename);
		return ("");
	}
	fcontent << conffile.rdbuf();
	return fcontent.str();
}

std::string search_replace(std::string str, std::string a, std::string b) {
	size_t		pos;
	std::string	repl;

	repl = str;
	while ((pos = repl.find(a)) != std::string::npos)
		repl.replace(pos, a.length(), b);
	return (repl);
}

std::string	list_dir(std::string path){
	DIR		*dir;
	struct dirent	*dirfiles;
	std::string	response;

	dir = opendir(path.c_str());
	if (dir == NULL)
		throw(std::runtime_error("Directory not found"));
	while ((dirfiles = readdir(dir)) != NULL)
		response += "<a href=" + search_replace(dirfiles->d_name, " ", "+") + ">" + 
			dirfiles->d_name + "</a><br>";
	closedir(dir);
	return (response);
}


void	Response::GET(){
	std::string	rootpath = search_val_table(_RequestPacket->getConfig(), "root_dir");
	std::string	FilePath = rootpath + _RequestPacket->getUri();
	handleCGI	cgi(this, FilePath);

	if (isExist(FilePath) == false){
		setStatusCode(404);
		return;
	}
	if (isCGI(FilePath) == true){
		cgi.execCGI();
		return ;
	}
	else if (is_dir(FilePath) == true ){
		if (FilePath.back() != '/'){
			setMetadata("Location", _RequestPacket->getUri() + "/");
			setStatusCode(301);
			return;
		}
		if (isExist(FilePath + "index.html") == true)
			FilePath += "index.html";
		else
		{
			try{
				if (dirlist == false)
					throw (false);
				logx.info("listing dir " + FilePath);
				_Body = list_dir(FilePath);
			}catch(...){
				setStatusCode(404);
			}
			return;
		}
	}
	_Body = read_file(FilePath);
	if (_Body.empty() == true && errno == EACCES){
		setStatusCode(401);
		return;
	}
	setMetadata("Content-Type", mime_types[_GetFileExtension(FilePath)]);
	setMetadata("Content-Length", std::to_string(_Body.size()));
}
