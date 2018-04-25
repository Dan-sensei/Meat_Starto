/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ground.cpp
 * Author: dan
 * 
 * Created on 11 de abril de 2018, 3:34
 */

#include "Ground.h"

Ground::Ground(std::vector<std::array<int,2> > coords) {
    physicsEngine* world;
    
    t = new physicsEngine::type;
    t->id = 1;
    t->data = this;
    body = world->Instance().createGround(coords, t);
    
}

Ground::Ground(const Ground& orig) {
    body = orig.body;
}

Ground::~Ground() {
    std::cout << "Destruyendo suelo" << std::endl;
}

