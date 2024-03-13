/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:26:30 by tarzan            #+#    #+#             */
/*   Updated: 2024/03/12 21:43:08 by tarzan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <map>

class	ServerData {
	private:
		std::string	_PORT;
		std::string	_HOST;
		std::string	_SERVER_NAME;
		std::string	_ERROR_PAGE;
		std::string	_INDEX;
		std::string	_ROOT;
		bool		_AUTO_INDEX;
		std::map<std::string, std::string>	_LOCATION;
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
		ServerData	*_ServerData;
		Server		*_Prev;
		Server		*_Next;
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
