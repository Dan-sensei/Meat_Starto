/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MPuntuaciones.h
 * Author: alba
 *
 * Created on 23 de marzo de 2018, 19:25
 */

#ifndef MPUNTUACIONES_H
#define MPUNTUACIONES_H

#include "State.h" 
#include "MenuPausa.h"
#include "MenuInicio.h"
#include "Juego.h"
#include "Player.h"

class MPuntuaciones: public State {
public:
    MPuntuaciones();
    MPuntuaciones(const MPuntuaciones& orig);
    virtual ~MPuntuaciones();
    
    void Update();
    virtual void Handle();
    void Render();
    void recuento();
    
    static MPuntuaciones* Instance();//Singleton
    
    
private:
    int selectedItemIndex;
    sf::Font font;
     sf::Text** menu;
    renderEngine::rSprite* sprite;
    sf::Text tsalir;
    sf::Text  titulo;
    sf::RenderWindow* window;
   
    static MPuntuaciones* instance;
    
    float width;
    float height;
    
    float posx;
    float posy;
    
    renderEngine *sfml;
    renderEngine::rTexture text_fondo;
    renderEngine::rRectangleShape f1;
    renderEngine::rSprite mancha;
    renderEngine::rSprite personaje;

    std::vector<Player*>* jugadores;

};

#endif /* MPUNTUACIONES_H */

