/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 05:57:08 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/05 06:00:19 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <cstdarg>
# include <string>
# include <vector>
# include <sstream>

void	msg(std::ostream &os, const char *format, ...){
	va_list	args;

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
}

std::vector<std::string>	split(const std::string &str, char delim){
	std::vector<std::string>	result;
	std::string::size_type		start = 0;
	std::string::size_type		end = 0;

	while ((end = str.find(delim, start)) != std::string::npos){
		result.push_back(str.substr(start, end - start));
		start = end + 1;
	}
	result.push_back(str.substr(start));

	return result;
}

bool	has_ONE_value(const std::string &option, const std::string &value, size_t &file_line){
	if (split(value, '|').size() != 1){
		msg(std::cout, "%I The \"%s\" option must have only one value", file_line, option.c_str());
		msg(std::cerr, "%E Invalid value at line %I", option.c_str(), file_line);
		return (false);
	}
	return (true);
}

std::string	trim(const std::string &str, const std::string &list){
	std::string::size_type	start = str.find_first_not_of(list);
	std::string::size_type	end = str.find_last_not_of(list);

	if (start == std::string::npos)
		return "";
	return str.substr(start, end - start + 1);
}

std::string	INT_2_STRING(int value){
	std::stringstream	ss;

	ss << value;
	return ss.str();

}

int	STRING_2_INT(const std::string &str){
	std::stringstream	ss(str);
	int					value;

	ss >> value;
	return value;
}
