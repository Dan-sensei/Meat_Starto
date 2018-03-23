/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Motor.h
 * Author: alba
 *
 * Created on 14 de marzo de 2018, 18:57
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <iostream>
#include <string>
#include "MenuInicio.h"
#include "State.h"
#include "MenuPausa.h"
#include "Juego.h"

using namespace std;


class Motor {
public:
    Motor();
    Motor(const Motor& orig);
    virtual ~Motor();
    

    void ChangeState(State* pState);
    
    static Motor* Instance();
    
    sf::RenderWindow* window;
    
    
private:
   // MainMenu& m_menuState;
    State* _state;
    static Motor* instance;

};

#endif /* MOTOR_H */

