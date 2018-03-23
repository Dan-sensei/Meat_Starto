/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Juego.cpp
 * Author: alba
 * 
 * Created on 15 de marzo de 2018, 22:20
 */

#include "Juego.h"

Juego* Juego::instance=NULL;
Juego* Juego::Instance(){
      if(instance == NULL)
          instance = new Juego();

    return instance;
}


Juego::Juego() {
    
    window=Motor::Instance()->window;
    
    float width =  window->getSize().x;
    float height = window->getSize().y;
  
   if (!font.loadFromFile("resources/fuente.ttf"))
    {
            std::cerr << "Error cargando la imagen sprite.png";
            exit(0);	
    }
    
   titulo.setFont(font);
   titulo.setCharacterSize(20);
   titulo.setColor(sf::Color::White);
   titulo.setString("Juego");
   titulo.setPosition(sf::Vector2f(2*width/5, height/6));
   
   titulo2.setFont(font);
   titulo2.setCharacterSize(20);
   titulo2.setColor(sf::Color::White);
   titulo2.setString("pulsa Esc para pausa");
   titulo2.setPosition(sf::Vector2f(width/4, height/4));
   
   titulo3.setFont(font);
   titulo3.setCharacterSize(20);
   titulo3.setColor(sf::Color::White);
   titulo3.setString("pulsa P para ir al estado de puntuaciones");
   titulo3.setPosition(sf::Vector2f(width/8, height/3));
}

Juego::Juego(const Juego& orig) {
}

Juego::~Juego() {
}

void Juego::Render(){
    
    window->clear();
      
    window->draw(titulo);
    window->draw(titulo2);
    window->draw(titulo3);

    window->display();
    
}

void Juego::Handle(Motor* pMotor){
    pgame=pMotor;

    while (window->isOpen())
    {
        //Bucle de obtención de eventos
        sf::Event event;   
 
        Update(event);
        Render();       

    }
}

void Juego::Update(sf::Event event){
       while (window->pollEvent(event))
        {
            
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window->close();
                    break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                                                   
                        //Tecla Q para salir
                        case sf::Keyboard::Q:
                            window->close();
                        break;
                        
                         case sf::Keyboard::Escape:
                            pgame->ChangeState(MenuPausa::Instance());    
                            break;
                        
                        case sf::Keyboard::P:
                             pgame->ChangeState(MPuntuaciones::Instance());    
                             break;

             
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                        break;
                              
                    }
                     
            }
         
        }  
}
