/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   physicsEngine.cpp
 * Author: dan
 * 
 * Created on 16 de marzo de 2018, 10:00
 */

#include <random>

#include "physicsEngine.h"
#include "Mapa/Nodo/Nodo.h"

/*
physicsEngine* physicsEngine::pInstance = nullptr;
physicsEngine* physicsEngine::Instance(){
    if(!pInstance)
        pInstance = new physicsEngine;
    
    return pInstance;
}
*/

physicsEngine::physicsEngine():world(b2Vec2(0.f, 40.f)) {
    world.SetContactListener(&listener);
}

void physicsEngine::setGravity(float gx_, float gy_){
    b2Vec2 gravity(gx_, gy_);
    world.SetGravity(gravity);
}

pBody physicsEngine::createBody(float width_, float height_, float px_, float py_, char type_){
    
    pBody result;       //Creo un pBody
    
    b2PolygonShape shape;
    shape.SetAsBox(pConverter::pixelToWorld(width_/2), pConverter::pixelToWorld(height_/2));    // Como serán cuadrados lo creo con SetAsBox, pasándole ancho y alto (dividiendo por 2, ya que Box2D, cuenta desde el centro)
    
    b2BodyDef bodyDef;                                                  // Preparamos las características del cuerpo con b2BodyDef
    bodyDef.position = b2Vec2(pConverter::pixelToWorld(px_), pConverter::pixelToWorld(py_));    // Le asignamos una posición inicial (pasándo al sistema de coordenadas de Box2D)
    
    switch (type_){                                                     // Asignamos el tipo en función de la letra que nos han pasado, en caso de que no te pasen una letra correcta, será STATIC
        case 's':
        case 'S':   bodyDef.type = b2_staticBody;                       //    STATIC: No se moverá con nada
                    break;
                    
        case 'd':
        case 'D':   bodyDef.type = b2_dynamicBody;                      //   DYNAMIC: Se puede controlar y se verá afectado por las fuerzas del mundo y otros cuerpos
                    break;
                    
        case 'k':
        case 'K':   bodyDef.type = b2_kinematicBody;                    // KINEMATIC: Se puede controlar, pero no se verá afectado por otros cuerpos ni las fuerzas del mundo
                    break;
                    
        default:    bodyDef.type = b2_staticBody;
                    break;
    }
    
    bodyDef.fixedRotation = true;                                       // Determina si la rotación del cuerpo es fija
    result.setBody(world.CreateBody(&bodyDef));                         // Creamos el cuerpo usando el world
    result.getBody()->SetUserData((void*)"undefined");
    
    b2FixtureDef fixtureDef;                                            // Creamos las características físicas del cuerpo con un b2FixtureDef
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.f;                                       
    fixtureDef.shape = &shape;
    
    result.getBody()->CreateFixture(&fixtureDef);                       // Finalizamos la creación del Body creado su Fixture
    
    return result;                                                      // Lo devolvemos
}


void physicsEngine::updateWorld(float tick_){ world.Step(tick_, 8.f, 3.f); }


pBody physicsEngine::createGround(std::vector<std::array<float, 2>> vertex_, type* data){

    pBody result;
    
    b2Vec2 vs[vertex_.size()];
    for(int i=0; i< vertex_.size(); i++)
        vs[i].Set(pConverter::pixelToWorld(vertex_[i][0]), pConverter::pixelToWorld(vertex_[i][1]));
    
    b2ChainShape chain;
    chain.CreateChain(vs, vertex_.size());
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    
    result.setBody(world.CreateBody(&bodyDef));
    result.setUserData(data);

    b2FixtureDef fixtureDef;
    //fixtureDef.density = 1.f;
    fixtureDef.shape = &chain;
    
    result.getBody()->CreateFixture(&fixtureDef);

    return result;
}

float physicsEngine::genFloatRandom(float min, float max){
    std::random_device rd;
    std::default_random_engine gen(rd());

    std::uniform_real_distribution<float> distribution(min, max);
    
    return distribution(gen);
}

int physicsEngine::genIntRandom(int min, int max){
    std::random_device rd;
    std::default_random_engine gen(rd());

    std::uniform_int_distribution<int> distribution(min, max);
    
    return distribution(gen);
}