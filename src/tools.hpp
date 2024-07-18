#ifndef TOOLS_HPP
# define TOOLS_HPP

# include <iostream>
# include <string>
# include <vector>


int	StringToInteger(const std::string &str);
std::vector<std::string>	ohmysplit(const std::string &str, const std::string &delim);
std::string	trim(const std::string &str, const std::string &delim);

#endif
