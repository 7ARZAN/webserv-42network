/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 02:45:14 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/21 14:47:15 by tarzan           ###   ########.fr       */
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

class	Response
{
	private:
		Request		*_RequestPacket;
		std::string	_statusCode;
		std::string	_ResponsePacket;
		std::string	_Body;
		std::string	_HEAD;
		std::map<std::string, std::string>	_Metadata;

		std::string	_GetPacketDate();
		void	_GenerateHEAD();
		void	_GenerateCookie();
		std::string	_GetFileExtension(const std::string &path);

	public:
		Response(Request *req);
		Response(int status_code);
		~Response();
		
		int	getStatusCode();
		bool	setStatusCode(int code);

		bool	setMetadata(const std::string &key, const std::string &value);
		bool	setBody(const std::string &informations);
		
		bool	Redirect(const std::string &uri, bool isPermanent);

		void	setRequest(Request &request);
		Request	*getRequest();

		void	handleResponse();

		std::string	render_response();
		void		DELETE();
		void		GET();
		void		POST();
		void		POSTFILE(std::string boundary);
};

bool	isExist(const std::string &fullPath);
bool	is_dir(std::string path);

#endif
