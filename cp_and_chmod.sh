#!/bin/bash
#this script copies the read_button.cgi application to the /usr/lib/cgi-bin/ directory
#and issues chmod +s to the application to be run by a web server

sudo cp read_button.cgi /usr/lib/cgi-bin/
echo "read_button.cgi copied to /usr/lib/cgi-bin/"
sudo chmod +s /usr/lib/cgi-bin/read_button.cgi
echo "chmod +s complete"
