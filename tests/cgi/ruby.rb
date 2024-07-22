#!/usr/bin/env ruby

require 'cgi'

# Create a new CGI object

# Output the HTML form for POST requests
puts "<html><body>"
puts "<h2>Enter your name via POST:</h2>"
puts "<form action=\"ruby.rb\" method=\"post\">"
puts "  <label for=\"name\">Name:</label>"
puts "  <input type=\"text\" id=\"name\" name=\"name\" required>"
puts "  <input type=\"submit\" value=\"Submit\">"
puts "</form>"
puts "</body></html>"

cgi = CGI.new
# Process the form submission
if cgi.request_method == "POST"
  name = cgi['name']
  puts "<html><body>"
  puts "Hello #{name}! (via POST)"
  puts "</body></html>"
elsif cgi.query_string =~ /name=(.*)/
  name = $1
  puts "<html><body>"
  puts "Hello #{name}! (via GET)"
  puts "</body></html>"
else
  puts "<html><body>"
  puts "Welcome! No name provided via GET or POST."
  puts "</body></html>"
end

