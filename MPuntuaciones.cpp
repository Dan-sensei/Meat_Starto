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
  
   if (!font.loadFromFile("resources/fuente.ttf"))
    {
            std::cerr << "Error cargando la imagen sprite.png";
            exit(0);	
    }
    
   titulo.setFont(font);
   titulo.setCharacterSize(56);
   titulo.setFillColor(sf::Color::Black);
   titulo.setString("Puntuaciones");
   titulo.setPosition(posx-width/30, posy-height/3);   
   
   tsalir.setFont(font);
   tsalir.setCharacterSize(50);
   tsalir.setFillColor(sf::Color::Red);
   tsalir.setString("Exit");
   tsalir.setPosition(posx-width/3, posy+height/5);

}

MPuntuaciones::MPuntuaciones(const MPuntuaciones& orig) {
}

MPuntuaciones::~MPuntuaciones() {
}

void MPuntuaciones::Render(){

    sfml->Instance().clear('k');
    f1.draw();
    sfml->Instance().getWindow()->draw(titulo);
    sfml->Instance().getWindow()->draw(tsalir);
    sfml->Instance().getWindow()->display();
    
}

void MPuntuaciones::Handle(){
    
    width =  sfml->Instance().getViewSize()[0];
    height = sfml->Instance().getViewSize()[1];
    
    posx = sfml->Instance().getViewCenter()[0];
    posy = sfml->Instance().getViewCenter()[1];
    
    titulo.setPosition(posx-width/15, posy-height/3);   
    tsalir.setPosition(posx-width/3, posy+height/5);


    while (sfml ->Instance().isOpen())
    {
        //Bucle de obtención de eventos
 
        Update();
        Render();       

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
