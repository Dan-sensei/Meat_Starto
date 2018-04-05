/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   boss.h
 * Author: pablomanez
 *
 * Created on 5 de abril de 2018, 16:11
 */

#ifndef BOSS_H
#define BOSS_H

#include "renderEngine.h"
#include "physicsEngine/pBody.h"
#include "physicsEngine/physicsEngine.h"


class boss {
public:
    //<SINGLETON>
    static boss& Instance(){
        static boss instance;
        return instance;
    }
    //</SINGLETON>
    
    void init(int x_);
    void update(int x_m, float x_, float y_);
    void render();
    bool isBossOn();

private:
    //<SINGLETON>
    boss();
    boss(const boss& orig);
    void operator=(boss const& orig);
    //</SINGLETON>
    
    //METODOS
    void crearProyectil(float x_, float y_);
    
    //ATRIBUTOS
    struct t_muro{ //TILES MURO
        renderEngine::rRectangleShape r;    //FORMA
        pBody b;                            //COLISION
    };
    struct proyectil{
        renderEngine::rRectangleShape r;
        float v_x;  //COMPONENTE X DEL VECTOR DE MOVIMIENTO
        float v_y;  //COMPONENTE Y DEL VECTOR DE MOVIMIENTO
    };
    struct jefe{
        renderEngine::rRectangleShape r;    //EL BOSS FINAL
        bool move;                          //TRUE: DERECHA
        std::vector<proyectil> proy;             //VECTOR DE PROYECTILES
    };
    
    t_muro puerta[12];
    jefe javi;
    
    renderEngine::rClock clock_boss;        //DETERMINA LAS ACCIONES DEL BOSS
    renderEngine::rClock dt_boss;           //DELTA TIME 1
    int x_max;                              //X MAXIMA DONDE ACABA EL BOSS
    int x_min;                              //X MINIMA DONDE EMPIEZA EL BOSS
    bool on;            //TRUE: BOSS EN MARCHA
    bool restart;       //TRUE: BOSS INICIADO
    
    
    
};

#endif /* BOSS_H */

