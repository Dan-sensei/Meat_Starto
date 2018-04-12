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
#include <random>
#include <math.h>


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
    void crearAbanicoProyectiles();
    void crearProyectil(float x_, float y_);
    void crearProyectilTele();
    void updateJavi();
    
    //float getVX_BP(); //DEVUELVE LA COMPONENTE X DEL VECTOR VELOCIDAD DEL 
    
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
    struct proyectilT: proyectil{
        float a;            //AMPLITUD
        float a_1;          //AMPLITUD AUXILIAR 1
        float a_2;          //AMPLITUD AUXILIAR 2
        
        float x_ini;        //X INICIAL
        float x_fin;        //X FINAL
        float y_ini;        //Y INICIAL
        float y_fin;        //Y FINAL
        
        float angle;
        
        
    };
    struct jefe{
        renderEngine::rRectangleShape r;            //EL BOSS FINAL
        std::vector<proyectil*> proy;               //VECTOR DE PROYECTILES
        std::vector<proyectilT*> proyT;             //VECTOR DE PROYECTILES T
        
        //LOS VALORES DE x_f E y_f CAMBIAN
        float x_v;          //X DEL VECTOR VELOCIDAD
        float y_v;          //Y DEL VECTOR VELOCIDAD
        int x_f;            //X DE POSICION FINAL
        int y_f;            //Y DE POSICION FINAL
        bool llegada;       //TRUE: HA LLEGADO A LA POSICION FINAL Y BUSCA UNA NUEVA
        renderEngine::rIntRect *ir;
    };
    renderEngine::rRectangleShape r_aux;    //DEBUG
    renderEngine::rRectangleShape ir_aux;   //DEBUG
    t_muro puerta[12];
    jefe javi;
    
    renderEngine::rClock clock_boss;        //DETERMINA LAS ACCIONES DEL BOSS
    renderEngine::rClock dt_fan;            //ABANICO
    renderEngine::rClock dt_boss;           //DELTA TIME 1
    int x_max;                              //X MAXIMA DONDE ACABA EL BOSS
    int x_min;                              //X MINIMA DONDE EMPIEZA EL BOSS
    bool on;                                //TRUE: BOSS EN MARCHA
    bool restart;                           //TRUE: BOSS INICIADO
    
    
    
};

#endif /* BOSS_H */

