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
    
    if (!font.loadFromFile("resources/fuente.ttf"))
    {
            std::cerr << "Error cargando la imagen sprite.png";
            exit(0);	
    }
    
      //imprime el numero de player
       menu[0].setFont(font);
       menu[0].setCharacterSize(30);
       menu[0].setFillColor(sf::Color::Black);

        //imprime el nombre del personaje
       menu[1].setFont(font);
       menu[1].setCharacterSize(30);
       menu[1].setFillColor(sf::Color::Black);

        //imprime el nivel del personaje
       menu[2].setFont(font);
       menu[2].setCharacterSize(30);
       menu[2].setFillColor(sf::Color::Black);
       
}

Hud::Hud(const Hud& orig) {
}

Hud::~Hud() {
}

//todos arriba
/*void Hud::cambiarHud(Player* player){
    
       menu[0].setString("Player " + std::to_string(player->getId()+1));
       menu[1].setString(""+player->getName());
       menu[2].setString("Level " + std::to_string(player->getLevel()));
       hudsprite=player->getSprite();

               
       //cambia la posicion segun el player             
       switch(player->getId()){

           case 0:       
               hudsprite.setPosition(posx-width/12.3,posy-height/2.2);
               menu[0].setPosition(posx-width/12.2,posy-height/2.4);
               menu[1].setPosition(posx-width/12.2,posy-height/2.6);
               menu[2].setPosition(posx-width/12.2,posy-height/2.8);
               break;
           case 1:
               hudsprite.setPosition(posx-width/12.6,posy-height/2.2);
               menu[0].setPosition(posx-width/12.4,posy-height/2.4);
               menu[1].setPosition(posx-width/12.4,posy-height/2.6);
               menu[2].setPosition(posx-width/12.4,posy-height/2.8);
               break;
           case 2:
               hudsprite.setPosition(posx,posy-height/2.2);
               menu[0].setPosition(posx,posy-height/2.4);
               menu[1].setPosition(posx,posy-height/2.6);
               menu[2].setPosition(posx,posy-height/2.8);
               break;
           case 3:
               hudsprite.setPosition(posx+width/12.6,posy-height/2.2);
               menu[0].setPosition(posx+width/12.4,posy-height/2.4);
               menu[1].setPosition(posx+width/12.4,posy-height/2.6);
               menu[2].setPosition(posx+width/12.4,posy-height/2.8);
               break;

       }
    
}*/

//con un jugador en cada esquina
/*void Hud::cambiarHud2(Player* player){

       menu[0].setString("Player " + std::to_string(player->getId()+1));
       menu[1].setString(""+player->getName());
       menu[2].setString("Level " + std::to_string(player->getLevel()));
       hudsprite=player->getSprite();

               
       //cambia la posicion segun el player             
       switch(player->getId()){

           case 0:       
               hudsprite.setPosition(posx-width/12.3,posy-height/2.2);
               menu[0].setPosition(posx-width/12.2,posy-height/2.4);
               menu[1].setPosition(posx-width/12.2,posy-height/2.6);
               menu[2].setPosition(posx-width/12.2,posy-height/2.8);
               break;
           case 1:
               hudsprite.setPosition(posx+width/12.6,posy-height/2.2);
               menu[0].setPosition(posx+width/12.7,posy-height/2.4);
               menu[1].setPosition(posx+width/12.7,posy-height/2.6);
               menu[2].setPosition(posx+width/12.7,posy-height/2.8);
               break;
           case 2:
               hudsprite.setPosition(posx-width/12.3,posy+height/2.9);
               menu[0].setPosition(posx-width/12.2,posy+height/2.6);
               menu[1].setPosition(posx-width/12.2,posy+height/2.4);
               menu[2].setPosition(posx-width/12.2,posy+height/2.2);
               break;
           case 3:
               hudsprite.setPosition(posx+width/12.6,posy+height/2.9);
               menu[0].setPosition(posx+width/12.7,posy+height/2.6);
               menu[1].setPosition(posx+width/12.7,posy+height/2.4);
               menu[2].setPosition(posx+width/12.7,posy+height/2.2);
               break;

       }
    
}*/

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
              hudsprite.setPosition(posx-5*(width/12),posy+height/3);
               menu[0].setPosition(posx-5.5*(width/12),posy+height/2.6);
               menu[1].setPosition(posx-5.5*(width/12),posy+height/2.4);
               menu[2].setPosition(posx-5.5*(width/12),posy+height/2.2);
               break;
           case 1:
               hudsprite.setPosition(posx-2*width/12,posy+height/3);
               menu[0].setPosition(posx-2.5*width/12,posy+height/2.6);
               menu[1].setPosition(posx-2.5*width/12,posy+height/2.4);
               menu[2].setPosition(posx-2.5*width/12,posy+height/2.2);
               break;
             case 2:
               hudsprite.setPosition(posx+1.5*width/12,posy+height/3);
               menu[0].setPosition(posx+width/12,posy+height/2.6);
               menu[1].setPosition(posx+width/12,posy+height/2.4);
               menu[2].setPosition(posx+width/12,posy+height/2.2);
               break;
           case 3:
               hudsprite.setPosition(posx+4.5*(width/12),posy+height/3);
               menu[0].setPosition(posx+4*(width/12),posy+height/2.6);
               menu[1].setPosition(posx+4*(width/12),posy+height/2.4);
               menu[2].setPosition(posx+4*(width/12),posy+height/2.2);
               break;
       }
    
}

void Hud::render(){
    
    for(int i=0; i<players.size(); i++){

        cambiarHud(players[i]);
        hudsprite.draw();
        for(int i=0; i<3; i++){
            sfml->Instance().getWindow()->draw(menu[i]);
        }
    }

}
