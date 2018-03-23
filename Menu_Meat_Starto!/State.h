/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State.h
 * Author: alba
 *
 * Created on 19 de marzo de 2018, 18:47
 */

#ifndef STATE_H
#define STATE_H


#include <iostream>
#include <SFML/Graphics.hpp>

class Motor;

class State {
public:
    
    virtual void Update(sf::Event event) = 0;
    virtual void Render() = 0;
    virtual void Handle(Motor* pMotor) = 0;
private:

};


#endif /* STATE_H */

