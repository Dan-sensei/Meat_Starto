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
    
    //font.loadFromFile("resources/fuente.ttf");
    font.loadFromFile("assets/fonts/ninjagarden.ttf");
    
        //imprime el nombre del personaje
       menu[0].setFont(font);
       menu[0].setCharacterSize(50);
       menu[0].setFillColor('w');

      //imprime el numero de player
       menu[1].setFont(font);
       menu[1].setCharacterSize(70);
       menu[1].setFillColor('w');

        //imprime el nivel del personaje
       menu[2].setFont(font);
       menu[2].setCharacterSize(40);
       menu[2].setFillColor('k');
       
       
           /*PERSONAJE*/
    std::string sprite_name1 = "assets/cuadrado2.png";
    
    int widthp = AssetManager::GetTexture(sprite_name1).getXSize();
    int heightp = AssetManager::GetTexture(sprite_name1).getYSize();
    
    cuadrado.setTexture(AssetManager::GetTexture(sprite_name1));
    cuadrado.setOrigin(widthp / 4, heightp / 2.4);
    cuadrado.setScale(0.7, 0.5);

    renderEngine::rSprite aux;
    float scale = 1.7f;
    
    aux.setTexture(AssetManager::GetTexture("assets/RED_HUD.png"));
    aux.setScale(scale, scale);
    NEWHUD.push_back(aux);
    
    aux.setTexture(AssetManager::GetTexture("assets/YELLOW_HUD.png"));
    aux.setScale(scale, scale);
    NEWHUD.push_back(aux);
    
    aux.setTexture(AssetManager::GetTexture("assets/GREEN_HUD.png"));
    aux.setScale(scale, scale);
    NEWHUD.push_back(aux);
    
    aux.setTexture(AssetManager::GetTexture("assets/PURPLE_HUD.png"));
    aux.setScale(scale, scale);
    NEWHUD.push_back(aux);
    
       
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
    
    menu[0].setString(player->getName());
    menu[1].setString(std::to_string(player->getLevel()));
    menu[2].setString("Exp: " + std::to_string(player->getExp()) +"/"+ std::to_string(player->getExp_levelup()));
    hudsprite=player->getSprite();


    //cambia la posicion segun el player             
    switch(player->getId()){

        case 0:       
            NEWHUD[0].setPosition(posx-5.5*(width/12) -20, posy-height/2.2);
            hudsprite.setPosition(posx-5*(width/12) + 230 , posy-height/2.2 + 75);
            menu[0].setPosition(posx-5.5*(width/12) + 130 ,posy-height/2.4 -30 );
            menu[1].setPosition(posx-5.5*(width/12) + 40 ,posy-height/2.6 -65);
            menu[2].setPosition(posx-5.5*(width/12) + 180 ,posy-height/2.8 -85);
            //cuadrado.setPosition(posx-5.5*(width/12),posy-height/2.4);

            break;
         case 1:
            NEWHUD[1].setPosition(posx-2.5*width/12 -20,posy-height/2.2);
            hudsprite.setPosition(posx-2*width/12 + 230, posy-height/2.2 +75);
            menu[0].setPosition(posx-2.5*width/12 + 130, posy-height/2.4 -30);
            menu[1].setPosition(posx-2.5*width/12 + 40, posy-height/2.6 -65);
            menu[2].setPosition(posx-2.5*width/12 + 180, posy-height/2.8 -85);
            //cuadrado.setPosition(posx-2.5*(width/12),posy-height/2.4);

            break;
        case 2:
            NEWHUD[2].setPosition(posx+1*width/12 -20,posy-height/2.2);
            hudsprite.setPosition(posx+1.5*width/12 + 230 , posy-height/2.2 +75);
            menu[0].setPosition(posx+width/12 + 130 , posy-height/2.4 -30);
            menu[1].setPosition(posx+width/12 + 40 , posy-height/2.6 -65);
            menu[2].setPosition(posx+width/12 + 180 , posy-height/2.8 -85);
            //cuadrado.setPosition(posx+(width/12),posy-height/2.4);
            break;
        case 3:
            NEWHUD[3].setPosition(posx+4*(width/12) -20 ,posy-height/2.2);
            hudsprite.setPosition(posx+4.5*(width/12) + 230 , posy-height/2.2 +75);
            menu[0].setPosition(posx+4*(width/12) + 130 , posy-height/2.4 -30);
            menu[1].setPosition(posx+4*(width/12) + 40 , posy-height/2.6 -65);
            menu[2].setPosition(posx+4*(width/12) +180 , posy-height/2.8 -85);
            //cuadrado.setPosition(posx+4*(width/12),posy-height/2.4);

            break;
   }
    
}

void Hud::render(){

    for(int i=0; i<players.size(); i++){
        cambiarHud(players[i]);
        NEWHUD[i].draw();
        //cuadrado.draw();
        hudsprite.draw();
        for(int i=0; i<3; i++){
            menu[i].draw();
        }
    }

}
