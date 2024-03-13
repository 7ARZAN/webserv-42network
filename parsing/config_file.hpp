/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_file.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:40:39 by tarzan            #+#    #+#             */
/*   Updated: 2024/02/11 14:09:56 by tarzan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_FILE_HPP
#define CONFIG_FILE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>

class ConfigFile {
	public:
		ConfigFile(const std::string &filename);
		~ConfigFile();
		std::string get(const std::string &key) const;
		void	print() const;
		void	checker(const std::string &key, const std::string &value);
		void	save();
	private:
		std::string filename;
		std::map<std::string, std::string> data;
};

#endif
