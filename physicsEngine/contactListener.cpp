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
    //    SKULL = 4
    
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    
    // SUELO CON JUGADOR
    if(typeA->id == 1 && typeB->id == 2 ){
        if(worldManifold.normal.x == 0 && worldManifold.normal.y == -1){
            Player* p = static_cast<Player*>(typeB->data);
            p->setAir(1); 
        }
    }
    else if(typeB->id == 1 && typeA->id == 2){
        if(worldManifold.normal.x == 0 && worldManifold.normal.y == -1){
            Player* p = static_cast<Player*>(typeA->data);
            p->setAir(1);    
        }
    }
    
    // SKULL CON JUGADOR
    if(typeA->id == 4 && typeB->id == 2 ){
        if(worldManifold.normal.x == 0 && worldManifold.normal.y == -1){
            Player* p = static_cast<Player*>(typeB->data);
            p->setAir(1); 
        }
    }
    else if(typeB->id == 4 && typeA->id == 2){
        if(worldManifold.normal.x == 0 && worldManifold.normal.y == -1){
            Player* p = static_cast<Player*>(typeB->data);
            p->setAir(1); 
        }
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
    
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    
    if(typeA->id == 1 && typeB->id == 2){
        if(worldManifold.normal.x == 0 && worldManifold.normal.y == -1){
            Player* p = static_cast<Player*>(typeB->data);
            p->setAir(-1);
        }
    }
    else if(typeB->id == 1 && typeA->id == 2){
        if(worldManifold.normal.x == 0 && worldManifold.normal.y == -1){
            Player* p = static_cast<Player*>(typeA->data);
            p->setAir(-1);
        }
    }
    
    if(typeA->id == 4 && typeB->id == 2){
        if(worldManifold.normal.x == 0 && worldManifold.normal.y == -1){
            Player* p = static_cast<Player*>(typeB->data);
            p->setAir(-1);
        }
    }
    else if(typeB->id == 4 && typeA->id == 2){
        if(worldManifold.normal.x == 0 && worldManifold.normal.y == -1){
            Player* p = static_cast<Player*>(typeB->data);
            p->setAir(-1);
        }
    }
    
}
