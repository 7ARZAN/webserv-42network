/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Routes.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:23:07 by tarzan            #+#    #+#             */
/*   Updated: 2024/03/14 03:53:03 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTES_DATA_HPP
# define ROUTES_DATA_HPP

# include <iostream>

class	Routes_data{
	private:
		std::string	_URL; //url of the route (ex: /index.html)
		std::string	_RootPath; //root path of the route (where the files are)
		enum		Methods{
			GET,
			POST,
			DELETE,
			NONE
		};
		Methods		_Methods; //method of the route (GET, POST, DELETE)
		bool		_Brows; //if the route is a browsing route or not
		bool		_isRedirection; //if the route is a redirection route or not
		std::string _Redirect; //the redirection url
		Routes_data	*_Next; //next route in the list
		Routes_data	*_Prev; //previous route in the list
	public:
		Routes_data(const std::string &url, const std::string &root); //constructor
		~Routes_data(void); //destructor
		void		setPrev(Routes_data *prevRoute); //set the previous route
		void		setUrl(const std::string &newUrl); //set the url of the route
		void		setRoot(const std::string &newRoot); //set the root path of the route
		void		setMethod(const std::string &methodName); //set the method of the route
		void		setBrowsing(bool status); //set the browsing status of the route
		void		setRedirection(const std::string &redirectionUrl); //set the redirection url of the route
		Routes_data	*setNext(Routes_data *nextRoute); //set the next route
		const std::string	&getUrl(void) const; //get the url of the route
		const std::string	&getRoot(void) const; //get the root path of the route
		const std::string	&getRedirection(void) const; //get the redirection url of the route
		bool				isRedirection(void) const; //check if the route is a redirection route
		bool				useMethod(const std::string &methodName) const; //check if the route uses a specific method
		Routes_data			*getNext(void); //get the next route
		Routes_data			*getPrev(void); //get the previous route
		bool		isBrowsing(void) const; //check if the route is a browsing route (for autoindex)
};

#endif
