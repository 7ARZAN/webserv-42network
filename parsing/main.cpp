/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:51:06 by tarzan            #+#    #+#             */
/*   Updated: 2024/03/13 21:00:25 by tarzan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config_file.hpp"

int	main()
{
	ConfigFile config("config.conf");

	//config.checker("server", "http://localhost:8080");
	//config.checker("port", "8080");
	config.save();
	config.print();
	if (true)
		std::cout << "Parsing is done successfully" << std::endl;
	return 0;
}
