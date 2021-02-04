#include "HTML.hpp"

// Default constructor, just set the type to "html".
// There should be no text inside the HTML tags, just subcomponents
HTML::HTML():Component("html"),head(Component("head")), body(Component("body")) {
}

// Adding a component to the HTML means adding it to its body
void HTML::addChild(Component newChild){
    this->body.addChild(newChild);
}

void HTML::setText(std::string text){
    // Do nothing
}

