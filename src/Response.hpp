/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 02:45:14 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/18 15:10:40 by tarzan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RESPONSE_HPP
# define RESPONSE_HPP

# include <string>
# include <map>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include "RequestParsing.hpp"

class	Response
{
	private:
		Request		*_RequestPacket;
		std::map<int, std::string>	_StatusType;
		std::map<std::string, std::string>	_MimeType;
		std::string	_statusCode;
		std::string	_ResponsePacket;
		std::string	_Body;
		std::string	_HEAD;
		std::map<std::string, std::string>	_Metadata;

		bool	_MimeTypes();
		bool	_StatusTypes();
		std::string	_GetPacketDate();
		void	_GenerateHEAD();
		bool	_GenerateResponsePacket();
		std::string	_GetFileExtension(const std::string &path);

	public:
		Response();
		~Response();
		
		int	getStatusCode();
		bool	setStatusCode(int code);

		bool	setMetadata(const std::string &key, const std::string &value);
		bool	setBody(const std::string &informations);
		
		bool	sendResponse(int fd);
		bool	Redirect(const std::string &uri, bool isPermanent);

		void	setRequest(Request &request);
		Request	*getRequest();

		bool	FileReader(const std::string &path);

		//bool	isBusy();
};

#endif
