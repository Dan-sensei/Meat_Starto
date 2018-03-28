/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pConverter.h
 * Author: dan
 *
 * Created on 28 de marzo de 2018, 14:51
 */

#ifndef PCONVERTER_H
#define PCONVERTER_H

class pConverter {
public:
    pConverter();
    
    float static pixelToWorld(float p_);        // Convierte los pixeles de pantalla al sistema de coordenadas de Box2D
    float static worldToPixel(float w_);        // Convierte del sitema de coordenadas de Box2D a pixeles en patanlla
    
private:

};

#endif /* PCONVERTER_H */

