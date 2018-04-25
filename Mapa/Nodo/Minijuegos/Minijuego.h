/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Minijuego.h
 * Author: dan
 *
 * Created on 23 de abril de 2018, 10:46
 */

#ifndef MINIJUEGO_H
#define MINIJUEGO_H

class Minijuego {
public:
    Minijuego();
    Minijuego(const Minijuego& orig);
    virtual ~Minijuego();
    
    virtual void update();
    virtual void draw(float tick_);
    
private:

};

#endif /* MINIJUEGO_H */

