/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   particleSystem.cpp
 * Author: dan
 * 
 * Created on 14 de abril de 2018, 9:51
 */

#include "particleSystem.h"

particleSystem::particleSystem(int x, int y) {
    xPos = x;
    yPos = y;
    sprite.setTexture(AssetManager::GetTexture("assets/triangle.png"));
    n_particles = 50;
    timer = 0.2;
    min_velocity = 10;
    max_velocity = 10;
    min_angular_velocity = 0;
    max_angular_velocity = 0;
    accumulator = 0;

}

particleSystem::particleSystem(const particleSystem& orig) {
}

particleSystem::~particleSystem() {
}

void particleSystem::draw() {
    for(std::list<Particle>::iterator it=lista_particular.begin(); it!=lista_particular.end(); ++it){
        (*it).draw();   
    }
}

void particleSystem::interpola(float tick_) {
    for(std::list<Particle>::iterator it=lista_particular.begin(); it!=lista_particular.end(); ++it){
        (*it).interpola(tick_);   
    }
}

void particleSystem::newState() {
    for(std::list<Particle>::iterator it=lista_particular.begin(); it!=lista_particular.end(); ++it){
        (*it).newState();   
    }
}

void particleSystem::preState() {
    for(std::list<Particle>::iterator it=lista_particular.begin(); it!=lista_particular.end(); ++it){
        (*it).preState();   
    }
}

void particleSystem::update() {
    
    std::list<Particle>::iterator it = lista_particular.begin();
    
    while(it != lista_particular.end()){
        
        if((*it).getTimeAlive().asSeconds() > (*it).getLifeTime())
            lista_particular.erase(it++);    
        else
            ++it;
        
    }
    
    
    if(timerClock.getElapsedTime().asSeconds() > timer){
        accumulator += timerClock.restart().asSeconds();
        while(accumulator > timer){
            accumulator -= timer;
            
            
            //lista_particular.emplace_back();
        }
        
    }
   
}

void particleSystem::setGenerationTimer(float s) {
    timer = s;
}
