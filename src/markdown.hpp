#pragma once
#include <stdio.h>
#include "HTML.hpp"

struct HTML markdown_file(FILE *f, char **flags); //Read from a file, return a HTML file
struct HTML markdown_stdin(int size, char *buffer, char **flags); //Read from stdin, return a HTML file
