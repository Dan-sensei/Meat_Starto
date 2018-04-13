/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   contactListener.cpp
 * Author: dan
 * 
 * Created on 4 de abril de 2018, 19:13
 */

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>

#include "contactListener.h"

#include "Player.h"
#include "Mapa/Nodo/Nodo.h"
#include "Mapa/Mapa.h"

void contactListener::BeginContact(b2Contact* contact){
    //std::cout << "Start contact" << std::endl;
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    
    void* a = bodyA->GetUserData();
    void* b = bodyB->GetUserData();

    
    physicsEngine::type* typeA = static_cast<physicsEngine::type*>(a);
    physicsEngine::type* typeB = static_cast<physicsEngine::type*>(b);
    
    //   GROUND = 1
    //   PLAYER = 2
    // XPLOTATO = 3

    if(typeA->id == 1 && typeB->id == 2){
        Player* p = static_cast<Player*>(typeB->data);
        p->setAir(1);
    }

}

void contactListener::EndContact(b2Contact* contact){
    //std::cout << "End contact" << std::endl;
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    
    void* a = bodyA->GetUserData();
    void* b = bodyB->GetUserData();
    
    physicsEngine::type* typeA = static_cast<physicsEngine::type*>(a);
    physicsEngine::type* typeB = static_cast<physicsEngine::type*>(b);
    

    if(typeA->id == 1 && typeB->id == 2){
        Player* p = static_cast<Player*>(typeB->data);
        p->setAir(-1);
    }
    
}
