#ifndef SESSION_MANAGER_HPP
# define SESSION_MANAGER_HPP

# include <string>
# include <map>
# include <ctime>

class		SessionManager
{
	private:
	    std::map<std::string, std::map<std::string, std::string> > _sessions;
	    std::map<std::string, time_t> _sessionExpiries;

	    std::string generateSessionId();

	public:
	    SessionManager();
	    ~SessionManager();

	    std::string createSession();
	    std::string getSessionData(const std::string &sessionId, const std::string &key);
	    void setSessionData(const std::string &sessionId, const std::string &key, const std::string &value);
	    void cleanupExpiredSessions();
};

#endif
