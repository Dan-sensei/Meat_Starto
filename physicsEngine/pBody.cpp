/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pBody.cpp
 * Author: dan
 * 
 * Created on 28 de marzo de 2018, 14:48
 */

#include "pBody.h"

pBody::pBody() {
}

pBody::pBody(const pBody& orig) {
    body = orig.body;
    body->SetUserData(orig.body->GetUserData());
}

void pBody::setLinealVelocicity(float vx_, float vy_){
    b2Vec2 velocity(vx_, vy_);
    body->SetLinearVelocity(velocity);
}

void    pBody::applyForceToCenter( float vx_, float vy_) { body->ApplyForceToCenter(b2Vec2(vx_, vy_), true); }

float   pBody::getLinearXVelocity()  { return body->GetLinearVelocity().x; }

float   pBody::getLinearYVelocity()  { return body->GetLinearVelocity().y; }

float   pBody::getXPosition()        { return pConverter::worldToPixel(body->GetPosition().x); }

float   pBody::getYPosition()        { return pConverter::worldToPixel(body->GetPosition().y); }

float   pBody::getRotation()         { return body->GetAngle()*180/M_PI; }

b2Body* pBody::getBody()             { return body; }

void    pBody::setBody(b2Body* body_){ body = body_; }

void    pBody::setFixedRotation(bool flag_) { body->SetFixedRotation(flag_); }

void    pBody::applyLinearImpulse(float ix_, float iy_) { body->ApplyLinearImpulse(b2Vec2(ix_, iy_), body->GetWorldCenter(), true); }

void    pBody::setUserData(void* data){ 
    // std::cout<< "Data " <<  static_cast<std::string*>(data) << std::endl;
   
    body->SetUserData(data); 

}

void pBody::setPosition(float x, float y) {
    body->SetTransform(b2Vec2(pConverter::pixelToWorld(x), pConverter::pixelToWorld(y)), body->GetAngle());
    body->SetLinearVelocity(b2Vec2(0,0));
}
