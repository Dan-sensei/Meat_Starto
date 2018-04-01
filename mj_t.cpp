/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mj_t.cpp
 * Author: pablomanez
 * 
 * Created on 1 de abril de 2018, 10:50
 */

#include <iostream>
#include "mj_t.h"

mj_t::mj_t() {}

void mj_t::init(int x_) {
    //LE PASO LA x_max DE TILE
    x_max = x_;
    x_min = x_ - 19*70; //LONTIGUD YA PREFEDINIDA DE TILED
                        //CUANDO LLEGUE A LA MITAD DEL MINIJUEGO EMPIEZA
    
    restart = false;
    on = false;
    fin = false;
    
}

void mj_t::update(int x_) {
    if(!fin){
        if(x_ > x_min && x_ < x_max){
                //std::cout << "Estoy dentro del tetris wey" << std::endl;
            on = true;

            if(restart == false){
                    //std::cout << "REINICIO RELOJ" << std::endl;
                clock.restart();
                restart = true;
            }
            else{
                std::cout << "  Tiempo TETRIS: " << clock.getElapsedTime().asSeconds() << std::endl;
            }
            
            if(clock.getElapsedTime().asSeconds() > 5){
                fin = true;
                on = false;
            }


        }
        else if(x_ < x_min || x_ > x_max){
            on = false;
        }
    }
}

bool mj_t::isTetrisOn() {
    return on;
}







mj_t::mj_t(const mj_t& orig) {
}