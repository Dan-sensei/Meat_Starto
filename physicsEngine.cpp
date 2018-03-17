/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   physicsEngine.cpp
 * Author: dan
 * 
 * Created on 16 de marzo de 2018, 10:00
 */

#include "physicsEngine.h"
#include "Tile.h"

/*
physicsEngine* physicsEngine::pInstance = nullptr;
physicsEngine* physicsEngine::Instance(){
    if(!pInstance)
        pInstance = new physicsEngine;
    
    return pInstance;
}
*/
#define PI 3.1415926535
#define SCALE 65.f

physicsEngine::physicsEngine()
:world(b2Vec2(0.0f, 40.f))
{
}

void physicsEngine::setGravity(float gx_, float gy_){
    b2Vec2 gravity(gx_, gy_);
    world.SetGravity(gravity);
}

physicsEngine::body physicsEngine::createBody(float width_, float height_, float px_, float py_, char type_){
    
    physicsEngine::body result;
    
    b2PolygonShape shape;
    shape.SetAsBox(pixelToWorld(width_), pixelToWorld(height_));
    
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(pixelToWorld(px_), pixelToWorld(py_));
    switch (type_){
        case 'S':   bodyDef.type = b2_staticBody;
                    break;
        case 'D':   bodyDef.type = b2_dynamicBody;
                    break;
        case 'K':   bodyDef.type = b2_kinematicBody;
                    break;
        default:    std::cout << "ERROR " << std::endl;
                    break;
    }
    
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    result.body = world.CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.7f;
    fixtureDef.shape = &shape;
    
    result.body->CreateFixture(&fixtureDef);
    
    //std::cout << "body " << result.body->GetPosition().x<< std::endl;
    return result;
}

b2World* physicsEngine::getWorld() { return &world;}
void physicsEngine::updateWorld(float tick_){ world.Step(tick_, 8.f, 3.f); }


void physicsEngine::body::setLinealVelocicty(float vx_, float vy_){
    b2Vec2 velocity(vx_, vy_);
    this->body->SetLinearVelocity(velocity);
}

float physicsEngine::body::getLinearVelocityY(){ return this->body->GetLinearVelocity().y; }
void physicsEngine::body::addForceToCenter(float vx_, float vy_){ this->body->ApplyForceToCenter(b2Vec2(vx_, vy_), true); }

float physicsEngine::body::getXPosition() { return worldToPixel(this->body->GetPosition().x); }
float physicsEngine::body::getYPosition() { return worldToPixel(this->body->GetPosition().y); }
float physicsEngine::body::getRoation()   { return this->body->GetAngle()*180/PI; }

float physicsEngine::pixelToWorld(float p_) { return p_/SCALE; }
float physicsEngine::worldToPixel(float w_) { return w_*SCALE; }

void physicsEngine::createGround(std::vector<std::array<float, 2>> vertex_, int n_){

    b2Vec2 vs[n_];
    for(int i=0; i< n_; i++){
        vs[i].Set(vertex_[i][0]/SCALE, vertex_[i][1]/SCALE);
        //std::cout << "X " << vertex_[i][0] << " | Y " << vertex_[i][1] << std::endl;
    }
    
    b2ChainShape chain;
    chain.CreateChain(vs, n_);
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    
    b2Body* body = world.CreateBody(&bodyDef);
   
    b2FixtureDef fixtureDef;
    //fixtureDef.density = 1.f;
    //fixtureDef.restitution = 0.5f;
    fixtureDef.shape = &chain;
    
    body->CreateFixture(&fixtureDef);
}