Webserv

Webserv is a lightweight, high-performance HTTP/1.1 web server written in C++98. Designed for simplicity and efficiency, it supports GET, POST, and DELETE methods, CGI execution, file uploads, directory listing, and session management. Built with a focus on robustness and extensibility, Webserv is ideal for educational purposes, small-scale deployments, or as a foundation for custom web server projects.
Table of Contents

Features
Installation
Usage
Configuration
Session Management
Contributing
License
Acknowledgements

Features

HTTP/1.1 Compliance: Supports GET, POST, and DELETE methods with proper status code handling.
CGI Support: Executes scripts in PHP, Python, Perl, Ruby, and custom CGI programs.
File Uploads: Handles multipart/form-data for file uploads with configurable upload directories.
Directory Listing: Optional auto-indexing for directories without an index file.
Session Management: Secure session handling with server-side storage and cookie-based tracking.
Configuration: Flexible configuration via a custom .conf file for ports, root directories, and more.
Logging: Configurable logging levels (ERROR, WARN, INFO, DEBUG) with file and console output.
Non-blocking I/O: Efficient handling of multiple connections using poll.
C++98 Standard: Ensures compatibility with older compilers and environments.

Installation
Prerequisites

Compiler: A C++98-compliant compiler (e.g., g++).
Operating System: Linux or Unix-like system (tested on Ubuntu).
Dependencies: Standard C++ library, POSIX libraries (sys/socket.h, poll.h, etc.).

Building

Clone the repository:
git clone https://github.com/yourusername/webserv.git
cd webserv


Compile the source code:
make

This will generate the webserv executable.

(Optional) Install dependencies for CGI scripts (e.g., PHP, Python):
sudo apt-get install php python3 perl ruby



Usage
Run the web server by providing a configuration file:
./webserv config/ws_configuration.conf

The server will listen on the ports specified in the configuration file and serve content from the configured root directory.
Example Requests

GET a file:
curl http://localhost:8080/index.html


POST a file:
curl -F "file=@localfile.txt" http://localhost:8080/upload


DELETE a resource:
curl -X DELETE http://localhost:8080/file.txt



Configuration
Webserv uses a .conf file to configure server settings. Below is an example configuration:
[default]
log_path = logs/webserv.log
log_level = INFO
dirlist = true

[server1]
port = 8080
root_dir = www
upload_dir = www/uploads
max_connections = 100
req_timeout = 30
PHPCGI = /usr/bin/php
PYCGI = /usr/bin/python3

Configuration Options



Key
Description
Example Value



log_path
Path to the log file
logs/webserv.log


log_level
Logging level (ERROR, WARN, INFO, DEBUG)
INFO


dirlist
Enable directory listing (true/false)
true


port
Port to listen on
8080


root_dir
Root directory for serving files
www


upload_dir
Directory for uploaded files
www/uploads


max_connections
Maximum simultaneous connections
100


req_timeout
Request timeout in seconds
30


PHPCGI
Path to PHP CGI executable
/usr/bin/php


PYCGI
Path to Python CGI executable
/usr/bin/python3


Place your configuration file in the config/ directory or specify a custom path when running the server.
Session Management
Webserv includes a robust session management system:

Session Creation: Each client receives a unique session ID stored in a session cookie.
Session Storage: Session data is stored server-side in an in-memory std::map.
Expiration: Sessions expire after 1 hour (configurable via code).
Usage Example:// In a CGI script or custom handler
std::string sessionId = response.createSession();
response.setSessionData(sessionId, "username", "tarzan");
std::string username = response.getSessionData(sessionId, "username");



To use sessions in CGI scripts, parse the session cookie and query the server for session data.
Contributing
We welcome contributions to Webserv! To contribute:

Fork the repository.
Create a feature branch:git checkout -b feature/your-feature


Commit your changes:git commit -m "Add your feature"


Push to the branch:git push origin feature/your-feature


Open a Pull Request.

Please follow the Contributor Covenant Code of Conduct.
Development Guidelines

Write C++98-compliant code.
Include unit tests for new features.
Update documentation for any changes.
Ensure no memory leaks (use valgrind).

License
Webserv is licensed under the MIT License. See the LICENSE file for details.
Acknowledgements

Inspired by classic web servers like Nginx and Apache.
Built as an educational project to explore HTTP and socket programming.
Special thanks to the open-source community for tools and libraries.


Feel free to star ⭐ this repository if you find it useful!


# lighttpd clone works perfectly with Brave Browser !!
