/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 02:45:14 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/31 00:36:59 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <string>
# include <map>
# include <vector>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <fstream>
# include <string.h>
# include <unistd.h>
# include "RequestParsing.hpp"

# define STAT_FAIL 1
# define STAT_SUCCESS 0

class SessionManager;

class Cookie {
	private:
		std::string _name;
		std::string _value;
		std::string _expires;
		std::string _path;
		bool _secure;
		bool _httpOnly;

	public:
		Cookie();
		~Cookie();

		bool setName(const std::string &name);
		bool setValue(const std::string &value);
		bool setExpires(const std::string &expires);
		bool setPath(const std::string &path);
		void setSecure(bool secure);
		void setHttpOnly(bool httpOnly);

		std::string serialize() const;
};

class Response {
	private:
		Request *_RequestPacket;
		std::string _statusCode;
		std::string _ResponsePacket;
		std::string _Body;
		std::string _HEAD;
		std::vector<Cookie> _Cookies;
		std::map<std::string, std::string> _Metadata;
		SessionManager *_sessionManager;

		std::string _GetPacketDate();
		void _GenerateHEAD();
		std::string _GetFileExtension(const std::string &path);

	public:
		Response(Request *req, SessionManager *sessionManager);
		Response(int status_code);
		~Response();

		int getStatusCode();
		bool setStatusCode(int code);

		bool setMetadata(const std::string &key, const std::string &value);
		bool setBody(const std::string &informations);

		bool sendResponse(int fd);
		bool Redirect(const std::string &uri, bool isPermanent);

		void setRequest(Request &request);
		Request *getRequest();

		void handleResponse();

		void addCookie(const Cookie &cookie);
		std::string createSession();
		std::string getSessionData(const std::string &sessionId, const std::string &key);
		void setSessionData(const std::string &sessionId, const std::string &key, const std::string &value);

		std::string render_response();
		void DELETE();
		void GET();
		void POST();
		void POSTFILE(std::string boundary);
};

bool isExist(const std::string &fullPath);
bool is_dir(std::string path);

#endif
