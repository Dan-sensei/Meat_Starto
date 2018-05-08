/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rSoundBuffer.h
 * Author: dan
 *
 * Created on 15 de abril de 2018, 9:11
 */

#ifndef RSOUNDBUFFER_H
#define RSOUNDBUFFER_H

#include <SFML/Audio.hpp>

class rSoundBuffer {
public:
    rSoundBuffer();
    rSoundBuffer(std::string const& filename);
    rSoundBuffer(const rSoundBuffer& orig);
    virtual ~rSoundBuffer();
    
    bool loadFromFile(std::string const& filename);
    sf::SoundBuffer* getBuffer();
    
private:
    
    sf::SoundBuffer soundBuffer;
};

#endif /* RSOUNDBUFFER_H */

