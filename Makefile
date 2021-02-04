CC=g++			# Compiler of choice
flags=-DDEBUG	# Flags

all: clean prepare debug

clean:
	rm -f *.*o bin/*

prepare:
	mkdir -p bin/

debug: src/*
	$(CC) src/*.cpp $(flags) -o bin/MarkdownCLI