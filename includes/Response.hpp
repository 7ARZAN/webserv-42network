/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 02:45:14 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/22 04:45:03 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RESPONSE_HPP
# define RESPONSE_HPP

# include <string>
# include <map>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <fstream>
# include <string.h>
# include <vector>
# include <unistd.h>
# include "RequestParsing.hpp"

# define STAT_FAIL 1
# define STAT_SUCCESS 0

class	Cookie{
	private:
		std::string	_name;
		std::string	_value;
		std::string	_expires;
		std::string	_path;
		std::string	_domain;
		std::string	_secure;
		std::string	_httpOnly;

	public:
		Cookie();
		~Cookie();

		bool	setName(const std::string &name);
		bool	setValue(const std::string &value);
		bool	setExpires(const std::string &expires);
		bool	setPath(const std::string &path);
		bool	setDomain(const std::string &domain);
		bool	setSecure(const std::string &secure);
		bool	setHttpOnly(const std::string &httpOnly);

		std::string	getName();
		std::string	getValue();
		std::string	getExpires();
		std::string	getPath();
		std::string	getDomain();
		std::string	getSecure();
		std::string	getHttpOnly();
};

class	Response
{
	private:
		Request		*_RequestPacket;
		std::string	_statusCode;
		std::string	_ResponsePacket;
		std::string	_Body;
		std::string	_HEAD;
		std::vector<Cookie>	Cookies;
		std::map<std::string, std::string>	_Metadata;

		std::string	_GetPacketDate();
		void	_GenerateHEAD();
		std::string	_GetFileExtension(const std::string &path);

	public:
		Response(Request *req);
		Response(int status_code);
		~Response();
		
		int	getStatusCode();
		bool	setStatusCode(int code);

		bool	setMetadata(const std::string &key, const std::string &value);
		bool	setBody(const std::string &informations);
		
		bool	sendResponse(int fd);
		bool	Redirect(const std::string &uri, bool isPermanent);

		void	setRequest(Request &request);
		Request	*getRequest();

		void	handleResponse();

		std::string	GenerateRandomCookie(Cookie *cookie);

		std::string	render_response();
		void		DELETE();
		void		GET();
		void		POST();
		void		POSTFILE(std::string boundary);

		//bool	isBusy();
};

bool	isExist(const std::string &fullPath);
bool	is_dir(std::string path);

#endif
