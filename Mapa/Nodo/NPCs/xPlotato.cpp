/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   xPlotato.cpp
 * Author: dan
 * 
 * Created on 9 de abril de 2018, 8:27
 */

#include "xPlotato.h"

#define velocity 2.f

xPlotato::xPlotato(int x_, int y_, int x_b, int x_e) {
    //std::cout << "Creando xPlotato" << std::endl;

    std::string sprite_name = "assets/kawaii_potato.png";
    
    int width = AssetManager::GetTexture(sprite_name).getXSize();
    int height = AssetManager::GetTexture(sprite_name).getYSize();

    sprite.setTexture(AssetManager::GetTexture(sprite_name));
    sprite.setOrigin(width / 2, height / 2);
    sprite.setPosition(x_, y_);
    
    physicsEngine* world;
    body = world->Instance().createBody(width, height, x_, y_, 'D');
    t = new physicsEngine::type;
    t->id = 3;
    t->data = this;
    body.setUserData(t);
    

    //Zona en la que se puede mover teniendo en cuenta el ancho del sprite
    x_begin = x_b + width/2;
    x_end = x_e - width/2;
    
    target = x_begin;
    
    if(body.getXPosition() > target){
        body.setLinealVelocicity(-velocity, body.getLinearYVelocity());
        sprite.setScale(-1, 1);
    }
    else if(body.getXPosition() < target){
        body.setLinealVelocicity(velocity, body.getLinearYVelocity());
        sprite.setScale(1, 1);
    }
    
    hp = 1;
    
    previous.x = actual.x = body.getXPosition();
    previous.y = actual.y = body.getYPosition();
    previous.r = actual.r = body.getRotation();
    
}

xPlotato::xPlotato(const xPlotato& orig) {
    t = orig.t;
    x_begin = orig.x_begin;
    x_end = orig.x_end;
    target = orig.target;
    
    hp = orig.hp;
    sprite = orig.sprite;
    body = orig.body;
    previous = orig.previous;
    actual = orig.actual;
}

xPlotato::~xPlotato() {
}

void xPlotato::update(){ 
    
    if(abs(body.getXPosition() - target) < 5 ){
        
        target = (target == x_begin) ? x_end : x_begin;
        
        if(body.getXPosition() > target){
            body.setLinealVelocicity(-velocity, body.getLinearYVelocity());
            sprite.setScale(-1, 1);
        }
        else if(body.getXPosition() < target){
            body.setLinealVelocicity(velocity, body.getLinearYVelocity());
            sprite.setScale(1, 1);
        }
        
    }
    
}
