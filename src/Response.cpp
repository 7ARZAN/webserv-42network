/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 02:44:37 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/19 01:57:50 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include <fstream>
#include <vector>

bool	Response::_MimeTypes(){
	std::ifstream	file;
	std::string		line;
	std::vector<std::string>	temp;

	file.open("MimeTypes");
	if (!file.is_open())
		return (false);
	while (std::getline(file, line)){
		temp = ohmysplit(line, "=");
		_MimeType[trim(temp[0], " ")] = trim(temp[1], " ");
	}
	file.close();
	return (true);
}

bool	Response::_StatusTypes(){
	std::ifstream	file;
	std::string		line;
	std::vector<std::string>	temp;

	file.open("HTTPstatus");
	if (!file.is_open())
		return (false);
	while (std::getline(file, line)){
		temp = ohmysplit(line, "=");
		_StatusType[StringToInteger(trim(temp[0], " "))] = trim(temp[1], " ");
	}
	file.close();
	return (true);
}

bool	Response::setMetadata(const std::string &key, const std::string &value){

	if (key.empty() || value.empty())
		return (false);
	_Metadata[key] = value;
	return (true);
}

bool	Response::setBody(const std::string &body){
	if (body.empty())
		return (false);
	_Body = body;
	setMetadata("Content-Length", std::to_string(_Body.size()));
	return (true);
}

std::string	Response::_GetFileExtension(const std::string &path){
	std::string	extension;

	if (path.empty())
		return ("text/html");
	if (path.find_last_of(".") != std::string::npos)
		extension = path.substr(path.find_last_of(".") + 1);
	return (extension);
}

std::string	Response::_GetPacketDate(){
	time_t		rawtime;
	struct tm	*timeinfo;
	char		buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime); // [Tue Nov 15 08:12:31 1994]
	strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S GMT", timeinfo); // format date to be like: "Tue, 15 Nov 1994 08:12:31 GMT"
	return (buffer);
}

void	Response::_GenerateHEAD(){
	std::map<std::string, std::string>::iterator	it;

	_HEAD = "HTTP/1.1 " + _statusCode + "\r\n";
	_HEAD += "Date: " + _GetPacketDate() + "\r\n";
	while (it = _Metadata.begin(), it != _Metadata.end()){
		_HEAD += it->first + ": " + it->second + "\r\n";
		it++;
	}
	_HEAD += "\r\n";
}

bool	Response::_GenerateResponsePacket(){
	if (_HEAD.empty())
		return (false);
	_ResponsePacket = _HEAD + _Body;
	return (true);
}

bool	Response::setStatusCode(int code){
	if (_StatusType.find(code) == _StatusType.end())
		return (false);
	_statusCode = std::to_string(code) + " " + _StatusType[code];
	return (true);
}

int	Response::getStatusCode(){
	std::string	code;

	code = _statusCode.substr(0, 3);
	return (StringToInteger(code));
}

bool	Response::sendResponse(int fd){
	if (_RequestPacket == NULL)
		return (false);
	_MimeTypes();
	_StatusTypes();
	_GenerateHEAD();
	_GenerateResponsePacket();
	if (write(fd, _ResponsePacket.c_str(), _ResponsePacket.size()) == -1) // send response to client [browser]
		return (false); // if failed to send response
	return (true);
}

bool	Response::Redirect(const std::string &uri, bool isPermanent){
	if (uri.empty())
		return false;
	if (isPermanent)
		setStatusCode(301);
	else
		setStatusCode(302);
	setMetadata("Location", uri);
	setMetadata("Content-Length", "0");
	setMetadata("Connection", "close");
	setBody("");
	_GenerateHEAD();
	_GenerateResponsePacket();
	return (true);
}

bool	Response::FileReader(const std::string &path){
	std::fstream	file;
	size_t			bytes;
	char			buffer[1024];

	if (path.empty())
		return (false);
	file.open(path, std::ios::in);
	if (!file.is_open())
		return (false);
	while (!file.eof()){
		file.read(buffer, 1024);
		bytes = file.gcount();
		_Body.append(buffer, bytes);
	}
	file.close();
	setMetadata("Content-Type", _MimeType[_GetFileExtension(path)]);
	setMetadata("Content-Length", std::to_string(_Body.size()));
	return (true);
}

Response::Response(){
	if (_MimeType.empty() || _StatusType.empty()){
		_MimeTypes();
		_StatusTypes();
	}
	_statusCode = "200 OK";
	_HEAD = "";
	_ResponsePacket = "";
	_Body = "";
	_RequestPacket = NULL;
	setMetadata("SERVER", "Webserv/1.0");
	
}

Response::~Response(){
}

void	Response::setRequest(Request &request){
	_RequestPacket = &request;
}

Request	*Response::getRequest(){
	return (_RequestPacket);
}
