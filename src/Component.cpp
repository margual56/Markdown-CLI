#include <string>
#include "Component.hpp"

Component::Component(std::string type){
    this->type=type;
}

std::string Component::render(){
    std::string tmp = "<" + this->type + ">";

    for(Component c: this->children)
        tmp += c.render();
    
    tmp += "</" + this->type + ">";

    return tmp;
}