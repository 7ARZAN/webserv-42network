#!/usr/bin/perl

use strict;
use warnings;
use CGI;

my $cgi = CGI->new;

my $request_method = $cgi->request_method;

print "<html><head><title>Perl CGI Script</title></head><body>";

if ($request_method eq 'GET') {
    # Handle GET request
    print "<h1>GET Request</h1>";
    print "<p>This is a GET request.</p>";

    # Retrieve and display GET parameters
    my $name = $cgi->param('name') // 'Not provided';
    my $email = $cgi->param('email') // 'Not provided';

    print "<p>GET Parameters:</p>";
    print "<ul>";
    print "<li>Name: $name</li>";
    print "<li>Email: $email</li>";
    print "</ul>";

    # Display the form for POST request
    print <<'END_FORM';
    <h2>Submit a POST Request</h2>
    <form method="post" action="">
        <label for="name">Name:</label>
        <input type="text" id="name" name="name"><br>
        <label for="email">Email:</label>
        <input type="email" id="email" name="email"><br>
        <input type="submit" value="Submit">
    </form>
END_FORM

} elsif ($request_method eq 'POST') {
    # Handle POST request
    print "<h1>POST Request</h1>";

    # Retrieve form parameters
    my $name = $cgi->param('name') // 'Not provided';
    my $email = $cgi->param('email') // 'Not provided';

    # Display the submitted data
    print "<p>Submitted POST Parameters:</p>";
    print "<ul>";
    print "<li>Name: $name</li>";
    print "<li>Email: $email</li>";
    print "</ul>";

    print "<p><a href=\"\">Go back to the form</a></p>";
}

print "</body></html>";

