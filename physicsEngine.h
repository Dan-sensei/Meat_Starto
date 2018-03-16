/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   physicsEngine.h
 * Author: dan
 *
 * Created on 16 de marzo de 2018, 10:00
 */

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>


class physicsEngine {
public:
    //======== SINGLETON =========
    static physicsEngine& Instance(){
        static physicsEngine instance;        // Las variables estáticas se destruyen al terminar el programa
        return instance;                // Return molón
    }
    //============================
    
    struct body{
        b2Body* body;
        void setLinealVelocicty(float vx_, float vy_);
        void addForceToCenter(float vx_, float vy_);
        float getLinearVelocityY();
        
        float getXPosition();
        float getYPosition();
        float getRoation();
    };
    
    body createBody(float width_, float height_, float px_, float py_, char type_);
    void createGround(std::vector<std::array<float, 2>> vertex_, int n_);
    void setGravity(float gx_, float gy_);
    void updateWorld(float tick_);
    b2World* getWorld();
    
private:
    
    //============ SINGLETON ============
    physicsEngine();
    physicsEngine(physicsEngine const& orig);           // <--------------------- No implementar estos métodos
    void operator=(physicsEngine const& orig);    // <----------------'
    //===================================
    
    
    float static pixelToWorld(float p_);
    float static worldToPixel(float w_);
    
    b2World world;
    
};

#endif /* PHYSICSENGINE_H */

/*  FORMA DEL PDF DE FV___________________

 public:
    static physicsEngine* Instance();
    int getVar();
    void setVar(int n_);
    
protected:
    physicsEngine();
    physicsEngine(const physicsEngine &);
    physicsEngine &operator = (const physicsEngine &);
private:
    static physicsEngine* pInstance;
    int var;
 
 */