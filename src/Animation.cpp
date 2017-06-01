#include "Animation.h"

Animation::Animation()
{
    //ctor
}
Animation::Animation(std::string MMPath,sf::Vector2f _position)
{
    FILE*fin=fopen(MMPath.c_str(),"r");
    char SpritePath[256];
    fgets(SpritePath,256,fin);
    int n=strlen(SpritePath);
    SpritePath[n-1]='\0';
    fscanf(fin,"%d",&number_of_frames);
    printf("%d",number_of_frames);
    for(int i=0; i<number_of_frames; i++)
    {
        int ms;
        fscanf(fin,"%d%d%d%d%d",&FrameRect[i].top,&FrameRect[i].left,&FrameRect[i].width,&FrameRect[i].height,&ms);
        delay[i]=sf::milliseconds(ms);
    }
    fclose(fin);
    SpriteSheet.loadFromFile(SpritePath);
    current_frame=0;
    currSprite.setTexture(SpriteSheet);
    currSprite.setTextureRect(FrameRect[current_frame]);
    currSprite.setPosition(_position);
    isPlaying=0;
    looped=0;
}
Animation::~Animation()
{
    //dtor
}
void Animation::Play()
{
    AnimationClock.restart();
    current_frame=0;
    isPlaying=1;
}
void Animation::Update()
{
    if(isPlaying)
    {
        if(AnimationClock.getElapsedTime()>=delay[current_frame])
        {
            if(current_frame==number_of_frames)
            {
                if(looped)
                {
                    current_frame=-1;
                }
                else
                {
                    isPlaying=0;
                    return;
                }
            }
            current_frame++;
            currSprite.setTextureRect(FrameRect[current_frame]);
            AnimationClock.restart();
        }
    }
}
void Animation::SetLooped(bool arg)
{
    looped=arg;
}
void Animation::Draw(sf::RenderWindow& Wind)
{
    Wind.draw(currSprite);
}
