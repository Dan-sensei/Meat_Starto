/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rSound.h
 * Author: dan
 *
 * Created on 8 de mayo de 2018, 1:19
 */

#ifndef RSOUND_H
#define RSOUND_H

#include <SFML/Audio/Sound.hpp>

#include "rSoundBuffer.h"


class rSound {
public:
    rSound();
    rSound(const rSound& orig);
    virtual ~rSound();
    
    void setBuffer(rSoundBuffer &buffer);
    void play();
    void stop();
    
private:
    sf::Sound sound;
    
};

#endif /* RSOUND_H */

