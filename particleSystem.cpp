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
/*
#include <complex>

#include "particleSystem.h"

particleSystem::particleSystem(int x, int y, int type_) {
    
    int sizeX = AssetManager::GetTexture("assets/triangle.png").getXSize();
    int sizeY = AssetManager::GetTexture("assets/triangle.png").getYSize();
    sprite.setTexture(AssetManager::GetTexture("assets/triangle.png"));
    sprite.setOrigin(sizeX/2, sizeY/2);
    sprite.setPosition(x, y);
    //sprite.setScale(0.02, 0.5);
    
    max_particles = 50;
    lifeTime = -1;
    xPos = x;
    yPos = y;
    xVelocity = yVelocity = 0;
    radius = 0;
    xSide = ySide = 0;
    rotation = 0;
    delayBetweenParticlesGeneration = 200;
    targetX = targetY = 0;
    
    particle_min_velocity = particle_max_velocity = 10;
    particle_min_angular_velocity = particle_max_angular_velocity = 0;
    particle_min_lifeTime = particle_max_lifeTime = 3;
    
    accumulator = 0;

    loop = true;
    
    type = type_;   // 0 = Circle, 1 = Square
    box.setOutlineThickness(2);
    box.setFillColor('t');
    box.setOutlineColor('r');
    box.setSize(xSide, ySide);
    box.setOrigin(xSide/2, ySide/2);
    box.setPosition(xPos, yPos);
}

particleSystem::particleSystem(const particleSystem& orig) {
}

particleSystem::~particleSystem() {
}

void particleSystem::draw(float tick_) {
    for(std::list<Particle>::iterator it=lista_particular.begin(); it!=lista_particular.end(); ++it){
        (*it).interpola(tick_);
        (*it).draw();   
    }
    box.draw();
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
    box.setPosition(xPos, yPos);
    std::cout << "PARTICULAS " << lista_particular.size() << std::endl;
    float px, py, vx, vy, r, vr, life;
    float aux_v;
    float aux_target_x, aux_target_y;
    int c = 0;
    //std::cout << "ElapsedTime " << timerClock.getElapsedTime().asMilliseconds() << " | Delay " << delayBetweenParticlesGeneration << std::endl;
    if(timerClock.getElapsedTime().asMilliseconds() > delayBetweenParticlesGeneration){
        accumulator += timerClock.restart().asMilliseconds();
        while(accumulator > delayBetweenParticlesGeneration){
            accumulator -= delayBetweenParticlesGeneration;
            
            // Variables independientes del shape
            if(lista_particular.size() < max_particles){
                c++;
                //Rotacion
                r = particle_max_rotation;
                if(particle_min_rotation != particle_max_rotation)
                    r = physicsEngine::Instance().genIntRandom(particle_min_rotation, particle_max_rotation);
                //Velocidad de rotacion
                vr = particle_max_angular_velocity;
                if(particle_min_angular_velocity != particle_max_angular_velocity)
                    vr = physicsEngine::Instance().genIntRandom(particle_min_angular_velocity, particle_max_angular_velocity);
                //Tiempo de vida
                life = particle_max_lifeTime;
                if(particle_min_lifeTime != particle_max_lifeTime)
                    life = physicsEngine::Instance().genFloatRandom(particle_min_lifeTime, particle_max_lifeTime);
                //Velocidad absoluta
                aux_v = particle_max_velocity;
                if(particle_min_velocity != particle_max_velocity)
                    aux_v = physicsEngine::Instance().genFloatRandom(particle_min_velocity, particle_max_velocity);

                aux_target_x = targetX;
                aux_target_y = targetY;
                if(aux_target_x == 0 && aux_target_y == 0){
                    aux_target_x = physicsEngine::Instance().genFloatRandom(-1, 1);
                    aux_target_y = physicsEngine::Instance().genFloatRandom(-1, 1);
                }

                px = xPos;
                py = yPos;

                if(type==0){    //CIRCULO
                    if(radius != 0){
                        px = physicsEngine::Instance().genFloatRandom(-1, 1);
                        float a = acos(px);
                        float maxY = sin(a);
                        py = physicsEngine::Instance().genFloatRandom(-maxY, maxY);

                        px *= radius;
                        py *= radius;

                        px += xPos;
                        py += yPos;
                    }

                    vx = aux_target_x*aux_v;
                    vy = aux_target_y*aux_v;
                }
                else if(type==1){   //RECTANGULO
                    if( xSide != 0 )
                        px = physicsEngine::Instance().genFloatRandom(xPos-(xSide/2), xPos+(xSide/2));
                    if( ySide != 0)
                        py = physicsEngine::Instance().genFloatRandom(yPos-(ySide/2), yPos+(ySide/2));

                    vx = aux_target_x*aux_v;
                    vy = aux_target_y*aux_v;
                }
               lista_particular.emplace_back(px, py, vx, vy, r, vr, sprite, life);
            }
        }

    }
    
    std::list<Particle>::iterator it = lista_particular.begin();
    while(it != lista_particular.end()){
        
        if((*it).getTimeAlive().asSeconds() > (*it).getLifeTime())
            lista_particular.erase(it++);    
        else
            ++it;
    }
    
    for(std::list<Particle>::iterator it=lista_particular.begin(); it!=lista_particular.end(); ++it){
        (*it).preState();
        (*it).update();   
    }
}

void particleSystem::setGenerationTimer(float s) {
    delayBetweenParticlesGeneration = s;
}

void particleSystem::setCircle(float radius_) {
    radius = radius_;
}

void particleSystem::setLifeTime(float time) {
    lifeTime = time;
}

void particleSystem::setLoop(bool loop_) {
    loop = loop_;
}

void particleSystem::setMaxParticleAmout(int n) {
    max_particles = n;
}

void particleSystem::setParticleAngularVelocity(float speed) {
    particle_min_angular_velocity = particle_max_angular_velocity = speed;
}

void particleSystem::setParticleAngularVelocityRandomBetween(float min, float max) {
    particle_min_angular_velocity = min;
    particle_max_angular_velocity = max;
}

void particleSystem::setParticleLifeTime(float time) {
    particle_min_lifeTime = particle_max_lifeTime = time;
}

void particleSystem::setParticleLifeTimeRandomBetween(float min, float max) {
    particle_min_lifeTime = min;
    particle_max_lifeTime = max;
}

void particleSystem::setParticleRotation(float degree) {
    particle_min_rotation = particle_max_rotation = degree;
}

void particleSystem::setParticleSpeed(float f) {
    particle_min_velocity = particle_max_velocity = f;
}

void particleSystem::setParticleSpeedRandomBetween(float min, float max) {
    particle_min_velocity = min;
    particle_max_velocity = max;
}

void particleSystem::setRectangle(float sideX, float sideY) {
    xSide = sideX;
    ySide = sideY;
    box.setSize(xSide, ySide);
    box.setOrigin(xSide/2, ySide/2);
    box.setPosition(xPos, yPos);
}

void particleSystem::setSprite(const std::string& filename) {
    int sizeX = AssetManager::GetTexture(filename).getXSize();
    int sizeY = AssetManager::GetTexture(filename).getYSize();
    renderEngine::rSprite newSprite;
    newSprite.setTexture(AssetManager::GetTexture(filename));
    newSprite.setOrigin(sizeX/2, sizeY/2);
    
    sprite = newSprite;
}

void particleSystem::setParticleDirection(float x, float y) {
    targetX = x;
    targetY = y;
}

void particleSystem::setPosition(float x, float y) {
    xPos = x;
    yPos = y;
}

void particleSystem::setSpriteSize(float x, float y) {
    sprite.setScale(x, y);
}

void particleSystem::setParticleRotationRandomBetween(float min, float max) {
    particle_min_rotation = min;
    particle_max_rotation = max;
}

float particleSystem::getYPosition() {
    return yPos;
}

*/