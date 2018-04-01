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

#include "renderEngine.h"

class mj_t {
public:
    //<SINGLETON>
    static mj_t& Instance(){
        static mj_t instance;
        return instance;
    }
    //</SINGLETON>
    
    void init(int x_);
    
    void update(int x_);
    bool isTetrisOn();
    
private:
    //<SINGLETON>
    mj_t();
    mj_t(const mj_t& orig);
    void operator=(mj_t const& orig);
    //</SINGLETON>
    
    renderEngine::rClock clock;
    int x_min;
    int x_max;
    bool restart;
    bool on;
    bool fin;
};

#endif /* MJ_T_H */

