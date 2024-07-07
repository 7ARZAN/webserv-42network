/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 03:40:31 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/05 06:09:31 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/request.hpp"
//
//
// //[get time function] is a function that return the current time in the format of the http date
// static std::string	get_time()
// {
// 	time_t	now;
// 	struct tm tstruct;
//
// 	now = time(0);
// 	char	buf[80];
// 	tstruct = *localtime(&now);
// 	strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", &tstruct);
// 	return buf;
// }

#include <iostream>
#include <string>
#include <sys/socket.h>


std::string	get_Request(int client){
	int	bytes;
	int	buffer_size = 1024;
	char	buffer[buffer_size + 1];
	std::string	request;

	bytes = recv(client, buffer, buffer_size, 0);
	if (bytes > 0)
		request.append(buffer, bytes);
	return request;
}

bool	Request_parser(int client, std::string &request){
	std::string	client_request;

	client_request = get_Request(client);
	return true;
}
