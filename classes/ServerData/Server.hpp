/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:26:30 by tarzan            #+#    #+#             */
/*   Updated: 2024/03/14 03:54:32 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <map>

class	ServerData {
	private:
		std::string	_PORT; // port
		std::string	_HOST; // host
		std::string	_SERVER_NAME; // server_name localhost
		std::string	_ERROR_PAGE; // error_page 404 /404.html
		std::string	_INDEX; // index.html
		std::string	_ROOT; // root directory
		bool		_AUTO_INDEX; // on or off
		std::map<std::string, std::string>	_LOCATION; // location, value (root, index, autoindex, error_page)
	public:
		ServerData(void);
		~ServerData(void);

		void	setPort(std::string newPort);
		void	setHost(std::string newHost);
		void	setServerName(std::string newServerName);
		void	setErrorPage(std::string newErrorPage);
		void	setIndex(std::string newIndex);
		void	setRoot(std::string newRoot);
		void	setAutoIndex(bool newAutoIndex);
		void	setLocation(std::string location, std::string value);

		std::string	getPort(void);
		std::string	getHost(void);
		std::string	getServerName(void);
		std::string	getErrorPage(void);
		std::string	getIndex(void);
		std::string	getRoot(void);
		bool		getAutoIndex(void);
		std::string	getLocation(std::string location);
		std::map<std::string, std::string>	getLocations(void);
		ServerData	*clone(void);
};

class	Server{
	private:
		ServerData	*_ServerData; // server data (port, host, server_name, error_page, index, root, autoindex, location)
		Server		*_Prev; // previous server
		Server		*_Next; // next server
	public:
		Server(void);
		~Server(void);

		void	setServerData(ServerData *newServerData);
		void	setNext(Server *nextServer);
		void	setPrev(Server *prevServer);

		ServerData	*getServerData(void);
		Server		*getNext(void);
		Server		*getPrev(void);
		Server		*clone(void);
};

#endif
