#include "../includes/multipart.hpp"
#include <string.h>

multipart::multipart(std::string boundaries){
	boundary = "--" + boundaries;
}

void multipart::setBoundary(std::string boundaries){
	boundary = "--" + boundaries;
}

void strip_str(std::string &str, char Char2Strip){
	int	i;

	i = 0;
	while (str[i] == Char2Strip){
		str.erase(i, i + 1);
	}
	i = str.size() - 1;
	while (str[i] == Char2Strip){
		str.erase(i, i + 1);
		i--;
	}
}

std::string find_and_delete(std::string &haystack, std::string needle){
	std::string	farm;

	if (haystack.find(needle) == std::string::npos){
		return (std::string(""));
	}
	farm = haystack.substr(0, haystack.find(needle));
	haystack.erase(0, haystack.find(needle) + needle.size());
	return (farm);
}


std::map<std::string, std::string> multipart::parse_propreties(std::string &props){
	std::map<std::string, std::string>	mprops;
	std::pair<std::string, std::string>	cont;
	while (props.empty() == false){
		strip_str(props, ' ');
		cont.first = find_and_delete(props, "=");
		if (cont.first.empty() == true)
			throw(std::runtime_error("prop key without value"));
		strip_str(props, ' ');
		cont.second = find_and_delete(props, ";");
		if (cont.second.empty() == true){
			cont.second = props;
			props.erase(0, props.size());
		}
		strip_str(cont.second, '"');
		mprops.insert(cont);
	}
	return (mprops);
}

void multipart::parse_attributes(std::string &chunk){
	// removing attributes out of the body
	data_chunk	data;

	std::string attrs = chunk.substr(0, chunk.find("\r\n\r\n") + 2);
	chunk.erase(0, chunk.find("\r\n\r\n") + 4);

	while (attrs.find("\r\n") != std::string::npos){
		std::string line = find_and_delete(attrs, "\r\n");

		// parsing the attribute
		data.attr.first = find_and_delete(line, ":");
		if (data.attr.first.empty())
			throw (std::runtime_error("corrupted attribute"));
		strip_str(line, ' ');

		data.attr.second = find_and_delete(line, ";");
		if (data.attr.second.empty() == true){
			data.attr.second = line;
			if (data.attr.second.empty())
				throw (std::runtime_error("corrupted attribute"));
			continue;
		}
		strip_str(line, ' ');
		data.propreties = this->parse_propreties(line);
	}
	this->chunks.push_back(data);
}

void multipart::parse_mbody(std::string mbody){
	std::string chunk_body;
	size_t		chunk_size;
	while ((chunk_size = mbody.find(this->boundary, this->boundary.size())) != std::string::npos){
		chunk_body = mbody.substr(this->boundary.size(), 
				chunk_size - this->boundary.size() - 2);
		mbody.erase(0, chunk_size);
		if (mbody == "--\r\n")
			break;
		else if (strncmp(chunk_body.c_str(), "\r\n", 2) == 0){
			chunk_body.erase(0, 2);
		}
		if (chunk_body.find("\r\n\r\n") != std::string::npos){
			this->parse_attributes(chunk_body);
			chunks.back().content = chunk_body;
		}
		else{
			throw (std::runtime_error("corrupted multipart body"));
		}
	}
	if (mbody != "--\r\n"){
		throw (std::runtime_error("corrupted multipart body"));
	}

}


std::vector<data_chunk> multipart::getChunks(){
	return (chunks);
}

// #include <fstream>
// #include <sstream>
// int main(int argc, char **argv){
// 	std::ifstream	multi_body;
// 	std::string	multi_data;
//
// 	if (argc < 2)
// 		return (1);
//
// 	multi_body.open(std::string(argv[1]));
// 	if (multi_body.is_open() == false){
// 		std::cerr << "cant open : "  << argv[1] << std::endl;
// 		return (1);
// 	}
// 	std::stringstream strStream;
// 	strStream << multi_body.rdbuf();
// 	multi_data = strStream.str();
// 	
//
// 	multipart req("----WebKitFormBoundaryWLmlGDw2PVjBcxFc");
// 	req.parse_mbody(multi_data);
// 	std::vector<data_chunk> x = req.get_chunks();
// 	size_t i = 0;
// 	while (i < x.size()){
// 		std::cout << "[+] - Attributes" << std::endl;
// 		std::cout << x[i].attr.first << " : " << x[i].attr.second << std::endl;
// 		std::cout << "[+] - Propreties " << x[i].propreties.size() << std::endl;
// 		std::map<std::string, std::string>::iterator xp = x[i].propreties.begin();
// 		while (xp != x[i].propreties.end()){
// 			std::cout << xp->first << " : " << xp->second << std::endl;
// 			xp++;
// 		}
// 		std::cout << "[+] - Content" << std::endl;
// 		std::cout << x[i].content << std::endl;
// 		i++;
// 	}
// }
