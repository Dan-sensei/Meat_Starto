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
#include "renderEngine.h"
#include "MenuPausa.h"
#include "MenuInicio.h"
#include "Juego.h"

class MPuntuaciones: public State {
public:
    MPuntuaciones();
    MPuntuaciones(const MPuntuaciones& orig);
    virtual ~MPuntuaciones();
    
    void Update();
    virtual void Handle();
    void Render();
    
    static MPuntuaciones* Instance();//Singleton
    
    
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text tsalir;
    sf::Text  titulo;
    sf::RenderWindow* window;
   
    static MPuntuaciones* instance;

};

#endif /* MPUNTUACIONES_H */

