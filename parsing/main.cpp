/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:51:06 by tarzan            #+#    #+#             */
/*   Updated: 2024/03/13 22:43:04 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config_file.hpp"

int	main()
{
	ConfigFile config("config.conf");

	config.checker("server", "http://localhost:8080");
	config.checker("port", "8080");
	config.save();
	config.print();
	return 0;
}
