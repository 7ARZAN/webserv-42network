#include "../includes/webserver.hpp"
#include "../includes/log.hpp"

std::map<std::string, std::string> 	mime_types;
std::map<int, std::string>		http_status;
ws_log					logx;
bool					dirlist = false;


std::map<std::string, std::string> cache_MimeTypes(){
	std::vector<std::string>	Types;
	std::vector<std::string>	Mime;
	std::map<std::string, std::string> MimeTypes;
	int	i;

	i = -1;
	Mime = ohmysplit(MIME, "|");
	Types = ohmysplit(TYPE, "|");
	while (++i < (int) Types.size()){
		std::pair<std::string, std::string> x(Types[i], Mime[i]);
		mime_types.insert(x);
	}
	return (mime_types);
}

std::map<int, std::string> cache_StatusCode(){
	std::vector<std::string>	codes;
	std::vector<std::string>	msg;
	std::map<int, std::string>	status;
	int	i;

	i = -1;
	codes = ohmysplit(HTTP_CODES, "|");
	msg = ohmysplit(HTTP_MSG, "|");
	while (++i < (int) codes.size()){
		std::pair<int, std::string> x(atoi(codes[i].c_str()), msg[i]);
		status.insert(x);
	}
	return (status);
}

int main(int ac, char **av){
	if (ac < 2){
		std::cerr << "Usage : " << av[0] << " <ws_configuration.conf>" << std::endl;
		return (EXIT_FAILURE);
	}
	std::string content = read_file(av[1]);
	if (content == "")
		return (EXIT_FAILURE);
	http_status = cache_StatusCode();
	mime_types = cache_MimeTypes();

	ws_config conf;
	conf.parse_string(content);

	// setting log
	//logx = ws_log(conf.search_val("default", "log_path"), conf.search_val("default", "log_level"));
	std::string dirlisting = conf.search_val("default", "dirlist");
	if (dirlisting == "true")
		dirlist = true;

	try {
		ws_connections connections(conf);
		connections.accept_connections();
	} catch (std::exception &e){
		logx.error(e.what());
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
