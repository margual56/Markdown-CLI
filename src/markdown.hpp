#pragma once
#include <stdio.h>      // Standard I/O
#include <string>       // Use strings
#include <fstream>      // Create, write and read files
#include <regex>        // Unlocks REGEX POWAA

#include "HTML.hpp"


HTML *markdown(std::string);                 // Read from a string, return a HTML file
HTML *markdown(std::string, std::string);    // Read from a string, return a HTML object with style applied
void markdown(std::string, HTML *out);      // Read from a string, modify the given HTML object
