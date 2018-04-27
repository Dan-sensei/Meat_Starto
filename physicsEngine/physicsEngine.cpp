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


physicsEngine::physicsEngine():world(b2Vec2(0.f, 40.f)) {
    world.SetContactListener(&listener);
}

void physicsEngine::setGravity(float gx_, float gy_){
    b2Vec2 gravity(gx_, gy_);
    world.SetGravity(gravity);
}

pBody physicsEngine::createBody(float width_, float height_, float px_, float py_, char type_, type* data){
    
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
    
    t = new type;
    t->id = 0;
    
    result.getBody()->SetUserData(t);
    
    b2FixtureDef fixtureDef;                                            // Creamos las características físicas del cuerpo con un b2FixtureDef
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.f;                                       
    fixtureDef.shape = &shape;
    
    b2Fixture* fixture = result.getBody()->CreateFixture(&fixtureDef);                       // Finalizamos la creación del Body creado su Fixture
    fixture->SetUserData(data);
    return result;                                                      // Lo devolvemos
}

pBody physicsEngine::createPlayer(float width_, float height_, float px_, float py_, type* main, type* data) {
    
    pBody result;       //Creo un pBody
    
    b2PolygonShape shape;
    shape.SetAsBox(pConverter::pixelToWorld(width_/2), pConverter::pixelToWorld(height_/2), b2Vec2(0, 0), 0);
    
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(pConverter::pixelToWorld(px_), pConverter::pixelToWorld(py_));
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    result.setBody(world.CreateBody(&bodyDef));
    
    
    b2FixtureDef fixtureDef;                                            // Creamos las características físicas del cuerpo con un b2FixtureDef
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.f;                                       
    fixtureDef.shape = &shape;
    b2Fixture* mainBodyFixture = result.getBody()->CreateFixture(&fixtureDef);                       // Finalizamos la creación del Body creado su Fixture
    mainBodyFixture->SetUserData(main);

    
    b2FixtureDef sensor;
    sensor.density = 1.f;
    sensor.isSensor = true;
    b2PolygonShape sensorShape;
    sensorShape.SetAsBox(pConverter::pixelToWorld(5), pConverter::pixelToWorld(5), b2Vec2(0, pConverter::pixelToWorld(height_/2)), 0);
    sensor.shape = &sensorShape;
    b2Fixture* THE_SENSOR = result.getBody()->CreateFixture(&sensor);
   
    THE_SENSOR->SetUserData(data);

    return result;    
}



void physicsEngine::updateWorld(float tick_){ world.Step(tick_, 8.f, 3.f); }


pBody physicsEngine::createGround(std::vector<std::array<int, 2>> vertex_, type* data){

    pBody result;
    
    b2Vec2 vs[vertex_.size()];
    for(int i=0; i< vertex_.size(); i++)
        vs[i].Set(pConverter::pixelToWorld(vertex_[i][0]), pConverter::pixelToWorld(vertex_[i][1]));
    
    b2ChainShape chain;
    chain.CreateChain(vs, vertex_.size());
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    
    result.setBody(world.CreateBody(&bodyDef));
    b2FixtureDef fixtureDef;
    //fixtureDef.density = 1.f;
    fixtureDef.shape = &chain;
    
    b2Fixture* fixture  = result.getBody()->CreateFixture(&fixtureDef);
    fixture->SetUserData(data);
    
    return result;
}

void physicsEngine::detroyBody(pBody body){
    world.DestroyBody(body.getBody());
}

int physicsEngine::getBodyListSize(){
    int c;
    
    c = 0;
    
    b2Body* b = world.GetBodyList();
    while(b){
        b = b->GetNext();
        c++;
    }
    
    return c;
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
