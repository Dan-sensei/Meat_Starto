/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MPuntuaciones.cpp
 * Author: alba
 * 
 * Created on 23 de marzo de 2018, 19:25
 */

#include "MPuntuaciones.h"

MPuntuaciones* MPuntuaciones::instance=NULL;
MPuntuaciones* MPuntuaciones::Instance(){
      if(instance == NULL)
          instance = new MPuntuaciones();

    return instance;
}

MPuntuaciones::MPuntuaciones() {
        
    width =  sfml->Instance().getViewSize()[0];
    height = sfml->Instance().getViewSize()[1];
    
    posx = sfml->Instance().getViewCenter()[0];
    posy = sfml->Instance().getViewCenter()[1];
    
    text_fondo.loadFromFile("assets/fondo.PNG");
    
    f1.setTexture(text_fondo);
    f1.setSize(sfml->Instance().getViewSize()[0], sfml->Instance().getViewSize()[1]);
    
    /*MANCHA*/
     std::string sprite_name = "assets/mancha1.png";
    
    int widths = AssetManager::GetTexture(sprite_name).getXSize();
    int heights = AssetManager::GetTexture(sprite_name).getYSize();
    
    mancha.setTexture(AssetManager::GetTexture(sprite_name));
    mancha.setOrigin(widths / 2, heights / 2.1);
    mancha.setScale(1.5, 1.5);
    mancha.setPosition(posx-width/30, posy+height/2.9);

    
     /*PERSONAJE*/
    std::string sprite_name1 = "assets/personaje.png";
    
    int widthp = AssetManager::GetTexture(sprite_name1).getXSize();
    int heightp = AssetManager::GetTexture(sprite_name1).getYSize();
    
    personaje.setTexture(AssetManager::GetTexture(sprite_name1));
    personaje.setOrigin(widthp / 2, heightp / 2.1);
    personaje.setScale(0.15, 0.15);
    personaje.setPosition(posx-width/11.5, posy+height/2.8);

    
  
    font.loadFromFile("resources/fuente.ttf");

    titulo.setFont(font);
    titulo.setCharacterSize(56);
    titulo.setFillColor('k');
    titulo.setString("Score");

    tsalir.setFont(font);
    tsalir.setCharacterSize(50);
    tsalir.setFillColor('w');
    tsalir.setString("Exit");

    titulo.setPosition(posx-width/15, posy-height/2.75);   
    tsalir.setPosition(posx-width/30, posy+height/2.9);
    
   //jugadores
    jugadores= Juego::Instance().getPlayers();
    

    menu= new renderEngine::rText*[MenuInicio::Instance()->numplayers];
    for(int i=0; i<MenuInicio::Instance()->numplayers; i++){
        menu[i]= new renderEngine::rText[5];
    }
    sprite=new renderEngine::rSprite[MenuInicio::Instance()->numplayers];
    
    recuento();
    
    for(int i=0; i<MenuInicio::Instance()->numplayers; i++){
        for(int j=0; j<5; j++){
      //imprime el numero de player
        menu[i][j].setFont(font);
        menu[i][j].setCharacterSize(40);
        menu[i][j].setFillColor('k');

        }
        switch(MenuInicio::Instance()->numplayers){
            case 1:
                sprite[i].setPosition(posx-0.4*width/12,posy-height/7.5);
                menu[i][0].setPosition(posx-0.75*width/12,posy-height/4);
                menu[i][1].setPosition(posx-0.75*width/12,posy);
                menu[i][2].setPosition(posx-0.75*width/12,posy+height/20);
                menu[i][3].setPosition(posx-0.75*width/12,posy+height/10);
                menu[i][4].setPosition(posx-0.75*width/12,posy+height/6.5);
                break;
            case 2: 
                switch(i){
                    case 0:
                          sprite[i].setPosition(posx-1.9*width/12,posy-height/7.5);
                          menu[i][0].setPosition(posx-2.25*width/12,posy-height/4);
                          menu[i][1].setPosition(posx-2.25*width/12,posy);
                          menu[i][2].setPosition(posx-2.25*width/12,posy+height/20);
                          menu[i][3].setPosition(posx-2.25*width/12,posy+height/10);
                          menu[i][4].setPosition(posx-2.25*width/12,posy+height/6.5);
                          break;
                    case 1:
                          sprite[i].setPosition(posx+1.1*width/12,posy-height/7.5);
                          menu[i][0].setPosition(posx+0.75*width/12,posy-height/4);
                          menu[i][1].setPosition(posx+0.75*width/12,posy);
                          menu[i][2].setPosition(posx+0.75*(width/12),posy+height/20);
                          menu[i][3].setPosition(posx+0.75*(width/12),posy+height/10);
                          menu[i][4].setPosition(posx+0.75*width/12,posy+height/6.5);
                          break;
                }
                break;
                
            case 3:
                switch(i){
                 case 0:    
                    sprite[i].setPosition(posx-2.9*width/12,posy-height/7.5);
                    menu[i][0].setPosition(posx-3.25*width/12,posy-height/4);
                    menu[i][1].setPosition(posx-3.25*width/12,posy);
                    menu[i][2].setPosition(posx-3.25*width/12,posy+height/20);
                    menu[i][3].setPosition(posx-3.25*width/12,posy+height/10);
                    menu[i][4].setPosition(posx-3.25*width/12,posy+height/6.5); 
                   break;
                case 1:
                    sprite[i].setPosition(posx-0.4*width/12,posy-height/7.5);
                    menu[i][0].setPosition(posx-0.75*width/12,posy-height/4);
                    menu[i][1].setPosition(posx-0.75*width/12,posy);
                    menu[i][2].setPosition(posx-0.75*width/12,posy+height/20);
                    menu[i][3].setPosition(posx-0.75*width/12,posy+height/10);
                    menu[i][4].setPosition(posx-0.75*width/12,posy+height/6.5);
                    
                    break;
                case 2:
                    sprite[i].setPosition(posx+2.1*width/12,posy-height/7.5);
                    menu[i][0].setPosition(posx+1.75*width/12,posy-height/4);
                    menu[i][1].setPosition(posx+1.75*width/12,posy);
                    menu[i][2].setPosition(posx+1.75*(width/12),posy+height/20);
                    menu[i][3].setPosition(posx+1.75*(width/12),posy+height/10);
                    menu[i][4].setPosition(posx+1.75*width/12,posy+height/6.5);
                    break;
                 }
                break;
            case 4:  
                switch(i){
                 case 0:       
                      sprite[i].setPosition(posx-4.65*(width/12),posy-height/7.5);
                      menu[i][0].setPosition(posx-5*(width/12),posy-height/4);
                      menu[i][1].setPosition(posx-5*(width/12),posy);
                      menu[i][2].setPosition(posx-5*(width/12),posy+height/20);
                      menu[i][3].setPosition(posx-5*(width/12),posy+height/10);
                      menu[i][4].setPosition(posx-5*(width/12),posy+height/6.5);

                      break;
                  case 1:
                      sprite[i].setPosition(posx-1.9*width/12,posy-height/7.5);
                      menu[i][0].setPosition(posx-2.25*width/12,posy-height/4);
                      menu[i][1].setPosition(posx-2.25*width/12,posy);
                      menu[i][2].setPosition(posx-2.25*width/12,posy+height/20);
                      menu[i][3].setPosition(posx-2.25*width/12,posy+height/10);
                      menu[i][4].setPosition(posx-2.25*width/12,posy+height/6.5);
                      break;
                    case 2:
                      sprite[i].setPosition(posx+1.1*width/12,posy-height/7.5);
                      menu[i][0].setPosition(posx+0.75*width/12,posy-height/4);
                      menu[i][1].setPosition(posx+0.75*width/12,posy);
                      menu[i][2].setPosition(posx+0.75*(width/12),posy+height/20);
                      menu[i][3].setPosition(posx+0.75*(width/12),posy+height/10);
                      menu[i][4].setPosition(posx+0.75*width/12,posy+height/6.5);
                      break;
                  case 3:
                      sprite[i].setPosition(posx+4.1*(width/12),posy-height/7.5);
                      menu[i][0].setPosition(posx+3.75*(width/12),posy-height/4);
                      menu[i][1].setPosition(posx+3.75*(width/12),posy);
                      menu[i][2].setPosition(posx+3.75*(width/12),posy+height/20);
                      menu[i][3].setPosition(posx+3.75*(width/12),posy+height/10);
                      menu[i][4].setPosition(posx+3.75*(width/12),posy+height/6.5);

                      break;
              }
            break;

        }
        sprite[i].setScale(3, 3);
    }
    


}

