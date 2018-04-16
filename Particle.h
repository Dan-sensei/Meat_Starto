/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Particle.h
 * Author: dan
 *
 * Created on 15 de abril de 2018, 13:23
 */

#ifndef PARTICLE_H
#define PARTICLE_H

#include "renderEngine/renderEngine.h"



class Particle {
public:
    Particle(float x, float y, float vx, float vy, float rot, float vrot, renderEngine::rSprite &s, float life);
    Particle(const Particle& orig);
    virtual ~Particle();
    
    renderEngine::rTime getTimeAlive();
    float getLifeTime();
    
    void interpola(float tick_);
    void draw();
    
    void preState();
    void newState();
    
    void update();
    
private:
    renderEngine::rClock lifeClock;
    float lifeTime;
    
    float xPosition;
    float yPosition;
    
    float xVelocity;
    float yVelocity;

    float rotation;
    float vRotation;
    
    struct state{
        float x;     // Posicion X
        float y;     // Posicion Y
        float r;     // Rotacion
    };
    state previous;
    state actual;

    //float opacity_time;
    renderEngine::rSprite pSprite;
};

#endif /* PARTICLE_H */

