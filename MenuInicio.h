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
    
    void Update();
    virtual void Handle();
    void Render();
    
    
    static MenuInicio* Instance();//Singleton
    
    int numplayers;
    
private:
     int selectedItemIndex;
    int selectedItemIndex2;
    int selectedItemIndex3;
   // int selectedItemIndex4;
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
    sf::RenderWindow* window;
    static MenuInicio* instance;
    
    float width;
    float height;
    
    float posx;
    float posy;
    
    bool primero;
   
    renderEngine *sfml;
    renderEngine::rTexture text_fondo;
    renderEngine::rRectangleShape f1;

    renderEngine::rSprite logo;
    renderEngine::rSprite logo1;
    renderEngine::rSprite personaje;
    renderEngine::rSprite mancha[MAX_NUMBER_OF_ITEMS];
    renderEngine::rSprite mancha2[MAX_NUMBER_OF_ITEMS2];
    renderEngine::rSprite mancha3[MAX_NUMBER_OF_ITEMS3];
    
    float tam;
    
    void muevepersonaje(int selec);


};

#endif /* MENUINICIO_H */

