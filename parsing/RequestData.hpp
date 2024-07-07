/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 23:45:43 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/07 00:02:17 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTDATA_HPP
# define REQUESTDATA_HPP

# include <iostream>
# include <map>

typedef enum Methods
{
	GET,
	POST,
	DELETE
}Methods;

class RequestData
{
	private:
		size_t		_Size;
		std::string	_ClientIP;
		std::string 	_Method;
		std::string 	_Path;
		std::string 	_FullPath;
		std::string	_Protocol;
		std::string	_Body;
		std::map<std::string, std::string>	_Metadata;
	public:

		RequestData(void);
		RequestData(const std::string &clientIP);
		~RequestData(void);
		void	setSize(size_t newsize);
		void	setClientIP(const std::string &newIP);
		void	setMethod(const std::string &method);
		void	setPath(const std::string &path);
		void	setProtocol(const std::string &protocol);
		void	appendBody(const std::string &data);
		void	addMetaData(const std::string &key, const std::string &value);
		size_t		getSize(void) const;
		const std::string	getClientIP(void) const;
		const std::string	getMethod(void) const;
		const std::string	getPath(void) const;
		const std::string	getFullPath(void) const;
		const std::string	getProtocol(void) const;
		const std::string	getBody(void) const;
		const std::string	getMetadata(const std::string &key) const;
};

#endif
