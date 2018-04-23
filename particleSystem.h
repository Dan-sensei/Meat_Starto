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
    particleSystem();
    particleSystem(const particleSystem& orig);
    virtual ~particleSystem();
    
    void setParticleDirection(float x, float y);
    void setMaxParticleAmout(int n);
    
    void setParticleSpeed(float f);
    void setParticleSpeedRandomBetween(float min, float max);
    
    void setParticleRotation(float degree);
    void setParticleRotationRandomBetween(float min, float max);
    
    void setParticleAngularVelocity(float speed);
    void setParticleAngularVelocityRandomBetween(float min, float max);
    
    void setParticleOpacityTime(float time);
    void setParticleOpacityTimeRandomBetween(float min, float max);
    
    void setParticleLifeTime(float time);
    void setParticleLifeTimeRandomBetween(float min, float max);
    
    void setSprite(std::string const& filename);
    void setSpriteSize(float x, float y);
    
    void setGenerationTimer(float s);
    
    void setLoop(bool loop_);
    void setLifeTime(float time);
    
    void setCircle(float radius_);
    void setRectangle(float sideX , float sideY);
    
    void setPosition(float x, float y);
    float getYPosition();
    float getXPosition();
    
    void alignToDirection(bool flag);
    void drawGenerationArea(bool flag);
    void setType(int type_);
    void interpola(float tick_);
    void draw(float tick_);
    
    void preState();
    void newState();
    
    void update();
    
private:
    
    renderEngine::rClock lifeTimeClock;
    renderEngine::rClock timerClock;
    
    //Variables del sistema en sí
    int max_particles;
    float lifeTime;
    float xPos, yPos;
    float xVelocity, yVelocity;
    float radius;
    float xSide, ySide;
    float rotation;
    float delayBetweenParticlesGeneration;
    float targetX, targetY;
    bool alignToDirectionBool;
    
    //Variables de las partículas del sistema
    float particle_min_velocity, particle_max_velocity;
    float particle_min_angular_velocity, particle_max_angular_velocity;
    float particle_min_lifeTime, particle_max_lifeTime;
    float particle_min_rotation, particle_max_rotation;
    
    float accumulator;
 
    bool loop;
    bool drawGen;
    
    int type;
    
    renderEngine::rRectangleShape box;
    renderEngine::rSprite sprite;
    
    std::list<Particle> lista_particular;
    
};

#endif /* PARTICLESYSTEM_H */

