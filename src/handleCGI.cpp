#include "../includes/handleCGI.hpp"
#include "../includes/webserver.hpp"


std::string	handleCGI::getCGIPath(){
	std::string	extension = req->getRequest()->getUri().substr(
			req->getRequest()->getUri().find_last_of('.') + 1);
	std::string	extensions[] = {"php", "py", "pl", "rb", "cgi"};
	std::string	cgi[] = {
		search_val_table(req->getRequest()->getConfig(), "PHPCGI"),
		search_val_table(req->getRequest()->getConfig(), "PYCGI"),
		search_val_table(req->getRequest()->getConfig(), "PLCGI"),
		search_val_table(req->getRequest()->getConfig(), "RBCGI"),
		search_val_table(req->getRequest()->getConfig(), "CGI")
	};
	int i = -1;

	while (++i < (int) sizeof(extensions)){
		if (extension == extensions[i]){
			return (cgi[i]);
		}

	}
	return ("");
}

CGI_TYPE	cgi_type(const std::string &Path){
	std::string	extension = Path.substr(Path.find_last_of('.') + 1);
	std::string	extensions[] = {"php", "py", "pl", "rb", "cgi"};
	CGI_TYPE	types[] = {PHP, PY, PL, RB, CGI};

	for (int i = 0; i < 5; i++)
		if (extension == extensions[i])
			return (types[i]);
	return (NOCGI);
}

bool	isCGI(const std::string &Path){
	std::string	extension = Path.substr(Path.find_last_of('.') + 1);
	std::string	extensions[] = {"php", "py", "pl", "rb", "cgi"};

	for (int i = 0; i < 5; i++)
		if (extension == extensions[i])
			return (true);
	return (false);
}

int	handleCGI::CGIMethod(const std::string &Method){
	if (Method == "GET")
		return (0);
	else if (Method == "POST")
		return (1);
	return (-1);
}

std::map<std::string, std::string>	handleCGI::getCGIEnv(){
	std::map<std::string, std::string>	envs;
	std::string	uri = req->getRequest()->getUri();
	std::string	ext = uri.substr(uri.find_last_of('.') + 1);

	envs["SERVER_NAME"] = "webserver";
	envs["SERVER_PORT"] = search_val_table(req->getRequest()->getConfig(), "port");
	envs ["CONTENT_TYPE"] = req->getRequest()->getMetadata("Content-Type");
	if (req->getRequest()->getMetadata("Content-Type").empty())
		envs ["CONTENT_TYPE"] = "text/html";
	envs ["CONTENT_LENGTH"] = req->getRequest()->getMetadata("Content-Length");
	if (req->getRequest()->getMetadata("Content-Length").empty())
		envs ["CONTENT_LENGTH"] = "0";
	envs ["SCRIPT_NAME"] = path;
	envs ["REQUEST_URI"] = uri;
	envs["SERVER_PROTOCOL"] = req->getRequest()->getVersion();
	envs["GATEWAY_INTERFACE"] = "CGI/1.1";
	envs["REQUEST_METHOD"] = req->getRequest()->getMethod();
	envs["SCRIPT_FILENAME"] = path ;
	envs["QUERY_STRING"] = req->getRequest()->getquery() ;

	if (ext == "php"){
		envs["PHP_SELF"] =  search_val_table(req->getRequest()->getConfig(), "PHPCGI") ;
		envs["REDIRECT_STATUS"] = "0" ;
	}
	else if (ext == "py")
		envs["PYTHONPATH"] = search_val_table(req->getRequest()->getConfig(), "PYCGI") ;
	else if (ext == "pl")
		envs["PERL5LIB"] =  search_val_table(req->getRequest()->getConfig(), "PLCGI") ;
	else if (ext == "rb")
		envs["RUBYLIB"] =  search_val_table(req->getRequest()->getConfig(), "RBCGI");
	else if (ext == "cgi")
		envs["CGI_NAME"] =  search_val_table(req->getRequest()->getConfig(), "CGI") ;
	return (envs);
}

char **maptoenv(std::map<std::string, std::string> menvs){
	char **env = new char*[menvs.size() + 1];
	std::map<std::string, std::string>::iterator it = menvs.begin();
	std::string	env_element;
	int i = 0;

	bzero(env, menvs.size() + 1);
	while (it != menvs.end()){
		env[i] = new char[it->first.size() + it->second.size() + 2];
		bzero(env[i], it->first.size() + it->second.size() + 2);
		env_element = it->first + "=" + it->second;
		strncpy(env[i], env_element.data(), env_element.size());
		i++;
		it++;
	}
	env[i] = NULL;
	return env;
}


handleCGI::handleCGI(Response *request, std::string path) {
	this->req = request;
	this->path = path;
}



void	handleCGI::execCGI(){
	pid_t	pid;
	int	status;
	char	buffer[1024];
	size_t	bytes;
	int	outpipes[2];
	int	inpipes[2];
	char	*argv[4];
	char	**env;
	std::string cgi_output;
	std::map<std::string, std::string> menv = getCGIEnv();

	env = maptoenv(menv);
	if (getCGIPath().empty() == true || access(getCGIPath().c_str(), X_OK) == -1){
		this->req->setStatusCode(500);
		return;
	}
	argv[0] = (char *) getCGIPath().c_str();
	argv[1] = (char *) path.c_str();
	argv[2] = NULL;

	pipe(outpipes) ;
	pipe(inpipes) ;

	pid = fork();
	if (pid == 0){
		close(inpipes[1]);
        	dup2(inpipes[0], STDIN_FILENO);
		close(inpipes[0]);


		close(outpipes[0]);
        	dup2(outpipes[1], STDOUT_FILENO);
		close(outpipes[1]);

		if (execve(argv[0], argv, env) == -1)
			std::cerr << "execve error" << std::endl;
		exit(EXIT_SUCCESS);
	}
	else{
		logx.info("executing :" + path);
		close(inpipes[0]);
		close(outpipes[1]);
		if (this->req->getRequest()->getMethod() == "GET"){
			write(inpipes[1], "\n",1);

		}
		if (this->req->getRequest()->getBody().empty() == false){
			write(inpipes[1], this->req->getRequest()->getBody().c_str(),
					this->req->getRequest()->getBody().size());
		}
		while ((bytes = read(outpipes[0], buffer, 1)) > 0){
			cgi_output.append(buffer, bytes);
			bzero(buffer, 1024);
		}


		this->req->setMetadata("Content-Type", "text/html");
		this->req->setBody(cgi_output);
		waitpid(pid, &status, 0);
	}
}
