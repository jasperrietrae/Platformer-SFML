#include "sound.h"

bool Sound::Load(std::string filename)
{
    return soundBuffer.loadFromFile(filename);
}

void Sound::Update(void)
{
    for (int i = 0 ; i < soundInstances.size() ; ++i)
    {
        if (soundInstances[i].getStatus() == sf::Sound::Stopped)
        {
            soundInstances.erase(soundInstances.begin() + i);
            --i;
        }
    }
}

void Sound::Play(void)
{
    soundInstances.push_back(sf::Sound(soundBuffer));
    soundInstances.back().play();
}
