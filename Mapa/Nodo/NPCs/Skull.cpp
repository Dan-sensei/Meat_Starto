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
    t = new physicsEngine::type;
    t->id = 4;
    t->data = this;
    body = world->Instance().createBody(width, height, x_, y_, 'k', t);
    
    
    //Zona en la que se puede mover teniendo en cuenta el ancho y alto del sprite
    x_min = x_b + width/2;
    x_max = x_e - width/2;
    
    y_min = y_b + height/2;
    y_max = y_e - height/2;
    
    // Genero la primera coordenada aleatoria a la que se dirigirá el buen Skull
    targetX = physicsEngine::Instance().genIntRandom(x_min, x_max);
    targetY = physicsEngine::Instance().genIntRandom(y_min, y_max);
    
    hp = 1;
    
    previous.x = actual.x = body.getXPosition();
    previous.y = actual.y = body.getYPosition();
    previous.r = actual.r = body.getRotation();
    
    alive = true;
    xplosion = NULL;
}

Skull::Skull(const Skull& orig) {
    // Constructor copia molón
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
    //std::cout << "Destruyendo Skull..." << std::endl;
    delete t;
    t = nullptr;
}

void Skull::update(){
    
    if(abs(body.getLinearXVelocity()) < 1){
        recalcula();
    }
    
    float x_distance = targetX - body.getXPosition();                       // Distancia a la coordenada objetivo en X
    float y_distance = targetY - body.getYPosition();                       // Distancia a la coordenada objetivo en Y
    float vector = sqrt((x_distance*x_distance)+(y_distance*y_distance));   // Distancia en línea recta
    
    if(vector < 20){        // Si la distancia al punto es menor de 15 (margen de error)
   
        // Genero un nuevo punto de destino aleatoriamente
        targetX = physicsEngine::Instance().genIntRandom(x_min, x_max);      
        targetY = physicsEngine::Instance().genIntRandom(y_min, y_max);
        
        // Ajusto el sprite teniendo en cuenta el eje X
        if(body.getXPosition() > targetX)
            sprite.setScale(1, 1);
        else if(body.getXPosition() < targetX)
            sprite.setScale(-1, 1);
        
        //Y recalculo la velocidad en los ejes
        recalcula();
    }   
}


void Skull::recalcula(){
    
    float x_distance = targetX - body.getXPosition();   // Distancia en X
    float y_distance = targetY - body.getYPosition();   // Distancia en Y
    
    float angle = atan2(y_distance, x_distance);        // Ángulo dado un vector (en radianes, devolverá un número entre 0 y 1)
    float x_velocity = cos(angle)*velocity;             // Lo multiplico por la velocidad para X
    float y_velocity = sin(angle)*velocity;             // Lo multiplico por la velocidad para Y
    
    body.setLinealVelocicity(x_velocity, y_velocity);   // Le asigno la velocidad al cuerpo
}
