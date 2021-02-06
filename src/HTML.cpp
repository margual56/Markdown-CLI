#include "HTML.hpp"

// Default constructor, just set the type to "html".
// There should be no text inside the HTML tags, just subcomponents
HTML::HTML():Component("html"){
    // Add the head and the body to the list of components
    this->head = new Component("head");
    this->head->setText("<link rel=\"stylesheet\" href=\"default.css\">");
    this->children.push_back(this->head);

    this->body = new Component("body");
    this->children.push_back(this->body);
}

// Overloaded constructor to include a styling file
HTML::HTML(std::string cssFilePath):Component("html"){
    this->cssFilePath = cssFilePath;

    // Add the head and the body to the list of components
    this->head = new Component("head");
    this->head->setText("<link rel=\"stylesheet\" href=\"default.css\">");
    this->children.push_back(this->head);

    this->body = new Component("body");
    this->children.push_back(this->body);

}

// Adding a component to the HTML means adding it to its body
void HTML::addChild(Component *newChild){
    this->body->addChild(newChild);
}

void HTML::setText(std::string text){
    this->body->setText(text);
}

