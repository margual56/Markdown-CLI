#include <list>
#include <string>

class Component{
    protected:
        struct Content{                 // Store the component's text
            std::string text = "";
            Component *after = NULL;    // Needed to know when to render the text
        };

        std::string type;               // Type of the component (div, html, code...)
        Content content;                // Struct storing the text (if any)
        Component *parent = NULL;       // Component parent to this one (default to NULL, unused for the moment)
        std::list<Component*> children;  // List of subcomponents (FIFO)

    public:
        Component(std::string type);    // Default constructor (only provide the type of Component)
        Component(std::string type, std::string content); // Overridden constructor to include text at the begginning

        void addChild(Component *newChild);          // Add a new subcomponent to the list
        std::string render();                       // Function returning all the subcomponents rendered inside this component
        
        void setText(std::string text);             // Set this component's text, placed after the last subcomponent added (if any)
        std::string getType(){return this->type;}   // Returns the type of this component
        Component* getParent(){return this->parent;}// Returns the parent of this component (unused for the moment)
};
