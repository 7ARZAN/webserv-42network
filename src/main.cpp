#include "../includes/webserver.hpp"
#include "../includes/log.hpp"
#include "../includes/SessionManager.hpp"

std::map<std::string, std::string> mime_types;
std::map<int, std::string> http_status;
ws_log logx;
bool dirlist = false;

std::map<std::string, std::string> cache_mime_types() {
	std::vector<std::string> types = ohmysplit(TYPE, "|");
	std::vector<std::string> mime = ohmysplit(MIME, "|");
	std::map<std::string, std::string> mime_types;
	int i = -1;
	while (++i < (int)types.size()) {
		std::pair<std::string, std::string> x(types[i], mime[i]);
		mime_types.insert(x);
	}
	return mime_types;
}

std::map<int, std::string> cache_http_status() {
	std::vector<std::string> http_codes = ohmysplit(HTTP_CODES, "|");
	std::vector<std::string> http_msg = ohmysplit(HTTP_MSG, "|");
	std::map<int, std::string> http_status;
	int i = -1;
	while (++i < (int)http_codes.size()) {
		std::pair<int, std::string> x(atoi(http_codes[i].c_str()), http_msg[i]);
		http_status.insert(x);
	}
	return http_status;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <ws_configuration.conf>" << std::endl;
		return EXIT_FAILURE;
	}
	std::string content = read_file(argv[1]);
	if (content == "") return EXIT_FAILURE;
	http_status = cache_http_status();
	mime_types = cache_mime_types();

	ws_config conf;
	conf.parse_string(content);

	std::string dirlisting = conf.search_val("default", "dirlist");
	if (dirlisting == "true") dirlist = true;

	SessionManager sessionManager;
	try {
		ws_connections connections(conf, &sessionManager);
		connections.accept_connections();
	} catch (std::exception &e) {
		logx.error(e.what());
		std::exit(EXIT_FAILURE);
	}
	return 0;
}
