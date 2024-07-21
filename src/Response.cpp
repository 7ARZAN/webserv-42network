/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 02:44:37 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/21 05:26:03 by lmongol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Response.hpp"
#include "../includes/webserver.hpp"

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
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S GMT", timeinfo);
	return (buffer);
}

void	Response::_GenerateHEAD(){
	std::map<std::string, std::string>::iterator	it;

	_HEAD = "HTTP/1.1 " + _statusCode + "\r\n";
	_HEAD += "Date: " + _GetPacketDate() + "\r\n";
	it = _Metadata.begin();
	while (it != _Metadata.end()){
		_HEAD += it->first + ": " + it->second + "\r\n";
		it++;
	}
	_HEAD += "\r\n";
}

std::string Response::render_response(){
	std::string resp;
	if (_HEAD.empty())
		_GenerateHEAD();
	resp = _HEAD + _Body;
	return (resp);
}

bool	Response::setStatusCode(int code){
	if (http_status.find(code) == http_status.end())
		return (false);
	_statusCode = std::to_string(code) + " " + http_status[code];
	setBody(http_status[code]);
	return (true);
}

int	Response::getStatusCode(){
	std::string	code;

	code = _statusCode.substr(0, 3);
	return (std::atoi(code.c_str()));
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
	// _GenerateResponsePacket();
	return (true);
}


void	Response::handleResponse(){
	if (_RequestPacket == NULL)
		return ;
	if (_RequestPacket->getMethod() == "POST")
		POST();
	else if (_RequestPacket->getMethod() == "GET")
		GET();
	else if (_RequestPacket->getMethod() == "DELETE")
		DELETE();
}

Response::Response(Request *req){
	_statusCode = "200 OK";
	_HEAD = "";
	_ResponsePacket = "";
	_Body = "";
	_RequestPacket = req;
	setMetadata("SERVER", "Webserv/1.0");
}

Response::Response(int status_code){
	setStatusCode(status_code);
	_HEAD = "";
	_ResponsePacket = "";
	_Body = "<h1>" + http_status[status_code] + "</h1>";
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
