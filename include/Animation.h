#ifndef ANIMATION_H
#define ANIMATION_H
#include<stdio.h>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<string.h>
class Animation
{
    public:
        Animation();
        Animation(std::string MMPath,sf::Vector2f _position);
        void Play();
        void Update();
        void Draw(sf::RenderWindow& Wind);
        void SetLooped(bool arg);
        virtual ~Animation();
    protected:

    private:
        sf::Texture SpriteSheet;
        sf::Sprite currSprite;
        sf::Clock AnimationClock;
        sf::IntRect FrameRect[256];
        sf::Time delay[256];
        sf::Vector2f position;
        int number_of_frames,current_frame;
        bool isPlaying;
        bool looped;
};

#endif // ANIMATION_H
