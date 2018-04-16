/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   particleSystem.h
 * Author: dan
 *
 * Created on 14 de abril de 2018, 9:51
 */

#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <list>
#include "Particle.h"



class particleSystem {
public:
    particleSystem(int x, int y);
    particleSystem(const particleSystem& orig);
    virtual ~particleSystem();
    
    void setMaxParticleAmout(int n);
    
    void setParticleSpeed(float f);
    void setParticleSpeedRandomBetween(float min, float max);
    
    void setParticleRotation(float degree);
    void setParticleAngularVelocity(float speed);
    void setParticleAngularVelocityRandomBetween(float min, float max);
    
    void setParticleOpacityTime(float time);
    void setParticleOpacityTimeRandomBetween(float min, float max);
    
    void setParticleLifeTime(float time);
    void setParticleLifeTimeRandomBetween(float min, float max);
    
    void setSprite(std::string const& filename);
    
    void setGenerationTimer(float s);
    
    void setLoop(bool loop_);
    void setLifeTime(float time);
    
    void interpola(float tick_);
    void draw();
    
    void preState();
    void newState();
    
    void update();
    
private:
    
    renderEngine::rClock lifeTimeClock;
    renderEngine::rClock timerClock;
    int n_particles;
    
    float accumulator;
    float timer;
    
    float min_velocity;
    float max_velocity;
    
    float min_angular_velocity;
    float max_angular_velocity;
    
    int xPos;
    int yPos;
    
    bool loop;
    
    
    
    renderEngine::rSprite sprite;
    
    std::list<Particle> lista_particular;
    
};

#endif /* PARTICLESYSTEM_H */

