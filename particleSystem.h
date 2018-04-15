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


class particleSystem {
public:
    particleSystem();
    particleSystem(const particleSystem& orig);
    virtual ~particleSystem();
private:
    
    struct particle{
        float xVelocity;
        float yVelocity;
        
        float rotation;
        
        float xPosition;
        float yPosition;
        
        renderEngine::rSprite sprite;
    };
    
    
};

#endif /* PARTICLESYSTEM_H */

