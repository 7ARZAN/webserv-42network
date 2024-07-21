#!/usr/bin/env python3

import cgi

# Print necessary headers
# HTML boilerplate
print("<html><head><title>Simple CGI Script with cgi module</title></head>")
print("<body>")
print("<h1>Simple CGI Script with cgi module</h1>")

# Create instance of FieldStorage
form = cgi.FieldStorage()

# Get data from fields
name = form.getvalue('name')
age = form.getvalue('age')

# Print HTML form
print("<form method='post' action='/tarzan.py'>")
print("Name: <input type='text' name='name'><br>")
print("Age: <input type='text' name='age'><br>")
print("<input type='submit' value='Submit'>")
print("</form>")

# Print submitted data
if name or age:
    print("<h2>Submitted Data:</h2>")
    print("<p>Name: {}</p>".format(name))
    print("<p>Age: {}</p>".format(age))

print("</body></html>")
