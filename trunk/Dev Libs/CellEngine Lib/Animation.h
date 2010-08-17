#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include "ImageManager.h"
#include <vector>


/// @TODO   add a setcurrentanimation and make the play animation play the current animation
///         and have a play animation for quick attacks and stuff :)

enum anim_type
{
    VERTICAL,   // animations are vertical, down and one collum over will be the next animation
    HORIZONTAL  // animations are horizontal, across and one row down will be the next animation
};
namespace cell
{

    class NumString; // instead of map
    typedef std::vector<NumString> AnimList;
    class Animation
    {
    public:
        // calls the ImageManager::GetImage(string) function to set the image on the sprite
        Animation(std::string name, uint16_t frame_width, uint16_t frame_height, uint16_t num_frames, anim_type type = HORIZONTAL);

        // the image is already here for this constructor
        Animation(sf::Image& image, uint16_t frame_width, uint16_t frame_height, uint16_t num_frames, anim_type type = HORIZONTAL);

        Animation(sf::Sprite& sprite, uint16_t frame_width, uint16_t frame_height, uint16_t num_frames, anim_type type = HORIZONTAL);

        ~Animation();

        // add the animations from the image
        void AddAnimation(std::string name);

        // plays the animation selected also renders so it needs the window
        void PlayAnimation(std::string name, sf::RenderWindow &window, int times = -1);
        void PlayAnimation(sf::RenderWindow& window, int times = -1);

        float GetX() { return _sprite.GetPosition().x; }
        float GetY() { return _sprite.GetPosition().y; }

        void SetCurrentAnimation(std::string anim){ _animName = anim; }

        void SetDelay(float delay)
        {
            _delay = delay;
        }
        float GetDelay() const
        {
            return _delay;
        }

        // gets the row/collum of the called animation
        int GetRow(std::string name);

        // increments the frame, ocillation is not supported atm lol im too lazy right now... ill add a todo
        /// @TODO implement ocillation
        void IncrementFrame(bool ocillate = true);

        sf::Sprite& GetSprite() { return _sprite; }

    private:
        // keep the f_width and height handy for funnctions
        uint16_t        _frameWidth;
        uint16_t        _frameHeight;

        float           _delay;

        // weather the animation is vertical or horizontal
        anim_type       _type;

        // to manage the images
        ImageManager&   _imgMgr;

        int             _row;
        int             _frame;
        int             _maxFrame;

        // the sprite for rendering
        sf::Sprite      _sprite;


        // the clock for keeping the speed of the animation
        sf::Clock       _clock;

        // the list of animations
        AnimList        _animList;

        std::string      _animName;

    };

    //could do a templated class namedvar but whatever lol i want a numbered string and i dont feel like being modular right now
    class NumString
    {
    public:
        NumString(std::string string, int number)
            :
            _string(string),
            _number(number)
        {
        }

        void SetString(std::string s)
        {
            _string = s;
        }
        void SetNumber(int n)
        {
            _number = n;
        }

        int GetNumber() const
        {
            return _number;
        }
        std::string GetString() const
        {
            return _string;
        }

    private:
        std::string _string;
        int         _number;
    };
}
#endif
