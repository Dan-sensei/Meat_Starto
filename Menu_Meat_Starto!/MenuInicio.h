/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MenuInicio.h
 * Author: alba
 *
 * Created on 22 de marzo de 2018, 20:38
 */

#ifndef MENUINICIO_H
#define MENUINICIO_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h" 
#include "Motor.h"
#include "MenuPausa.h"
#include "Juego.h"


#define MAX_NUMBER_OF_ITEMS 4
#define MAX_NUMBER_OF_ITEMS2 2
#define MAX_NUMBER_OF_ITEMS3 3

class MenuInicio: public State {
public:
    MenuInicio();
    MenuInicio(const MenuInicio& orig);
    virtual ~MenuInicio();
    
    void MoveUp();
    void MoveDown();
    
    void Update(sf::Event event);
    virtual void Handle(Motor* pMotor);
    void Render();
    
    
    static MenuInicio* Instance();//Singleton
    
    int numplayers;
    
private:
    int selectedItemIndex;
    int selectedItemIndex2;
    int selectedItemIndex3;
    int selectedItemIndex4;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    sf::Text menuop[MAX_NUMBER_OF_ITEMS2];
    sf::Text menuplayer[MAX_NUMBER_OF_ITEMS3];
    sf::Sprite fondo;
    int statemenu;
    sf::Text  titulo;
    sf::Text  titulo2;
    sf::Text titulo3;
    sf::Text titulo4;
    sf::Text menuhow;
    Motor* pgame;
    sf::RenderWindow* window;
    static MenuInicio* instance;


};

#endif /* MENUINICIO_H */

