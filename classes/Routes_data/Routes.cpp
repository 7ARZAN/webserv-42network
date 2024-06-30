/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Routes.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:31:37 by tarzan            #+#    #+#             */
/*   Updated: 2024/06/30 03:51:24 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Routes.hpp"
#include <iostream>

Routes_data::Routes_data(const std::string &url, const std::string &root)
	: _URL(url), _RootPath(root), _Brows(false), _isRedirection(false), _Next(NULL), _Prev(NULL){}

Routes_data::~Routes_data(void){}

void	Routes_data::setUrl(const std::string &newUrl){
	this->_URL = newUrl;
}

void	Routes_data::setRoot(const std::string &newRoot){
	this->_RootPath = newRoot;
}

void	Routes_data::setPrev(Routes_data *prevRoute){
	this->_Prev = prevRoute;
}

void	Routes_data::setMethod(const std::string &methodName){
	std::string		method = methodName;
	if (method == "GET")
		this->_Methods = GET;
	else if (method == "POST")
		this->_Methods = POST;
	else if (method == "DELETE")
		this->_Methods = DELETE;
	else
		this->_Methods = NONE;
}

void	Routes_data::setBrowsing(bool status){
	this->_Brows = status;
}

void	Routes_data::setRedirection(const std::string &redirectionUrl){
	this->_isRedirection = true;
	this->_Redirect = redirectionUrl;
}

Routes_data	*Routes_data::setNext(Routes_data *nextRoute){
	this->_Next = nextRoute;
	return (this->_Next);
}

const std::string	&Routes_data::getUrl(void) const{
	return (this->_URL);
}

const std::string	&Routes_data::getRoot(void) const{
	return (this->_RootPath);
}

const std::string	&Routes_data::getRedirection(void) const{
	return (this->_Redirect);
}

bool	Routes_data::isRedirection(void) const{
	return (this->_isRedirection);
}

bool	Routes_data::isBrowsing(void) const{
	return (this->_Brows);
}

bool	Routes_data::useMethod(const std::string &methodName) const{
	if (methodName == "GET" && this->_Methods == GET)
		return (true);
	else if (methodName == "POST" && this->_Methods == POST)
		return (true);
	else if (methodName == "DELETE" && this->_Methods == DELETE)
		return (true);
	return (false);
}

Routes_data	*Routes_data::getNext(void){
	return (this->_Next);
}

Routes_data	*Routes_data::getPrev(void){
	return (this->_Prev);
}

std::ostream	&operator<<(std::ostream &out, const Routes_data &route){
	out << "URL: " << route.getUrl() << std::endl;
	out << "Root: " << route.getRoot() << std::endl;
	out << "Method: ";
	if (route.useMethod("GET"))
		out << "GET" << std::endl;
	else if (route.useMethod("POST"))
		out << "POST" << std::endl;
	else if (route.useMethod("DELETE"))
		out << "DELETE" << std::endl;
	else
		out << "NONE" << std::endl;
	out << "Browsing: " << route.isBrowsing() << std::endl;
	out << "Redirection: " << route.isRedirection() << std::endl;
	if (route.isRedirection())
		out << "Redirect to: " << route.getRedirection() << std::endl;
	return (out);
}

int		main(void){
	Routes_data	route("/index.html", "/home/user");
	route.setMethod("GET");
	route.setBrowsing(true);
	route.setRedirection("/home/user/redirect");
	std::cout << route << std::endl;
	return (0);
}
