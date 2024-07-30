/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParsing.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:51:39 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/31 00:15:10 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RequestParsing.hpp"
#include "../includes/Response.hpp"
#include "../includes/webserver.hpp"
#include "../includes/connection.hpp"

std::vector<std::string>	ohmysplit(const std::string &str, const std::string &sep)
{
	size_t						start = 0;
	size_t						end = 0;
	std::string					holder;
	std::vector<std::string>	result;

	do{
		end = str.find(sep, start);

		holder = str.substr(start, end - start);
		if (holder[holder.length() - 1] == '\r')
			holder[holder.length() - 1] = '\0';

		result.push_back(holder);
		start = end + sep.length();
	} while (end != std::string::npos);

	return (result);
}

std::string	correct_Format(const std::string &str)
{
	size_t	length;

	length = -1;
	while (str[++length])
		if (str[length] == '\r')
			break;

	if (length != str.length())
		return (str.substr(0, length));
	return (str);
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

std::string Request::getquery(){
	return (this->_Query);
}

bool	Request::parseRequest(){
	std::stringstream	header;
	std::string	line;
	std::vector<std::string>	query;
	std::vector<std::string> list;
	ssize_t		body_size;

	if (request->status == BODY_READ){
		_Body += request->buffer;
		request->buffer.erase();
		request->status = READY;
		return (true);
	}
	header << request->delivery.substr(0, request->delivery.find("\r\n\r\n"));
	std::getline(header, line);
	list = ohmysplit(line, " ");
	if (list.size() != 3)
		return (false);
	setMethod(correct_Format(list[0]));
	if (_Method != "POST" && _Method != "GET" && _Method != "DELETE")
		throw (Response(501));
	if (_Method == "GET" && list[1].find("?") != std::string::npos){
		query = ohmysplit(list[1], "?");
		if (query.size() != 2)
			throw (Response(400));
		setUri(correct_Format(query[0]));
		this->_Query = query[1];
	}
	else
		setUri(correct_Format(list[1]));
	if (_Uri.size() > PATH_MAX)
		throw (Response(415));
	setVersion(correct_Format(list[2]));
	if (parseMetadata(header) == false)
		throw (Response(400));
	if (getMetadata("Content-Length").empty() == true && _Method == "POST"){
		logx.error(getMetadata("Accept"));
		throw (Response(411));
	}
	body_size = std::atoi(getMetadata("Content-Length").c_str());
	if (body_size > INT_MAX || body_size < 0 || getMetadata("Content-Length").size() > 9)
		throw (Response(413));
	if (body_size <= (int) request->buffer.size()){
		_Body = request->buffer.substr(0, body_size);
		request->buffer.erase(0, body_size);
		request->status = READY;
	}
	else{
		_Body = request->buffer;
		request->buffer.erase();
		request->status = BODY_READ;
	}
	return (true);
}

ws_config_table	*Request::getConfig(){
	return (this->config);
}

bool	Request::parseMetadata(std::stringstream &header){
	std::string	line;
	std::vector<std::string> list;

	while (getline(header, line)){
		list = ohmysplit(line, ": ");
		if (list.size() != 2)
			return (false);
		setMetadata(correct_Format(list[0]), correct_Format(list[1]));
	}
	return (true);
}

std::string	Request::getMethod() const{
	return (_Method);
}

std::string	Request::getUri() const{
	return (_Uri);
}

std::string	&Request::getBody(){
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

Request::Request(ws_delivery *request, ws_delivery *response, ws_config_table *table){
	this->config = table;
	this->request = request;
	this->response = response;
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
