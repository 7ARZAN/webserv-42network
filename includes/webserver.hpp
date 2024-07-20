#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "../lib/libconfpp/includes/libconfpp.h"
#include "../includes/connection.hpp"
#include "RequestParsing.hpp"
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <iostream>
#include <map>
#include <fstream> 
#include <utility>
#include "log.hpp"
#include <string> 
#include <sstream>

#define HTTP_CODES	"200|201|202|203|204|205|206|207|208|226|" \
			"300|301|302|303|304|305|306|307|308|" \
			"400|401|402|403|404|405|406|407|408|409|410|411|412|413|414|415|416|417"

#define HTTP_MSG	"OK|Created|Accepted|Non-Authoritative Information|No Content|Reset Content|"\
			"Partial Content|Multi-Status|Already Reported|IM Used|" \
/* 300 */		"Multiple Choices|Moved Permanently|Found|See Other|Not Modified|Use Proxy|" \
			"Switch Proxy|Temporary Redirect|Permanent Redirect|" \
/* 400 */		"Bad Request|Unauthorized|Payment Required|Forbidden|Not Found|" \
			"Method Not Allowed|Not Acceptable|Proxy Authentication Required|" \
			"Request Timeout|Conflict|Gone|Length Required|Precondition Failed|" \
			"Payload Too Large|URI Too Long|Unsupported Media Type|Range Not Satisfiable|" \
			"Expectation Failed"

#define TYPE 		"3gp|3gpp|7z|ai|asf|asx|atom|avi|avif|bin|bmp|cco|crt|css|deb|der|dll|dmg|doc|ear|eot|eps|exe|flv|gif|hqx|htc|"\
			"htm|html|ico|img|iso|jad|jar|jardiff|jng|jnlp|jpeg|jpg|js|json|kar|kml|kmz|m3u8|m4a|m4v|mid|midi|mml|mng|" \
			"mov|mp3|mp4|mpeg|mpg|msi|msm|msp|odg|odp|ods|odt|ogg|pdb|pdf|pem|pl|pm|png|ppt|prc|ps|ra|rar|rpm|rss|rtf|run|" \
			"sea|shtml|sit|svg|svgz|swf|tcl|tif|tiff|tk|ts|txt|war|wasm|wbmp|webm|webp|wml|wmlc|wmv|woff|woff2|xhtml|xls|xml|xpi|xspf|zip"

#define MIME		"video/3gpp|video/3gpp|application/x-7z-compressed|application/postscript|video/x-ms-asf|video/x-ms-asf|application/atom+xml|video/x-msvideo|"\
			"image/avif|application/octet-stream|image/x-ms-bmp|application/x-cocoa|application/x-x509-ca-cert|text/css|application/octet-stream|"\
			"application/x-x509-ca-cert|application/octet-stream|application/octet-stream|application/msword|application/java-archive|application/vnd.ms-fontobject|"\
			"application/postscript|application/octet-stream|video/x-flv|image/gif|application/mac-binhex40|text/x-component|text/html|text/html|" \
			"image/x-icon|application/octet-stream|application/octet-stream|text/vnd.sun.j2me.app-descriptor|application/java-archive|application/x-java-archive-diff|"\
			"image/x-jng|application/x-java-jnlp-file|image/jpeg|image/jpeg|application/javascript|application/json|audio/midi|application/vnd.google-earth.kml+xml|"\
			"application/vnd.google-earth.kmz|application/vnd.apple.mpegurl|audio/x-m4a|video/x-m4v|audio/midi|audio/midi|text/mathml|video/x-mng|video/quicktime|"\
			"audio/mpeg|video/mp4|video/mpeg|video/mpeg|application/octet-stream|application/octet-stream|application/octet-stream|"\
			"application/vnd.oasis.opendocument.graphics|application/vnd.oasis.opendocument.presentation|application/vnd.oasis.opendocument.spreadsheet|"\
			"application/vnd.oasis.opendocument.text|audio/ogg|application/x-pilot|application/pdf|application/x-x509-ca-cert|application/x-perl|application/x-perl|" \
			"image/png|application/vnd.ms-powerpoint|application/x-pilot|application/postscript|audio/x-realaudio|application/x-rar-compressed|"\
			"application/x-redhat-package-manager|application/rss+xml|application/rtf|application/x-makeself|application/x-sea|text/html|"\
			"application/x-stuffit|image/svg+xml|image/svg+xml|application/x-shockwave-flash|application/x-tcl|image/tiff|image/tiff|application/x-tcl|video/mp2t|"\
			"text/plain|application/java-archive|application/wasm|image/vnd.wap.wbmp|video/webm|image/webp|text/vnd.wap.wml|application/vnd.wap.wmlc|video/x-ms-wmv|"\
			"font/woff|font/woff2|application/xhtml+xml|application/vnd.ms-excel|text/xml|application/x-xpinstall|application/xspf+xml|application/zip"


extern std::map<std::string, std::string> mime_types;
extern std::map<int, std::string> http_status;
extern ws_log logx;
extern bool	dirlist;

std::string	read_file(std::string filename);

#endif
