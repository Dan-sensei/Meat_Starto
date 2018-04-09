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
    
    renderEngine *sfml;
    
    float width = sfml->Instance().getSize()[0];
    float height = sfml->Instance().getSize()[1];
    
   if (!font.loadFromFile("resources/fuente.ttf"))
    {
            std::cerr << "Error cargando la imagen sprite.png";
            exit(0);	
    }
    
   titulo.setFont(font);
   titulo.setCharacterSize(20);
   titulo.setColor(sf::Color::White);
   titulo.setString("Puntuaciones");
   titulo.setPosition(sf::Vector2f(2*width/5, height/6));
   
   tsalir.setFont(font);
   tsalir.setCharacterSize(20);
   tsalir.setColor(sf::Color::Red);
   tsalir.setString("Exit");
   tsalir.setPosition(sf::Vector2f(150, height/(MAX_NUMBER_OF_ITEMS +1)*4));
}

MPuntuaciones::MPuntuaciones(const MPuntuaciones& orig) {
}

MPuntuaciones::~MPuntuaciones() {
}

void MPuntuaciones::Render(){
    renderEngine *sfml;
    sfml->Instance().clear('w');
    sfml->Instance().getWindow()->draw(titulo);
    sfml->Instance().getWindow()->draw(tsalir);
    sfml->Instance().getWindow()->display();
    
}

void MPuntuaciones::Handle(){
    renderEngine *sfml;

    while (sfml ->Instance().isOpen())
    {
        //Bucle de obtención de eventos
 
        Update();
        Render();       

    }
}

void MPuntuaciones::Update(){
    renderEngine::rEvent event;
    renderEngine *sfml;
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
