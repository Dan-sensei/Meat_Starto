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

xPlotato::xPlotato(std::string const& name_, int x_, int y_, int x_b, int x_e) {
    std::cout << "Creando xPlotato" << std::endl;
    int width = AssetManager::GetTexture(name_).getXSize();
    int height = AssetManager::GetTexture(name_).getYSize();
    
    sprite.setTexture(AssetManager::GetTexture(name_));
    sprite.setOrigin(width / 2, height / 2);
    sprite.setPosition(x_, y_);
    
    physicsEngine* world;
    body = world->Instance().createBody(width, height, x_, y_, 'D');
    
    //Zona en la que se puede mover teniendo en cuenta el ancho del sprite
    x_begin = x_b + width/2;
    x_end = x_e - width/2;
    
    target = x_begin;
    
    previous.x = actual.x = body.getXPosition();
    previous.y = actual.y = body.getYPosition();
    previous.r = actual.r = body.getRotation();
    
    std::cout << "Begin "<< x_begin << std::endl;
    std::cout << "End "<< x_end << std::endl;
}

xPlotato::xPlotato(const xPlotato& orig) {
}

xPlotato::~xPlotato() {
}

void xPlotato::update(){

    if(body.getXPosition() > target){
        body.setLinealVelocicity(-velocity, body.getLinearYVelocity());
        sprite.setScale(-1, 1);
    }
    else if(body.getXPosition() < target){
        body.setLinealVelocicity(velocity, body.getLinearYVelocity());
        sprite.setScale(1, 1);
    }
    
    if(abs(body.getXPosition() - target) < 5 )
        target = (target == x_begin) ? x_end : x_begin;
    
}
