CC=g++			# Compiler of choice
flags=			# Flags

all: clean prepare install debug

clean:
	rm -f *.*o bin/*

prepare:
	mkdir -p bin/
	mkdir -p $(XDG_CONFIG_HOME)/markdown-cli/

install:
	curl https://gist.githubusercontent.com/moalex/c5211cd7869944d37260/raw/5353d71bdd6140d311c1ac04cd0a1a59e601778e/clearness-dark.markdown.css > default.css

build: src/*
	$(CC) src/*.cpp $(flags) -o bin/MarkdownCLI
