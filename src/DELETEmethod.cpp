#include "../includes/Response.hpp"
#include "../includes/webserver.hpp"

bool is_dir(std::string path){
	struct stat	path_stat;

	if (stat(path.c_str(), &path_stat) == -1)
		return (false);
	if (path_stat.st_mode & S_IFDIR)
		return (true);
	return (false);

}

int delete_dir(std::string filepath) {
	DIR	*dir = opendir(filepath.c_str());
	struct dirent	*dir_elems;
	std::string	element;

	if (dir == NULL)
		return (-1);
	while ((dir_elems = readdir(dir)) != NULL){
		std::string elem = std::string(dir_elems->d_name);
		if (elem == "." || elem == "..")
			continue;
		element = filepath + "/" + elem;
		if (is_dir(element) == true){
			if(delete_dir(element) == -1){
				closedir(dir);
				return (-1);
			}
		}
		else
		{
			if (remove(element.c_str()) == -1){
				closedir(dir);
				return (-1);
			}
		}
	}
	closedir(dir);
	if (rmdir(filepath.c_str()) == -1)
		return (-1);
	return (0);
}

bool	isExist(const std::string &fullPath){
	struct stat	sb;

	if (stat(fullPath.c_str(), &sb) == -1)
		return (false);
	return (true);
}

void	Response::DELETE(){
	std::string 	rootpath;
	std::string	FilePath;

	rootpath = search_val_table(_RequestPacket->getConfig(), "root_dir");
	FilePath = rootpath + _RequestPacket->getUri();

	if (isExist(FilePath) == false){
		setStatusCode(404);
		return;
	}
	if (is_dir(FilePath) == true && FilePath.back() != '/'){
		setStatusCode(409);
		return;
	}
	logx.info("deleting file " + FilePath);
	if (delete_dir(FilePath) == -1){
		if (errno == 1)
			setStatusCode(403);
		else
			setStatusCode(404);
	}
	else
		setStatusCode(204);
}
