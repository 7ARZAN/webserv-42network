/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParsing.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:51:39 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/18 13:10:02 by tarzan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParsing.hpp"
#include <vector>
#include <sstream>

std::string	correct_Format(const std::string &str)
{
	size_t	length = 0;

	for (; str[length]; length++){
		if (str[length] == '\r')
			break;
	}

	if (length != str.length())
		return (str.substr(0, length));
	return (str);
}

void	Request::appendRequestPacket(const std::string &requestPacket){
	_RequestPacket.append(requestPacket);
}

void	Request::setMethod(const std::string &method){
	_Method = method;
}

void	Request::setUri(const std::string &uri){
	_Uri = uri;
}

void	Request::setBody(const std::string &body){
	_Body = body;
}

void	Request::setVersion(const std::string &version){
	_Version = version;
}

void	Request::setMetadata(const std::string &key, const std::string &value){
	_Metadata[key] = value;
}

void	Request::setCookies(const std::string &key, const std::string &value){
	_cookies[key] = value;
}

bool	Request::parseRequest(){
	std::stringstream	header;
	std::string	line;
	std::vector<std::string> list;

	header << _RequestPacket.substr(0, _RequestPacket.find("\r\n\r\n"));
	_Body = _RequestPacket.substr(_RequestPacket.find("\r\n\r\n") + 4);
	std::getline(header, line);
	list = ohmysplit(line, " ");
	if (list.size() != 3)
		return (false);
	setMethod(correct_Format(list[0]));
	setUri(correct_Format(list[1]));
	setVersion(correct_Format(list[2]));
	return parseMetadata(header);
}


bool	Request::parseMetadata(std::stringstream &header){
	std::string	line;
	std::vector<std::string> list;

	while (getline(header, line)){
		list = ohmysplit(line, ": ");
		if (list.size() != 2)
			return (false);
		setMetadata(correct_Format(list[0]), correct_Format(list[1]));
		if (list[0] == "Content-Type"){
			list = ohmysplit(list[1], "; ");
			if (list.size() != 2)
				return (false);
			list = ohmysplit(list[1], "=");
			if (list.size() != 2)
				return (false);
			setMetadata(correct_Format(list[0]), correct_Format(list[1]));
		}
	}
	return (true);
}

bool	Request::parseCookies(){
	std::string	cookies;
	std::vector<std::string>	list;
	std::vector<std::string>	cookie;
	size_t	index;

	index = -1;
	cookies = getMetadata("Cookie");
	list = ohmysplit(cookies, "; ");
	while (++index < list.size()){
		cookie = ohmysplit(list[index], "=");
		if (cookie.size() == 2)
			_cookies[cookie[0]] = cookie[1];
	}
	return (true);
}

std::string	Request::getMethod() const{
	return (_Method);
}

std::string	Request::getUri() const{
	return (_Uri);
}

std::string	Request::getBody() const{
	return (_Body);
}

std::string	Request::getVersion() const{
	return (_Version);
}

std::string	Request::getMetadata(const std::string &key) const{
	if (_Metadata.find(key) == _Metadata.end())
		return ("");
	return (_Metadata.at(key));
}

std::map<std::string, std::string>	Request::getCookies() const{
	return (_cookies);
}

Request::Request(){
	_RequestPacket = "";
	_Method = "";
	_Uri = "";
	_Version = "";
	_Body = "";
}

Request::~Request(){
}

// int	main(){
// 	Request	req;
// 	std::string	requestPacket = "POST / HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: curl/7.68.0\r\nAccept: */*\r\nContent-Length: 5\r\nContent-Type: application/x-www-form-urlencoded; boundary=----------78678698978978344 \r\n\r\nhello POST / HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: curl/7.68.0\r\nAccept: */*\r\nContent-Length: 5\r\nContent-Type: application/x-www-form-urlencoded; boundary=----------78678698978978344 \r\n\r\nhello";
//
// 	req.appendRequestPacket(requestPacket);
// 	req.parseRequest();
// 	//req.parsemetaData();
// 	//req.parseBody();
// 	std::cout << "[Method]: "<< req.getMethod() << std::endl;
// 	std::cout << "[Uri]:" << req.getUri() << std::endl;
// 	std::cout << "[Body]: " <<req.getBody() << std::endl;
// 	std::cout << "[Version]: " << req.getVersion() << std::endl;
// 	std::cout << "[Host]: " << req.getmetaData("Content-Type") << '\n';
// 	std::cout << "[Host]: " << req.getmetaData("boundary") << '\n';
// }
