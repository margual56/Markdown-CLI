# Markdown-CLI
[![GitHub issues](https://img.shields.io/github/issues/SantiMA10/CampusVirtualPlus.svg)](https://github.com/margual56/Markdown-CLI/issues)
[![GitHub forks](https://img.shields.io/github/forks/SantiMA10/CampusVirtualPlus.svg)](https://github.com/margual56/Markdown-CLI/network)
[![GitHub stars](https://img.shields.io/github/stars/SantiMA10/CampusVirtualPlus.svg)](https://github.com/margual56/Markdown-CLI/stargazers)

A markdown CLI renderer in C++ <br/>

(Still in development)

## Goal
Simple syntax, concise commands and versatile while _trying_ to be suckless.

Command | Description
--- | ---
`markdown -i input.md output.html` | Reads the markdown from the file and outputs to another file.
`markdown output.html`             | Reads the markdown from the stdin (optional).
`markdown -i input.md`             | Reads the markdown from the file and writes the output to the stdout.
`markdown -i input.md -s style.css output.html` |  Reads the markdown from the file and outputs to another file, applying the styling rules specified in the css (includes a `<style></style>` tag in the html head).
`markdown -h` or `markdown --help` | Display the help (manual)

## Manual
The goal is to have here a wiki, implement the manual page and add it to the [tldr pages](https://github.com/tldr-pages/tldr).
