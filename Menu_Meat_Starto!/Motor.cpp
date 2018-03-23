/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Motor.cpp
 * Author: alba
 * 
 * Created on 14 de marzo de 2018, 18:57
 */

#include "Motor.h"
#include <iostream>
#include <string>
#include "MenuInicio.h"
#include "State.h"


Motor* Motor::instance = NULL;
Motor* Motor::Instance(){
    
    if(instance == NULL) instance = new Motor();

    return instance;
}

Motor::Motor() {

    window= new sf::RenderWindow(sf::VideoMode(1080, 720), "Menu");
    this->_state = 0;

}


Motor::Motor(const Motor& orig) {
}

Motor::~Motor() {
}


void Motor::ChangeState(State* pState){
        this->_state = pState;
        if(NULL != this->_state)
     {
        this->_state->Handle(this);
     }
        
}