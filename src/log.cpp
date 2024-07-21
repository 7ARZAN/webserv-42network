#include "../includes/log.hpp"
#include <iostream>


ws_log& ws_log::operator=(ws_log x){
	if (this->log_file.is_open()){
		this->log_file.open(x.log_path);
		this->log_path = x.log_path;
		this->log_to_file = true;
	}else
		this->log_to_file = false;
	this->log_level = x.log_level;
	return (*this);
}

ws_log::ws_log(std::string log_path, std::string level){
	this->log_path = log_path;
	log_level = detect_log_level(level);
	if (log_path.empty() == true || access(log_path.c_str(), W_OK) == -1){
		log_to_file = false;
		return;
	}
	log_file.open(log_path);
	log_to_file = true;
}

ws_log::~ws_log(){
	log_file.close();
}

void ws_log::info(std::string msg){
	if (log_level <= INFO){
		std::cout << "[" << BLUE << "*"  << DEFAULT << "] - " ;
		std::cout << msg << std::endl;
		if (log_to_file == true){
			log_file << msg << "\n" << std::flush;
		}
	}
}
void ws_log::error(std::string msg){
	if (log_level <= ERROR){
		std::cout << "[" << RED << "ERROR"  << DEFAULT << "] - " ;
		std::cout << msg << std::endl;
		if (log_to_file == true){
			log_file << msg << "\n" << std::flush;
		}
	}
}
void ws_log::debug(std::string msg){
	if (log_level <= DEBUG){
		std::cout << "[" << BLUE << "*"  << DEFAULT << "] - " ;
		std::cout << msg << std::endl;
		if (log_to_file == true){
			log_file << msg << "\n" << std::flush;
		}
	}
}
void ws_log::warn(std::string msg){
	if (log_level <= WARN){
		std::cout << "[" << YELLOW << "!"  << DEFAULT << "] - " ;
		std::cout << msg << std::endl;
		if (log_to_file == true){
			log_file << msg << "\n" << std::flush;
		}
	}
}

void ws_log::set_log_level(LOG_LEVEL level){
	this->log_level = level;
}

LOG_LEVEL ws_log::detect_log_level(std::string &msg){
	if (msg == "ERROR")
		return (ERROR);
	if (msg == "WARN")
		return (WARN);
	if (msg == "INFO")
		return (INFO);
	if (msg == "DEBUG")
		return (DEBUG);
	return (NONE);
}

