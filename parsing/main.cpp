/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:51:06 by tarzan            #+#    #+#             */
/*   Updated: 2024/03/20 02:44:16 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config_file.hpp"

int	main()
{
	ConfigFile config("config.conf");

	//redirected to the file meme.txt
	config.redirect("meme.txt");
	config.checker("server", "http://localhost:8080");
	config.checker("port", "8080");
	config.save();
	//config.print();
	return 0;
}
