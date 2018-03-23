/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MenuPausa.h
 * Author: alba
 *
 * Created on 15 de marzo de 2018, 21:30
 */

#ifndef MENUPAUSA_H
#define MENUPAUSA_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h" 
#include "Motor.h"
#include "MenuInicio.h"
#include "Juego.h"

#define NUMBER_OF_ITEMS 2

class MenuPausa: public State{
public:
    MenuPausa();
    MenuPausa(const MenuPausa& orig);
    virtual ~MenuPausa();
    
    void MoveUp();
    void MoveDown();
    
    virtual void Handle(Motor* pMotor);
    void Update(sf::Event event);
    void Render();
    
    static MenuPausa* Instance();//Singleton
    
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[NUMBER_OF_ITEMS];
    sf::Text  titulo;
    Motor* pgame;
    sf::RenderWindow* window;
    static MenuPausa* instance;

};

#endif /* MENUPAUSA_H */

