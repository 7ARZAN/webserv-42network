/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:51:06 by tarzan            #+#    #+#             */
/*   Updated: 2024/03/30 02:20:32 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config_file.hpp"
#include <fcntl.h>

int	main()
{
	ConfigFile config("config.conf");

	if (open("config.conf", O_RDONLY) == -1){
		std::cout << "File config.conf not found" << std::endl;
		return 1;
	}
	//redirected to the file meme.txt
	config.redirect("meme.txt");
	config.checker("server", "http://localhost:8080");
	config.checker("port", "8080");
	config.save();
	//config.print();
	return 0;
}
