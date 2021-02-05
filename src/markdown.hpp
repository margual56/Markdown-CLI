#pragma once
#include <stdio.h>      // Standard I/O
#include <string>       // Use strings
#include <fstream>      // Create, write and read files

#include "HTML.hpp"

HTML markdown_file(std::fstream f, char **flags); //Read from a file, return a HTML file
HTML markdown_stdin(int size, char *buffer, char **flags); //Read from stdin, return a HTML file
