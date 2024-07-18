#include "../includes/webserver.hpp"
#include <fstream> 
#include <string> 
#include <sstream>

std::string	read_conf(char *filename){
	std::ifstream conffile(filename);
	std::ostringstream fcontent;

	if (!conffile.is_open()){
		std::cerr << "cant open the conf file" << std::endl;
		return ("");
	}
	fcontent << conffile.rdbuf();
	return fcontent.str();
}

int main(int argc, char **argv){
	if (argc < 2){
		std::cerr << "Usage : " << argv[0] << " <ws_configuration.conf>" << std::endl;
		return (EXIT_FAILURE);
	}
	std::string content = read_conf(argv[1]);
	if (content == "")
		return (EXIT_FAILURE);
	ws_config conf;
	conf.parse_string(content);
	// int i = -1;
	// int j;
	// while (++i < conf.size()){
	// 	j = -1;
	// 	std::cout << "table_name {" << conf[i]->tables.size() <<  "} : " 
	// 		<< conf[i]->table_name << std::endl;
	// 	while (++j < (int) conf[i]->tables.size()){
	// 		std::cout << "\t\t" << conf[i]->tables[j]->key <<  " = " <<
	// 			conf[i]->tables[j]->val << std::endl;
	// 	}
	// }
	// std::cout << conf.search_val(conf[1]->table_name, "port") << std::endl;
	try {
		ws_connections connections(conf);
		connections.accept_connections();
	} catch (std::exception &e){
		std::cout << e.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}
