/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Skull.cpp
 * Author: dan
 * 
 * Created on 14 de abril de 2018, 12:05
 */

#include <complex>
#include <random>

#include "Skull.h"

#define velocity 6.f

Skull::Skull(int x_, int y_, int x_b, int x_e, int y_b, int y_e) {

    std::string sprite_name = "assets/skull.png";
    
    int width = AssetManager::GetTexture(sprite_name).getXSize();
    int height = AssetManager::GetTexture(sprite_name).getYSize();

    sprite.setTexture(AssetManager::GetTexture(sprite_name));
    sprite.setOrigin(width / 2, height / 2);
    sprite.setPosition(x_, y_);
    
    physicsEngine* world;
    body = world->Instance().createBody(width, height, x_, y_, 'k');
    t = new physicsEngine::type;
    t->id = 4;
    t->data = this;
    body.setUserData(t);
    
    //Zona en la que se puede mover teniendo en cuenta el ancho del sprite
    x_min = x_b + width/2;
    x_max = x_e - width/2;
    
    y_min = y_b + height/2;
    y_max = y_e - height/2;
    
    targetX = genRandom(x_min, x_max);
    targetY = genRandom(y_min, y_max);
    
    hp = 1;
    
    previous.x = actual.x = body.getXPosition();
    previous.y = actual.y = body.getYPosition();
    previous.r = actual.r = body.getRotation();
}

Skull::Skull(const Skull& orig) {
    t = orig.t;
    x_min = orig.x_min;
    x_max = orig.x_max;
    y_min = orig.y_min;
    y_max = orig.y_max;
    targetX = orig.targetX;
    targetY = orig.targetY;
    
    hp = orig.hp;
    sprite = orig.sprite;
    body = orig.body;
    previous = orig.previous;
    actual = orig.actual;
}

Skull::~Skull() {
}

void Skull::update(){
    
    float x_distance = targetX - body.getXPosition();
    float y_distance = targetY - body.getYPosition();
    float vector = sqrt((x_distance*x_distance)+(y_distance*y_distance));
    
    if(vector > 15){
       
        float angle = atan2(y_distance, x_distance);
        float x_velocity = cos(angle)*velocity;
        float y_velocity = sin(angle)*velocity;
        
        body.setLinealVelocicity(x_velocity, y_velocity);
        
        if(body.getXPosition() > targetX)
            sprite.setScale(1, 1);
        
        else if(body.getXPosition() < targetX)
            sprite.setScale(-1, 1);
 
    }
    else{        
        targetX = genRandom(x_min, x_max);
        targetY = genRandom(y_min, y_max);
    }
    
}

float Skull::genRandom(float min, float max){
    std::random_device rd;
    std::default_random_engine gen(rd());

    std::uniform_int_distribution<int> distribution(min, max);
    
    return distribution(gen);
}