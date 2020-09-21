/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pConverter.cpp
 * Author: dan
 * 
 * Created on 28 de marzo de 2018, 14:51
 */

#define SCALE 60.f

#include "pConverter.h"

pConverter::pConverter() {
}

float pConverter::pixelToWorld(float p_) { return p_/SCALE; }

float pConverter::worldToPixel(float w_) { return w_*SCALE; }