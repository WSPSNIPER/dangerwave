#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include <string>
#include <map>

namespace cell
{
    /// have not tested yet, you need to test it
    typedef std::map<std::string, sf::SoundBuffer>  BufferMap;
    class SoundManager
    {
    private:
        SoundManager();
        static SoundManager* _instance;
    public:
        ~SoundManager();
        static SoundManager* GetInst();
        static SoundManager& GetRef();

        sf::SoundBuffer& GetBuffer(std::string name);


    private:
        BufferMap           _buffers;
        BufferMap::iterator _iterator;
        sf::SoundBuffer&    _addSound(std::string name);

    };
}

#endif
