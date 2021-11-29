#!/bin/bash
#this script compiles the read_button.cpp application into a read_button.cgi file to be placed in the
#/usr/lib/cgi-bin/ directory to be run by a web server
#additionally, this script also configures gpio46 to be read as an input by the application

echo "beginning compilation..."
g++ read_button.cpp -o read_button.cgi -lcgicc
echo "compilation complete."
echo "configuring and building GPIO Pins to be used"
config-pin -a p8.16 in+
echo "configuration complete"
