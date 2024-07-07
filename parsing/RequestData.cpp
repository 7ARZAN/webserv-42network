/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestData.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 23:58:04 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/07 00:05:44 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestData.hpp"

RequestData::RequestData() : _Size(0), _ClientIP(""), _Method(""), _Path(""), _FullPath(""), _Protocol(""), _Body(""), _Metadata(){
}

RequestData::RequestData(const std::string &clientIP) : _Size(0), _ClientIP(clientIP), _Method(""), _Path(""), _FullPath(""), _Protocol(""), _Body(""), _Metadata(){
}

RequestData::~RequestData(){
}

void	RequestData::setSize(size_t newsize){
	_Size = newsize;
}

void	RequestData::setClientIP(const std::string &newIP){
	_ClientIP = newIP;
}

void	RequestData::setMethod(const std::string &method){
	_Method = method;
}

void	RequestData::setPath(const std::string &path){
	_Path = path;
}

void	RequestData::setProtocol(const std::string &protocol){
	_Protocol = protocol;
}

void	RequestData::appendBody(const std::string &data){
	_Body += data;
}

void	RequestData::addMetaData(const std::string &key, const std::string &value){
	_Metadata[key] = value;
}

size_t	RequestData::getSize(void) const{
	return (_Size);
}

const std::string	RequestData::getClientIP(void) const{
	return (_ClientIP);
}

const std::string	RequestData::getMethod(void) const{
	return (_Method);
}

const std::string	RequestData::getPath(void) const{
	return (_Path);
}

const std::string	RequestData::getFullPath(void) const{
	return (_FullPath);
}

const std::string	RequestData::getProtocol(void) const{
	return (_Protocol);
}

const std::string	RequestData::getBody(void) const{
	return (_Body);
}

const std::string	RequestData::getMetadata(const std::string &key) const{
	std::map<std::string, std::string>::const_iterator it = _Metadata.find(key);
	if (it != _Metadata.end())
		return (it->second);
	return ("");
}
