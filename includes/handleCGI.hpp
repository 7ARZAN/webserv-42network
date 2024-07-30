#ifndef HANDLECGI_HPP
# define HANDLECGI_HPP

# include "../includes/Response.hpp"
# include <sys/wait.h>

typedef enum CGI_TYPE{
	PY,
	PHP,
	PL,
	RB,
	CGI,
	NOCGI
}CGI_TYPE;


class	handleCGI
{
	private:
		Response *req;
		std::string path;
	public:
		handleCGI(Response *request, std::string path);
		bool		isCGI(std::string const &Path);
		std::map<std::string, std::string> getCGIEnv();
		std::string	getCGIPath();
		int		CGIMethod(std::string const &Method);
		void		setCGIEnv();
		void		execCGI();
};

bool	isCGI(const std::string &Path);

#endif
