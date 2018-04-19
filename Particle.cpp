/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Particle.cpp
 * Author: dan
 * 
 * Created on 15 de abril de 2018, 13:23
 */

#include "Particle.h"

#define tick 0.0666666666667f

Particle::Particle(float x, float y, float vx, float vy, float rot, float vrot, renderEngine::rSprite s, float life) {
    xPosition = x;
    yPosition = y;
    
    xVelocity = vx;
    yVelocity = vy;
    
    rotation = rot;
    vRotation = vrot;
    
    pSprite = s;
    
    lifeTime = life;
        
    previous.x = actual.x = xPosition;    
    previous.y = actual.y = yPosition;
    previous.r = actual.r = rotation;
    
    lifeClock.restart();
}


Particle::Particle(const Particle& orig) {
    xPosition = orig.xPosition;
    yPosition = orig.yPosition;
    
    xVelocity = orig.xVelocity;
    yVelocity = orig.yVelocity;
    
    rotation = orig.rotation;
    vRotation = orig.vRotation;
    
    pSprite = orig.pSprite;
}

Particle::~Particle() {
}

void Particle::update() {
    //std::cout << "Particula Velocidad X " << xVelocity << " | Velocidad Y " << yVelocity << std::endl; 
    xPosition += xVelocity;
    yPosition += yVelocity;
    rotation += vRotation;
}

void Particle::preState(){
    previous = actual;      // GUARDO EL ESTADO ANTERIOR
}

void Particle::newState(){
    actual.x = xPosition;
    actual.y = yPosition;
    actual.r = rotation;
}

float Particle::getLifeTime() {
    return lifeTime;
}

renderEngine::rTime Particle::getTimeAlive() {
    return lifeClock.getElapsedTime();
}

void Particle::draw() {
    pSprite.draw();
}

void Particle::interpola(float tick_) {
    // CALCULO LAS POSICIONES INTERPOLADAS DE ACUERDO AL TICK
    float x = previous.x *(1-tick_) + actual.x*tick_;
    float y = previous.y *(1-tick_) + actual.y*tick_;
        // Para las rotaciones es mejor interpolar los senos y cosenos, ya que si no, al calcular el ángulo entre 350 y 10, no nos devolvería 20, que sería lo correcto
    float s = sin(previous.r * M_PI/180) * (1-tick_) + sin(actual.r * M_PI/180)*tick_;
    float c = cos(previous.r * M_PI/180) * (1-tick_) + cos(actual.r * M_PI/180)*tick_;
    
    pSprite.setPosition(x, y);
    pSprite.setRotation(atan2(s,c)*180/M_PI);
}

