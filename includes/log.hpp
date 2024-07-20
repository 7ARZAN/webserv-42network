#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include <unistd.h>
#include <fcntl.h>

#define RED "\033[0;31m"		// error
#define BLUE "\033[0;31m"		// debug/info
#define YELLOW "\033[0;33m"		// warning
#define DEFAULT "\033[0m"

typedef enum LOG_LEVEL{
	ERROR,
	WARN,
	INFO,
	DEBUG,
	NONE
}LOG_LEVEL;

class ws_log{
	private :
		std::ofstream	log_file;
		std::string	log_path;
		LOG_LEVEL	log_level;
		bool		log_to_file;
	public :
		ws_log(std::string log_path, std::string level);
		ws_log(){};
		ws_log& operator=(ws_log x);
		~ws_log();
		void info(std::string msg);
		void error(std::string msg);
		void debug(std::string msg);
		void warn(std::string msg);

		void set_log_level(LOG_LEVEL level);
		LOG_LEVEL detect_log_level(std::string &msg);
};

#endif
