# Markdown-CLI
[![GitHub issues](https://img.shields.io/github/issues/margual56/Markdown-CLI?style=for-the-badge)](https://github.com/margual56/Markdown-CLI/issues)
[![GitHub](https://img.shields.io/github/license/margual56/Markdown-CLI?style=for-the-badge)](https://github.com/margual56/Markdown-CLI/blob/main/docs/LICENSE)
[![GitHub followers](https://img.shields.io/github/followers/margual56?style=for-the-badge)](https://github.com/margual56?tab=followers)
[![GitHub contributors](https://img.shields.io/github/contributors/margual56/Markdown-CLI?style=for-the-badge)](https://github.com/margual56/Markdown-CLI/graphs/contributors)

A markdown CLI renderer in C++ <br/>

(Still in development)

*this is italic* and _this is also italic_
_this is italic_
**this is bold**
__this is bold__

`this is code`


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

## Contributing
First of all, thank you for giving us part of your time!<br/>
You can contribute by:
* [Reporting a bug](https://github.com/margual56/Markdown-CLI/issues/new?assignees=margual56&labels=bug&template=bug_report.md&title=%5BBUG%5D+-+short+description+of+problem)
* [Suggesting a new feature](https://github.com/margual56/Markdown-CLI/issues/new?assignees=margual56&labels=enhancement&template=feature_request.md&title=%5BFEATURE%5D+-+short+description+of+the+feature+or+request)
* Completing the documentation or the wiki
* Fork this project and contribute!

Also, check out [the license](https://github.com/margual56/Markdown-CLI/blob/main/docs/LICENSE) and the [code of conduct](https://github.com/margual56/Markdown-CLI/blob/main/docs/CODE_OF_CONDUCT.md)

