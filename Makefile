CC=g++			# Compiler of choice
flags=-DDEBUG	# Flags

all: clean prepare install debug

clean:
	rm -f *.*o bin/*

prepare:
	mkdir -p bin/
	mkdir -p $(XDG_CONFIG_HOME)/markdown-cli/

install:
	curl https://gist.githubusercontent.com/tuzz/3331384/raw/fc0160dd7ea0b4a861533c4d6c232f56291796a3/github.css > default.css

debug: src/*
	$(CC) src/*.cpp $(flags) -o bin/MarkdownCLI
