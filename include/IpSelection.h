#ifndef IPSELECTION_H
#define IPSELECTION_H
#include<Scene.h>
#include<TextBox.h>
class IpSelection : public Scene
{
    public:
        IpSelection();
        virtual ~IpSelection();
        virtual Scene* Run(sf::RenderWindow& Wind);
    protected:

    private:
        TextBox* ipBox;
};

#endif // IPSELECTION_H