MPuntuaciones::MPuntuaciones(const MPuntuaciones& orig) {
}

MPuntuaciones::~MPuntuaciones() {
}

void MPuntuaciones::Render(){

    renderEngine::Instance().clear('k');
    f1.draw();
    mancha.draw();
    personaje.draw();
    for(int i=0; i<MenuInicio::Instance()->numplayers; i++){
        sprite[i].draw();
        for(int j=0; j<5; j++){
            menu[i][j].draw();
        }
    }
    titulo.draw();
    tsalir.draw();
    renderEngine::Instance().display();
    
}

void MPuntuaciones::recuento(){

    for(int i=0; i<jugadores->size(); i++){
       menu[i][0].setString("Player " + std::to_string(jugadores[0][i]->getId()+1));
       menu[i][1].setString("Level: " + std::to_string(jugadores[0][i]->getLevel()));
       menu[i][2].setString("Exp: " + std::to_string(jugadores[0][i]->getExp()));
       menu[i][3].setString("Deaths: " + std::to_string(jugadores[0][i]->getMuertes()));
       menu[i][4].setString("Kills: " + std::to_string(jugadores[0][i]->getEnemigos()));
       sprite[i]=jugadores[0][i]->getSprite();

     }
}

void MPuntuaciones::Update(){
    renderEngine::rEvent event;
    
    f1.setSize(sfml->Instance().getViewSize()[0], sfml->Instance().getViewSize()[1]);
    f1.setPosition(((sfml->Instance().getViewCenter()[0])-(sfml->Instance().getViewSize()[0])/2), (sfml->Instance().getViewCenter()[1])-(sfml->Instance().getViewSize()[1])/2);

     
       while (sfml->Instance().pollEvent(event))
        {
            
            switch(event.sfType()){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    sfml->Instance().close();
                    break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.getKeyCode()) {
                                                   
                        //Tecla Q para salir
                        case sf::Keyboard::Q:
                            sfml->Instance().close();
                        break;
                        
                         case sf::Keyboard::Escape:
                            sfml->Instance().ChangeState(MenuInicio::Instance());
                            
                            break;
                        
                         case sf::Keyboard::Return:
                            sfml->Instance().ChangeState(MenuInicio::Instance());
                              
                            break;
             
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.getKeyCode() << std::endl;
                        break;
                              
                    }
                     
            }
         
        }  
}

void MPuntuaciones::Handle(){
    
    /*width =  sfml->Instance().getViewSize()[0];
    height = sfml->Instance().getViewSize()[1];
    
    posx = sfml->Instance().getViewCenter()[0];
    posy = sfml->Instance().getViewCenter()[1];
    
    mancha.setPosition(posx-width/30, posy+height/3);
    
    titulo.setPosition(posx-width/15, posy-height/3);   
    tsalir.setPosition(posx-width/30, posy+height/3);*/


    while (sfml ->Instance().isOpen())
    {
        //Bucle de obtención de eventos
 
        Update();
        Render();       

    }
}

