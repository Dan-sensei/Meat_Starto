/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NPC.cpp
 * Author: dan
 * 
 * Created on 9 de abril de 2018, 8:22
 */

#include "NPC.h"

NPC::NPC() {
}

NPC::NPC(const NPC& orig) {
}

NPC::~NPC() {
}

void NPC::update(){
    std::cout << "Soy una clase genérica, no tengo razón de existencia individual :(" << std::endl;
}

void NPC::draw(){
    sprite.draw();
}

void NPC::preState(){
    previous = actual;      // GUARDO EL ESTADO ANTERIOR
}

void NPC::newState(){
    actual.x = body.getXPosition();
    actual.y = body.getYPosition();
    actual.r = body.getRotation();
}

void NPC::interpola(float tick_){
    std::cout << tick_ << std::endl;
    
    // CALCULO LAS POSICIONES INTERPOLADAS DE ACUERDO AL TICK
    float x = previous.x *(1-tick_) + actual.x*tick_;
    float y = previous.y *(1-tick_) + actual.y*tick_;
        // Para las rotaciones es mejor interpolar los senos y cosenos, ya que si no, al calcular el ángulo entre 350 y 10, no nos devolvería 20, que sería lo correcto
    float s = sin(previous.r * M_PI/180) * (1-tick_) + sin(actual.r * M_PI/180)*tick_;
    float c = cos(previous.r * M_PI/180) * (1-tick_) + cos(actual.r * M_PI/180)*tick_;
    
    sprite.setPosition(x, y);
    sprite.setRotation(atan2(s,c)*180/M_PI);
}

int NPC::getXPosition(){
    return body.getXPosition();
}

int NPC::getYPosition(){
    return body.getYPosition();
}