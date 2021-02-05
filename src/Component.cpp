#include <string>
#include "Component.hpp"

// Default constructor, type of the Component needed (div, tag, code...)
Component::Component(std::string type){
    this->type=type;
}

// Overloaded constructor to include text before any of the components
Component::Component(std::string type, std::string text){
    this->type=type;
    this->content = {text};
}

// Add subcomponents
void Component::addChild(Component *newChild){
    this->children.push_back(newChild); // Add the new component to the end
}

// Sets the text contained in this component. It is placed after the last added component
void Component::setText(std::string text){
    if(this->children.size() == 0)      // If no components were added before, 
        this->content = {text};         // just set the text (keep the reference NULL, the default)
    else                                // Otherwise,
        this->content = {text, this->children.back()}; // set the reference to the last component added
}

std::string Component::render(){
    std::string tmp = "<" + this->type + ">\n";   // Open the tag

    if(this->content.after == NULL && !this->content.text.empty())     // If the text's "after" is NULL, it means that the text should be rendered first
        tmp += this->content.text + "\n";

    for(Component *c: this->children){   // For each subcomponent,
        tmp += c->render() + "\n";              // render it

        if(this->content.after == c){  // and then check if the text goes after it
            tmp += this->content.text + "\n";  // (if it does, render the text)
        }
    }
    
    tmp += "</" + this->type + ">\n";     // And close the tag

    return tmp;
}