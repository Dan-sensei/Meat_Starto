/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alba
 *
 * Created on 8 de febrero de 2018, 16:47
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include "MenuInicio.h"
#include "Motor.h"
#include "State.h"
#include "MenuPausa.h"
#include "Juego.h"


using namespace std;

int state=0;

int main()
{
    //Creamos una ventana 
    //sf::RenderWindow window(sf::VideoMode(1080, 720), "Menu");
    Motor::Instance();
    State* pState =  MenuInicio::Instance();
    Motor::Instance()->ChangeState(pState);  


    return 0;
}
