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
#include "MenuInicio.h"
#include "Juego.h"
#include "Player.h"

#define NUMBER_OF_ITEMS 3
#define NUMBER_OF_ITEMS2 2

class MenuPausa: public State{
public:
    MenuPausa();
    MenuPausa(const MenuPausa& orig);
    virtual ~MenuPausa();
    
    void MoveUp();
    void MoveDown();
    
    virtual void Handle();
    void Update();
    void Render();
    
    static MenuPausa* Instance();//Singleton
    
private:
  int selectedItemIndex;
    int selectedItemIndex2;

    int statemenu;
    sf::Font font;
    sf::Text menu[NUMBER_OF_ITEMS];
    sf::Text  titulo;
    static MenuPausa* instance;
    
    sf::Text  titulo2;
    sf::Text menuhow;;

    float width;
    float height;
    
    float posx;
    float posy;
    
    renderEngine *sfml;
    renderEngine::rTexture text_fondo;
    renderEngine::rRectangleShape f1;
    renderEngine::rSprite personaje;
    renderEngine::rSprite mancha[NUMBER_OF_ITEMS];
    renderEngine::rSprite manchahtp;
    renderEngine::rSprite controles;
    
    void muevepersonaje(int selec);
    
    std::vector<Player*>* jugadores;
    
    void PonInmortal();
    bool InmortalOn;
};

#endif /* MENUPAUSA_H */

