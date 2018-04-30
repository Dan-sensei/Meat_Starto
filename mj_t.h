/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mj_t.h
 * Author: pablomanez
 *
 * Created on 1 de abril de 2018, 10:50
 */

#ifndef MJ_T_H
#define MJ_T_H
#include "renderEngine/renderEngine.h"
#include "physicsEngine/pBody.h"
#include "physicsEngine/physicsEngine.h"

class mj_t {
public:
    //<SINGLETON>
    static mj_t& Instance(){
        static mj_t instance;
        return instance;
    }
    //</SINGLETON>
    
    void init(int x_,int y_);
    
    void update();
    void render();
    bool isTetrisOn();
    
private:
    //<SINGLETON>
    mj_t();
    mj_t(const mj_t& orig);
    void operator=(mj_t const& orig);
    //</SINGLETON>
    
    //METODOS
    void crearPieza();
    
    //ATRIBUTOS
    struct muro_{
        renderEngine::rRectangleShape rect;     //FORMA
        pBody pb;
    };
    muro_ m1;
    muro_ m2;
    
    struct pieza_{
        renderEngine::rRectangleShape r[4];     //FORMA
        renderEngine::rTexture t[4];            //TEXTURA
        float vel;                              //VELOCIDAD DE BAJADA
    };
    //POSIBLE CAMBIO A pieza_ *v_piezas;
    std::vector<pieza_> v_piezas;               //VECTOR QUE ALMACENA TODAS LAS PIEZAS
    
    renderEngine::rClock clock;     //TIEMPO MAXIMO DEL MINIJUEGO
    renderEngine::rClock dt;        //DELTA TIME AL CREAR LAS PIEZAS
    int x_min;                      //POSICION MINIMA DONDE SE EJECUTA EL MINIJUEGO
    int x_max;                      //POSICION MAXIMA DONDE SE EJECUTA EL MINIJUEGO
    int y_min;
    bool restart;                   //TRUE: SE HA REINICIADO clock Y SE HA INICIADO EL MINIJUEGO
    bool on;                        //TRUE: EL MINIJUEGO ESTA EN MARCHA
    bool fin;                       //TRUE: SE HA ACABADO EL MINIJUEGO
    
    physicsEngine::type* t;
};

#endif /* MJ_T_H */

