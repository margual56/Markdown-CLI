CC=g++			# Compiler of choice
flags=			# Flags

all: clean prepare install build

clean:
	rm -f *.*o bin/*

prepare:
	mkdir -p bin/
	# mkdir -p $(XDG_CONFIG_HOME)/markdown-cli/

install:
	curl https://raw.githubusercontent.com/otsaloma/markdown-css/master/github.css > default.css

build: src/*
	$(CC) src/*.cpp $(flags) -o bin/markdown-cli
