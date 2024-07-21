#ifndef MULTIPART_HPP
#define MULTIPART_HPP

#include <iostream>
#include <vector>
#include <map>

typedef struct data_chunk{
	std::pair<std::string, std::string>	attr;
	std::map<std::string, std::string>	propreties;
	std::string				content;
}data_chunk;

class multipart{
	private :
		std::string boundary;
		std::vector<data_chunk> chunks;
	public :
		multipart(std::string boudary);
		multipart(){};
		std::map<std::string, std::string> parse_propreties(std::string &props);
		void parse_attributes(std::string &chunk);
		void parse_mbody(std::string mbody);

		void setboundary(std::string boundary);
		std::vector<data_chunk> get_chunks();
};

#endif
