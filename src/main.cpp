#include <algorithm>
#include <cstring>
#include <getopt.h>     // GNU's getopt (parse CL arguments)
#include <stdio.h>      // Standard I/O
#include <iostream>     // For the std::cin and std::cout. I don't like, but... oh well
#include <string>       // Use strings
#include <fstream>      // Create, write and read files

#include "markdown.hpp" // Markdown parser


int main(int argc, char **argv) {
    int c;
    std::string styleFile, inputFile, outputFile, stdinMarkdown;
    bool verbose_flag;

    while (1) {
        static struct option long_options[] = {
            {"verbose",     no_argument,        0, 'v'},
            {"help",        no_argument,        0, 'h'},
            {"style",       required_argument,  0, 's'},
            {"input",       required_argument,  0, 'i'}
        };

        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "vhs:i:", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c) {
            case 'v':
                verbose_flag = true;
            break;

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

            default:
                abort();
        }
    }

    if (verbose_flag)
        puts("Verbose flag is set");

    if (optind+1 < argc) {
        perror("Too many arguments\n");
        exit(2);
    }

    if(inputFile.empty()){
        printf("Input: stdin\nPress Ctrl+D (or Ctrl+Z on Windows) to end.\n");

        // Read from stdin and load it into a variable
        std::string line;
        do{
            std::getline(std::cin, line);
            stdinMarkdown += line + "\n";
        }while(!std::cin.eof());
    }else{
        std::ifstream inputStream(inputFile);

        if(inputStream.is_open()){
            std::string line;
            do{
                std::getline(inputStream, line);
                stdinMarkdown += line + "\n";
            }while(!inputStream.eof());

            inputStream.close();
        }else{
            printf("%s\n", outputFile.c_str());
            perror("Unable to open the output file");
            exit(3);
        }

        if(verbose_flag)
            printf("Input: %s\n", inputFile.c_str());
    }

    //printf("%s\n", stdinMarkdown.c_str());

    HTML *output = new HTML(markdown(stdinMarkdown));

    if(!styleFile.empty() && verbose_flag){
        printf("Style: %s\n", styleFile.c_str());
    }

    if(optind < argc){
        outputFile = std::string(argv[optind]);
        if(verbose_flag)
            printf("Output: %s\n", outputFile.c_str());

        std::ofstream outputStream (outputFile);
        if(outputStream.is_open()){
            outputStream << output->render();
            outputStream.close();
        }else{
            printf("%s\n", outputFile.c_str());
            perror("Unable to open the output file");
            exit(3);
        }
    }else{
        if(verbose_flag)
            printf("Output: stdout\n\n");

        printf("%s\n", output->render().c_str());
    }


    exit(0);
}
