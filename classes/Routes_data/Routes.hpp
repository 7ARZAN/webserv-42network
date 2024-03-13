/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Routes.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:23:07 by tarzan            #+#    #+#             */
/*   Updated: 2024/03/13 21:19:14 by tarzan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTES_DATA_HPP
# define ROUTES_DATA_HPP

# include <iostream>

class	Routes_data{
	private:
		std::string	_URL;
		std::string	_RootPath;
		enum		Methods{
			GET,
			POST,
			DELETE,
			NONE
		};
		Methods		_Methods;
		bool		_Brows;
		bool		_isRedirection;
		std::string _Redirect;
		Routes_data	*_Next;
		Routes_data	*_Prev;
	public:
		Routes_data(const std::string &url, const std::string &root);
		~Routes_data(void);
		void		setPrev(Routes_data *prevRoute);
		void		setUrl(const std::string &newUrl);
		void		setRoot(const std::string &newRoot);
		void		setMethod(const std::string &methodName);
		void		setBrowsing(bool status);
		void		setRedirection(const std::string &redirectionUrl);
		Routes_data	*setNext(Routes_data *nextRoute);
		const std::string	&getUrl(void) const;
		const std::string	&getRoot(void) const;
		const std::string	&getRedirection(void) const;
		bool				isRedirection(void) const;
		bool				useMethod(const std::string &methodName) const;
		Routes_data			*getNext(void);
		Routes_data			*getPrev(void);
		bool		isBrowsing(void) const;
};

#endif
