/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Juego.h
 * Author: alba
 *
 * Created on 15 de marzo de 2018, 22:20
 */

#ifndef JUEGO_H
#define JUEGO_H

#include <cstdlib>
#include <iostream>
#include <Box2D/Box2D.h>
#include <math.h>

#include <renderEngine.h>
#include <physicsEngine/physicsEngine.h>
#include <physicsEngine/pBody.h>

#include "State.h" 
#include "MenuPausa.h"
#include "MenuInicio.h"
#include "MPuntuaciones.h"

#include "Mapa/Mapa.h"
#include "mj_t.h"
#include "Player.h"
#include "boss.h"

class Juego: public State{
public:
    Juego();
    Juego(const Juego& orig);
    virtual ~Juego();
    
    void Render();
    void Update();  
    virtual void Handle();
    
    static Juego* Instance();//Singleton

    
private:
    bool* keys;
    Player * readyPlayerOne;
    
    renderEngine::rClock masterClock;
    renderEngine::rClock animationClock;
    
    double dt;
    float accumulator;
    double tick; //PARA LA INTERPOLACION
    
    renderEngine::rView *view;
    
    //FPS
    renderEngine::rClock cl_fps;
    float lastTime;
    float currentTime;
    float fps;
    
    sf::Font font;
    sf::Text  titulo;
    sf::Text  titulo2;
    sf::Text  titulo3;
    sf::RenderWindow* window;
    static Juego* instance;

};

#endif /* Juego_H */

