/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 02:44:37 by elakhfif          #+#    #+#             */
/*   Updated: 2024/07/31 00:17:14 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Response.hpp"
#include "../includes/webserver.hpp"
#include "../includes/SessionManager.hpp"
#include <ctime>
#include <cstdlib>

Cookie::Cookie() : _secure(false), _httpOnly(false) {}

Cookie::~Cookie() {}

bool Cookie::setName(const std::string &name) {
    if (name.empty() || name.find('=') != std::string::npos) return false;
    _name = name;
    return true;
}

bool Cookie::setValue(const std::string &value) {
    if (value.empty()) return false;
    _value = value;
    return true;
}

bool Cookie::setExpires(const std::string &expires) {
    if (expires.empty()) return false;
    _expires = expires;
    return true;
}

bool Cookie::setPath(const std::string &path) {
    if (path.empty() || path[0] != '/') return false;
    _path = path;
    return true;
}

void Cookie::setSecure(bool secure) {
    _secure = secure;
}

void Cookie::setHttpOnly(bool httpOnly) {
    _httpOnly = httpOnly;
}

std::string Cookie::serialize() const {
    std::string result = _name + "=" + _value;
    if (!_expires.empty()) result += "; Expires=" + _expires;
    if (!_path.empty()) result += "; Path=" + _path;
    if (_secure) result += "; Secure";
    if (_httpOnly) result += "; HttpOnly";
    return result;
}

bool Response::setMetadata(const std::string &key, const std::string &value) {
    if (key.empty() || value.empty()) return false;
    _Metadata[key] = value;
    return true;
}

bool Response::setBody(const std::string &body) {
    _Body = body;
    setMetadata("Content-Length", std::to_string(_Body.size()));
    return true;
}

std::string Response::_GetFileExtension(const std::string &path) {
    if (path.empty()) return "text/html";
    size_t pos = path.find_last_of(".");
    if (pos == std::string::npos) return "text/html";
    return path.substr(pos + 1);
}

std::string Response::_GetPacketDate() {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S GMT", timeinfo);
    return buffer;
}

void Response::_GenerateHEAD() {
    _HEAD = "HTTP/1.1 " + _statusCode + "\r\n";
    _HEAD += "Date: " + _GetPacketDate() + "\r\n";
    std::map<std::string, std::string>::iterator it = _Metadata.begin();
    while (it != _Metadata.end()) {
        _HEAD += it->first + ": " + it->second + "\r\n";
        ++it;
    }
    for (std::vector<Cookie>::const_iterator cit = _Cookies.begin(); cit != _Cookies.end(); ++cit) {
        _HEAD += "Set-Cookie: " + cit->serialize() + "\r\n";
    }
    _HEAD += "\r\n";
}

std::string Response::render_response() {
    if (_HEAD.empty()) _GenerateHEAD();
    return _HEAD + _Body;
}

bool Response::setStatusCode(int code) {
    if (http_status.find(code) == http_status.end()) return false;
    _statusCode = std::to_string(code) + " " + http_status[code];
    setBody(http_status[code]);
    return true;
}

int Response::getStatusCode() {
    return std::atoi(_statusCode.substr(0, 3).c_str());
}

bool Response::Redirect(const std::string &uri, bool isPermanent) {
    if (uri.empty()) return false;
    setStatusCode(isPermanent ? 301 : 302);
    setMetadata("Location", uri);
    setMetadata("Content-Length", "0");
    setMetadata("Connection", "close");
    setBody("");
    _GenerateHEAD();
    return true;
}

void Response::handleResponse() {
    if (!_RequestPacket) return;
    if (_RequestPacket->getMethod() == "POST") POST();
    else if (_RequestPacket->getMethod() == "GET") GET();
    else if (_RequestPacket->getMethod() == "DELETE") DELETE();
}

void Response::addCookie(const Cookie &cookie) {
    _Cookies.push_back(cookie);
}

std::string Response::createSession() {
    return _sessionManager->createSession();
}

std::string Response::getSessionData(const std::string &sessionId, const std::string &key) {
    return _sessionManager->getSessionData(sessionId, key);
}

void Response::setSessionData(const std::string &sessionId, const std::string &key, const std::string &value) {
    _sessionManager->setSessionData(sessionId, key, value);
}

Response::Response(Request *req, SessionManager *sessionManager) : _sessionManager(sessionManager) {
    _statusCode = "200 OK";
    _HEAD = "";
    _ResponsePacket = "";
    _Body = "";
    _RequestPacket = req;
    setMetadata("Server", "Webserv/1.0");
    Cookie sessionCookie;
    sessionCookie.setName("session");
    sessionCookie.setValue(createSession());
    sessionCookie.setPath("/");
    sessionCookie.setHttpOnly(true);
    addCookie(sessionCookie);
}

Response::Response(int status_code) : _sessionManager(0) {
    setStatusCode(status_code);
    _HEAD = "";
    _ResponsePacket = "";
    _Body = "<h1>" + http_status[status_code] + "</h1>";
    setMetadata("Server", "Webserv/1.0");
}

Response::~Response() {}

void Response::setRequest(Request &request) {
    _RequestPacket = &request;
}

Request *Response::getRequest() {
    return _RequestPacket;
}
