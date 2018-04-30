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
#include "renderEngine/renderEngine.h"


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
    void stateMenu();
    
     int selectedItemIndex;
    int selectedItemIndex2;
    int selectedItemIndex3;
   // int selectedItemIndex4;
    renderEngine::rFont font;
    renderEngine::rText menu[MAX_NUMBER_OF_ITEMS];
    renderEngine::rText menuop[MAX_NUMBER_OF_ITEMS2];
    renderEngine::rText menuplayer[MAX_NUMBER_OF_ITEMS3];
    renderEngine::rSprite fondo;
    int statemenu;
    renderEngine::rText  titulo;
    renderEngine::rText  titulo2;
    renderEngine::rText titulo3;
    renderEngine::rText titulo4;
    renderEngine::rText menuhow;
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
    renderEngine::rSprite controles;
    renderEngine::rSprite mancha[MAX_NUMBER_OF_ITEMS];
    renderEngine::rSprite manchahtp;
    
    float tam;
    
    void muevepersonaje(int selec);
    renderEngine::rTime reloj;

    //PARA LOS MANDOS
    bool m_Up;
    bool m_Down;
    bool controller_move;
};

#endif /* MENUINICIO_H */

