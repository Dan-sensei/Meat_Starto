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

#include "State.h" 
#include "MenuPausa.h"
#include "MenuInicio.h"
#include "MPuntuaciones.h"
#include "Hud.h"

#include "Mapa/Mapa.h"
#include "mj_t.h"
#include "Player.h"
#include "boss.h"
#include "renderEngine/rMusic.h"
#include "particleSystem.h"

class Juego: public State{
public:
    
    static Juego& Instance(){
        static Juego instance;
        return instance;
    }
    ~Juego();
    
    void HandleEvents();
    void Render();
    void Update();  
    virtual void Handle();
    
    void switchCameradirection();
    std::vector<Player*>* getPlayers();

    std::array<float,2> getPlayerPosition(); //DEBERIA DE DEVOLVER TODAS LAS POSICIONES DE TODOS LOS PERSONAJES
private:
    
    Juego();
    Juego(const Juego& orig);
    void operator=(Juego const& orig);
    
    bool* keys;
    std::vector<Player*> readyPlayer;
    
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
    static Juego* instance;
    
    int cameraDirection;
    
    rMusic THE_ARID_FLATS;
    particleSystem rain; 
    Hud *hud;
};

#endif /* Juego_H */

