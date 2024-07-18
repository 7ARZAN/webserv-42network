/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParsing.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 02:44:50 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/18 13:09:04 by tarzan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTPARSING_HPP
# define REQUESTPARSING_HPP

# include <iostream>
# include <string>
# include <map>
# include "tools.hpp"

class	Request
{
	private:
		std::string	_RequestPacket;
		std::string	_Method;
		std::string	_Uri;
		std::string	_Version;
		std::string	_Body;
		std::map<std::string, std::string>	_Metadata;
		std::map<std::string, std::string>	_cookies;

	public:
		Request();
		~Request();

		void	appendRequestPacket(const std::string &requestPacket);

		void	setMethod(const std::string &method);
		void	setUri(const std::string &uri);
		void	setBody(const std::string &body);
		void	setVersion(const std::string &version);
		void	setMetadata(const std::string &key, const std::string &value);
		void	setCookies(const std::string &key, const std::string &value);

		bool	parseRequest();
		bool	parseMetadata(std::stringstream &header);
		bool	parseCookies();

		std::string	getMethod() const;
		std::string	getUri() const;
		std::string	getBody() const;
		std::string	getVersion() const;
		std::string	getMetadata(const std::string &key) const;
		std::map<std::string, std::string>	getCookies() const;
};

#endif
