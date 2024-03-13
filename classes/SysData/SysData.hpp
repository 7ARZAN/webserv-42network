/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SysData.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:55:36 by tarzan            #+#    #+#             */
/*   Updated: 2024/02/11 15:34:48 by tarzan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSDATA_HPP
# define SYSDATA_HPP

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <vector>

class	SysData{
	private:
		bool		_CGI;
		std::string	_LogPath;
		std::fstream	_LogFile;
		size_t		_MaxClientSize;
	public:
		SysData();
		~SysData();
		void	setCGI(const bool &cgi);
		void	setLogPath(const std::string &logpath);
		void	setMaxClientSize(size_t maxclientsize);
		std::string	getCGI() const;
		std::string	getLogPath() const;
		size_t	getMaxClientSize() const;
		void	OpenLogFile();
		void	WriteLogFile(const std::string &log);
		void	CloseLogFile();
};

#endif
