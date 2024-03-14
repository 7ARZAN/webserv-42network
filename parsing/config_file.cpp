/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_file.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:33:07 by tarzan            #+#    #+#             */
/*   Updated: 2024/03/13 22:44:56 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config_file.hpp"

ConfigFile::ConfigFile(const std::string &filename) : filename(filename)
{
	std::ifstream	file(filename.c_str());
	std::string	line;

	while (std::getline(file, line)){
		if (line[0] == '#' || line.empty())
			continue;
		else if (std::count(line.begin(), line.end(), '=') == 1){
			std::string key = line.substr(0, line.find('='));
			std::string value = line.substr(line.find('=') + 1);
			data[key] = value;
		}
	}
	file.close();
}

ConfigFile::~ConfigFile(){
	save();
}

// std::string	ConfigFile::get(const std::string &key) const{
// 	std::map<std::string, std::string>::const_iterator it = data.find(key);
//
// 	if (it != data.end())
// 		return it->second;
// 	else
// 		return "Error: " + key + " not found";
// }

void	ConfigFile::checker(const std::string &key, const std::string &value){
	std::map<std::string, std::string>::iterator it = data.find(key);

	if (it != data.end())
		it->second = value;
	else
		data.insert(std::pair<std::string, std::string>(key, value));
}

void	ConfigFile::save(){
	std::ofstream file(filename.c_str());

	for (std::map<std::string, std::string>::const_iterator it = data.begin(); it != data.end(); ++it)
		file << it->first << "=" << it->second << std::endl;
}

void	ConfigFile::print() const{
	for (std::map<std::string, std::string>::const_iterator it = data.begin(); it != data.end(); ++it)
		std::cout << it->first << " = " << it->second << std::endl;
}
