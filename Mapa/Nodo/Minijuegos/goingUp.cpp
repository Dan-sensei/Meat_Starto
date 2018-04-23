/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   goingUp.cpp
 * Author: dan
 * 
 * Created on 22 de abril de 2018, 20:02
 */

#include "goingUp.h"

goingUp::goingUp(int x, int y, int width, int height) {
    initArea.setPosition(x, y);
    initArea.setSize(width, height);
}


goingUp::goingUp(const goingUp& orig) {
}

goingUp::~goingUp() {
}

void goingUp::update() {
    //std::cout << "UEEEEE" << std::endl;
}
