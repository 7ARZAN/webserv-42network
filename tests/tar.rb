#!/usr/bin/env ruby

require 'cgi'

cgi = CGI.new

puts "Content-type: text/html"
puts ""

puts "<html>"
puts "<head><title>CGI Test</title></head>"
puts "<body>"

puts "<h1>CGI Test</h1>"

puts "<h2>Parameters:</h2>"
puts "<ul>"
cgi.params.each do |key, value|
  puts "<li>#{CGI.escapeHTML(key)}: #{CGI.escapeHTML(value.join(', '))}</li>"
end
puts "</ul>"

puts "</body>"
puts "</html>"

