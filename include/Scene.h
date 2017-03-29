#ifndef SCENE_H
#define SCENE_H
#include<SFML/Graphics.hpp>

class Scene
{
    public:
        Scene();
        virtual Scene* Run(sf::RenderWindow& Wind)=0;
        virtual ~Scene();

    protected:

    private:
};

#endif // SCENE_H
