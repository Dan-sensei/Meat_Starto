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

void contactListener::BeginContact(b2Contact* contact){
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    
    if(bodyA->GetUserData() == "Player1" && bodyB->GetUserData() == "Load"){
        
    }
}

void contactListener::EndContact(b2Contact* contact){
    
}
