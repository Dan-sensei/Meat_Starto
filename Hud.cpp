/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hud.cpp
 * Author: alba
 * 
 * Created on 4 de abril de 2018, 13:10
 */


#include "Hud.h"
#include "MenuInicio.h"

Hud::Hud(std::vector<Player*> jugadores) {//cambiar y pasar array de jugadores

    players=jugadores;//cambiar a array de jugadores

    width =  sfml->Instance().getViewSize()[0];
    height = sfml->Instance().getViewSize()[1];
    
    posx = sfml->Instance().getViewCenter()[0];
    posy = sfml->Instance().getViewCenter()[1];
    
    font.loadFromFile("resources/fuente.ttf");
    
      //imprime el numero de player
       menu[0].setFont(font);
       menu[0].setCharacterSize(30);
       menu[0].setFillColor('k');

        //imprime el nombre del personaje
       menu[1].setFont(font);
       menu[1].setCharacterSize(30);
       menu[1].setFillColor('k');

        //imprime el nivel del personaje
       menu[2].setFont(font);
       menu[2].setCharacterSize(30);
       menu[2].setFillColor('k');
       
}

Hud::Hud(const Hud& orig) {
}

Hud::~Hud() {
}


void Hud::cambiarHud(Player* player){

        width =  sfml->Instance().getViewSize()[0];
        height = sfml->Instance().getViewSize()[1];

        posx = sfml->Instance().getViewCenter()[0];
        posy = sfml->Instance().getViewCenter()[1];
    
       menu[0].setString("Player " + std::to_string(player->getId()+1));
       menu[1].setString("Level " + std::to_string(player->getLevel()));
       menu[2].setString("Exp: " + std::to_string(player->getExp()) +"/"+ std::to_string(player->getExp_levelup()));
       hudsprite=player->getSprite();

               
       //cambia la posicion segun el player             
       switch(player->getId()){

          case 0:       
              hudsprite.setPosition(posx-5*(width/12),posy-height/2.2);
               menu[0].setPosition(posx-5.5*(width/12),posy-height/2.4);
               menu[1].setPosition(posx-5.5*(width/12),posy-height/2.6);
               menu[2].setPosition(posx-5.5*(width/12),posy-height/2.8);
               break;
           case 1:
               hudsprite.setPosition(posx-2*width/12,posy-height/2.2);
               menu[0].setPosition(posx-2.5*width/12,posy-height/2.4);
               menu[1].setPosition(posx-2.5*width/12,posy-height/2.6);
               menu[2].setPosition(posx-2.5*width/12,posy-height/2.8);
               break;
             case 2:
               hudsprite.setPosition(posx+1.5*width/12,posy-height/2.2);
               menu[0].setPosition(posx+width/12,posy-height/2.4);
               menu[1].setPosition(posx+width/12,posy-height/2.6);
               menu[2].setPosition(posx+width/12,posy-height/2.8);
               break;
           case 3:
               hudsprite.setPosition(posx+4.5*(width/12),posy-height/2.2);
               menu[0].setPosition(posx+4*(width/12),posy-height/2.4);
               menu[1].setPosition(posx+4*(width/12),posy-height/2.6);
               menu[2].setPosition(posx+4*(width/12),posy-height/2.8);
               break;
       }
    
}

void Hud::render(){

    for(int i=0; i<players.size(); i++){

        cambiarHud(players[i]);
        hudsprite.draw();
        for(int i=0; i<3; i++){
            menu[i].draw();
        }
    }

}
