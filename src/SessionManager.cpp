#include "../includes/SessionManager.hpp"
#include <cstdlib>
#include <sstream>

SessionManager::SessionManager() {
    std::srand(static_cast<unsigned int>(std::time(0)));
}

SessionManager::~SessionManager() {}

std::string SessionManager::generateSessionId() {
    std::stringstream ss;
    for (int i = 0; i < 16; ++i) {
        ss << std::hex << (std::rand() % 16);
    }
    return ss.str();
}

std::string SessionManager::createSession() {
    std::string sessionId = generateSessionId();
    while (_sessions.find(sessionId) != _sessions.end()) {
        sessionId = generateSessionId();
    }
    _sessions[sessionId] = std::map<std::string, std::string>();
    _sessionExpiries[sessionId] = std::time(0) + 3600; // 1 hour expiry
    return sessionId;
}

std::string SessionManager::getSessionData(const std::string &sessionId, const std::string &key) {
    cleanupExpiredSessions();
    std::map<std::string, std::map<std::string, std::string> >::iterator sessionIt = _sessions.find(sessionId);
    if (sessionIt == _sessions.end()) return "";
    std::map<std::string, std::string>::iterator dataIt = sessionIt->second.find(key);
    if (dataIt == sessionIt->second.end()) return "";
    return dataIt->second;
}

void SessionManager::setSessionData(const std::string &sessionId, const std::string &key, const std::string &value) {
    cleanupExpiredSessions();
    std::map<std::string, std::map<std::string, std::string> >::iterator sessionIt = _sessions.find(sessionId);
    if (sessionIt == _sessions.end()) return;
    sessionIt->second[key] = value;
}

void SessionManager::cleanupExpiredSessions() {
    time_t now = std::time(0);
    std::map<std::string, time_t>::iterator it = _sessionExpiries.begin();
    while (it != _sessionExpiries.end()) {
        if (it->second < now) {
            _sessions.erase(it->first);
            std::map<std::string, time_t>::iterator toErase = it;
            ++it;
            _sessionExpiries.erase(toErase);
        } else {
            ++it;
        }
    }
}
