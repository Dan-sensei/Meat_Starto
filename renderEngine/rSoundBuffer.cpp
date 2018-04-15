/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rSoundBuffer.cpp
 * Author: dan
 * 
 * Created on 15 de abril de 2018, 9:11
 */

#include "rSoundBuffer.h"

rSoundBuffer::rSoundBuffer() {
}

rSoundBuffer::rSoundBuffer(const rSoundBuffer& orig) {
}

rSoundBuffer::~rSoundBuffer() {
}

bool rSoundBuffer::loadFromFile(const std::string& filename) {
    return soundBuffer.loadFromFile(filename);
}
