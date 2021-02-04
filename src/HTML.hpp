#pragma once
#include <string.h>
#include <list>
#include "Component.hpp"

class HTML: public Component{
    public:
        HTML();
        std::string render();
};