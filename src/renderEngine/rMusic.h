/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rMusic.h
 * Author: dan
 *
 * Created on 15 de abril de 2018, 9:10
 */

#ifndef RMUSIC_H
#define RMUSIC_H

#include <SFML/Audio/Music.hpp>


class rMusic {
public:
    rMusic();
    rMusic(std::string const& filename);
    rMusic(const rMusic& orig);
    virtual ~rMusic();
    
    bool openFromFile(std::string const& filename);
    void play();
    void stop();
    void pause();
    
    void setLoop(bool loop);
    void setVolume(float volume);
    
    bool getLoop();
    float getVolume();
    
    
private:
    sf::Music music;
    
};

#endif /* RMUSIC_H */

