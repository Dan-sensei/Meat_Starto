/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rMusic.cpp
 * Author: dan
 * 
 * Created on 15 de abril de 2018, 9:10
 */

#include "rMusic.h"

rMusic::rMusic() {
}

rMusic::rMusic(const std::string& filename) {
    music.openFromFile(filename);
}


rMusic::rMusic(const rMusic& orig) {
}

rMusic::~rMusic() {
    
}

bool rMusic::openFromFile(const std::string& filename) {
    return music.openFromFile(filename);
}

bool rMusic::getLoop() {
    return music.getLoop();
}

float rMusic::getVolume() {
    return music.getVolume();
}

void rMusic::play() {
    music.play();
}

void rMusic::pause() {
    music.pause();
}

void rMusic::stop() {
    music.stop();
}

void rMusic::setLoop(bool loop) {
    music.setLoop(loop);
}

void rMusic::setVolume(float volume) {
    music.setVolume(volume);
}






