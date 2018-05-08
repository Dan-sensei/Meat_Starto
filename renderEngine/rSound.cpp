/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rSound.cpp
 * Author: dan
 * 
 * Created on 8 de mayo de 2018, 1:19
 */

#include "rSound.h"

rSound::rSound() {
}

rSound::rSound(const rSound& orig) {
}

rSound::~rSound() {
}

void rSound::setBuffer(rSoundBuffer &buffer) {
    sound.setBuffer(*buffer.getBuffer());
}

void rSound::play() {
    sound.play();
}

void rSound::stop() {
    sound.stop();
}

