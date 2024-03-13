/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SysData.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:06:52 by tarzan            #+#    #+#             */
/*   Updated: 2024/02/11 15:35:32 by tarzan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SysData.hpp"

SysData::SysData(){
	this->_MaxClientSize = 0;
	this->_CGI = false;
	this->_LogPath = "./Log";
}

SysData::~SysData(){
	if (this->_LogFile.is_open())
		this->_LogFile.close();
}

void	SysData::setCGI(const bool &cgi){
	if (cgi == true)
		this->_CGI = true;
	else
		this->_CGI = false;
}

void	SysData::setLogPath(const std::string &logpath){
	this->_LogPath = logpath;
}

void	SysData::setMaxClientSize(size_t maxclientsize){
	if (maxclientsize < 0)
		this->_MaxClientSize = 0;
	else
		this->_MaxClientSize = maxclientsize;
}

std::string	SysData::getCGI() const{
	if (this->_CGI == true)
		return ("on");
	else
		return ("off");
}

std::string	SysData::getLogPath() const{
	return (this->_LogPath);
}

size_t	SysData::getMaxClientSize() const{
	return (this->_MaxClientSize);
}

void	SysData::OpenLogFile(){
	if (this->_LogFile.is_open())
		this->_LogFile.close();
	this->_LogFile.open(this->_LogPath.c_str(), std::ios::app);
}

void	SysData::WriteLogFile(const std::string &log){
	if (this->_LogFile.is_open())
		this->_LogFile << log << std::endl;
	else
		std::cerr << "Error: Log file is not open" << std::endl;
}

void	SysData::CloseLogFile(){
	if (this->_LogFile.is_open())
		this->_LogFile.close();
	else
		std::cerr << "Error: Log file is not open" << std::endl;
}

int	main(){
	SysData sysdata;
	sysdata.setLogPath("./Log");
	sysdata.setCGI(true);
	sysdata.setMaxClientSize(0);
	std::cout << "CGI: " << sysdata.getCGI() << std::endl;
	std::cout << "LogPath: " << sysdata.getLogPath() << std::endl;
	std::cout << "MaxClientSize: " << sysdata.getMaxClientSize() << std::endl;
	sysdata.OpenLogFile();
	sysdata.WriteLogFile("Hello World");
	sysdata.WriteLogFile("im tarzan");
	//sysdata.CloseLogFile();
	return (0);
}
