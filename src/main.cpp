#include <algorithm>
#include <cstring>
#include <getopt.h>     // GNU's getopt (parse CL arguments)
#include <stdio.h>      // Standard I/O
#include <iostream>     // For the std::cin and std::cout. I don't like, but... oh well
#include <string>       // Use strings
#include <fstream>      // Create, write and read files

#include "markdown.hpp" // Markdown parser

/* Flag set by ‘--verbose’. */
static int verbose_flag;

int main(int argc, char **argv) {
    int c;
    std::string styleFile, inputFile, outputFile, stdinMarkdown;

    while (1) {
        static struct option long_options[] = {
            /* These options set a flag. */
            {"verbose", no_argument, &verbose_flag, 1},
            {"brief", no_argument, &verbose_flag, 0},
            {"help", no_argument, 0, 'h'},
            {"style", required_argument, 0, 's'},
            {"input", required_argument, 0, 'i'}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "hs:i:", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c) {
            case 'h':
                printf("Gotta show the man page (or the help)");
                exit(0);
            break;

            case 's':
                styleFile = optarg;
            break;

            case 'i':
                inputFile = optarg;
            break;

            case '?':
                /* getopt_long already printed an error message. */
            break;

            default:
                abort();
        }
    }

    /* Instead of reporting ‘--verbose’
    and ‘--brief’ as they are encountered,
    we report the final status resulting from them. */
    if (verbose_flag)
        puts("verbose flag is set");

    if (optind+1 < argc) {
        perror("Too many arguments\n");
        exit(2);
    }

    HTML output = HTML();
    output.addChild(Component("p", "This is a test"));

    if(inputFile.empty()){
        printf("Input: stdin\n");

        // Read from stdin and load it into a variable
        std::string line;
        do{
            std::getline(std::cin, line);
            stdinMarkdown += line + "\n";
        }while(!line.empty());

        printf("%s\n", stdinMarkdown.c_str());
    }else{
        std::ifstream inputStream(inputFile);

        if(inputStream.is_open()){
            std::string line;
            do{
                std::getline(inputStream, line);
                stdinMarkdown += line + "\n";
            }while(!line.empty());

            inputStream.close();
        }else{
            printf("%s\n", outputFile.c_str());
            perror("Unable to open the output file");
            exit(3);
        }

        printf("Input: %s\n", inputFile.c_str());
    }

    printf("%s\n", stdinMarkdown.c_str());

    if(!styleFile.empty()){
        printf("Style: %s\n", styleFile.c_str());
    }

    if(optind < argc){
        outputFile = std::string(argv[optind]);
        printf("Output: %s\n", outputFile.c_str());

        std::ofstream outputStream (outputFile);
        if(outputStream.is_open()){
            outputStream << output.render();
            outputStream.close();
        }else{
            printf("%s\n", outputFile.c_str());
            perror("Unable to open the output file");
            exit(3);
        }
    }else{
        printf("Output: stdout\n");

        printf("\n%s\n", output.render().c_str());
    }


    exit(0);
}
