#include <list>
#include <string>

class Component{
    protected:
        std::string type;
        Component *parent;
        std::list<Component> children;

    public:
        Component(std::string type);
        std::string render();
        std::string getType(){return this->type;}
        Component* getParent(){return this->parent;}
};