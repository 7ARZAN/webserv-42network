#include "tools.hpp"

int	StringToInteger(const std::string &str){
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9'){
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

std::vector<std::string>	ohmysplit(const std::string &str, const std::string &sep){
	std::vector<std::string>	result;
	size_t		start;
	size_t		end;

	start = 0;
	end = 0;
	while (end != std::string::npos){
		end = str.find(sep, start);
		result.push_back(str.substr(start, end - start));
		start = end + sep.size();
	}
	return (result);
}

std::string	trim(const std::string &str, const std::string &sep){
	size_t	start;
	size_t	end;

	start = str.find_first_not_of(sep);
	end = str.find_last_not_of(sep);
	if (start == std::string::npos)
		return ("");
	return (str.substr(start, end - start + 1));
}
