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

#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h" 
#include "Motor.h"
#include "MenuPausa.h"
#include "MenuInicio.h"
#include "MPuntuaciones.h"

class Juego: public State{
public:
    Juego();
    Juego(const Juego& orig);
    virtual ~Juego();
    
    void Render();
    void Update(sf::Event event);  
    virtual void Handle(Motor* pMotor);
    
    static Juego* Instance();//Singleton

    
private:
    sf::Font font;
    sf::Text  titulo;
    sf::Text  titulo2;
    sf::Text  titulo3;
    Motor* pgame;
    sf::RenderWindow* window;
    static Juego* instance;

};

#endif /* Juego_H */

