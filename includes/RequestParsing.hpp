/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParsing.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 02:44:50 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/31 00:14:51 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTPARSING_HPP
# define REQUESTPARSING_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <climits>
#include "../lib/libconfpp/includes/config.h"

struct ws_delivery;

class	Request
{
	private:
		ws_config_table	*config;
		ws_delivery	*request;
		ws_delivery	*response;
		std::string	_Method;
		std::string	_Uri;
		std::string	_Version;
		std::string	_Body;
		std::string	_Query;
		std::map<std::string, std::string>	_Metadata;

	public:
		Request(ws_delivery *request, ws_delivery *response, ws_config_table *config);
		~Request();

		// basically setters
		void	setMethod(const std::string &method);
		void	setUri(const std::string &uri);
		void	setBody(const std::string &body);
		void	setVersion(const std::string &version);
		void	setMetadata(const std::string &key, const std::string &value);

		bool	parseRequest();
		bool	parseMetadata(std::stringstream &header);

		std::string	getquery();
		std::string	getMethod() const;
		ws_config_table	*getConfig();
		std::string	getUri() const;
		std::string	&getBody();
		std::string	getVersion() const;
		std::string	getMetadata(const std::string &key) const;
};

std::vector<std::string>	ohmysplit(const std::string &str, const std::string &sep);

#endif
