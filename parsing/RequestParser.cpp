/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:10:16 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/07 00:16:31 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParser.hpp"
#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>

static std::string	readRequest(int fd)
{
	std::string	request;
	int			ret;
	int			maxSize = 1024;
	char		buffer[maxSize];

	ret = read(fd, buffer, maxSize);
	if (ret == -1){
		std::cerr << "Error: read failed" << std::endl;
		exit(1);
	}
	request = buffer;
	return (request);
}

static void	getBody(const std::string &packet, RequestData &data){
	std::string	Body = getMetadata("boundary");
	size_t		pos = packet.find(Body);

	if (pos == std::string::npos)
		throw std::runtime_error("Error: Boundary not found");
	pos += Body.size();
	data.body = packet.substr(pos);
}


int	main(void)
{
	int		fd = open("request.txt", O_RDONLY);
	std::string	request = readRequest(fd);
	std::cout << request << std::endl;
	close(fd);
	return (0);
}
