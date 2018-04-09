/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MenuPausa.cpp
 * Author: alba
 * 
 * Created on 15 de marzo de 2018, 21:30
 */

#include "MenuPausa.h"

//Patron Singleton
MenuPausa* MenuPausa::instance=NULL;
MenuPausa* MenuPausa::Instance(){
      if(instance == NULL)
          instance = new MenuPausa();

    return instance;
}


MenuPausa::MenuPausa() {
    
    renderEngine *sfml;
    
    float width =  sfml->Instance().getSize()[0];
    float height = sfml->Instance().getSize()[1];
  
   if (!font.loadFromFile("resources/fuente.ttf"))
    {
            std::cerr << "Error cargando la imagen sprite.png";
            exit(0);	
    }
    
   titulo.setFont(font);
   titulo.setCharacterSize(20);
   titulo.setColor(sf::Color::White);
   titulo.setString("Pause");
   titulo.setPosition(sf::Vector2f(2*width/5, height/(NUMBER_OF_ITEMS +6)));
  
   
   menu[0].setFont(font);
   menu[0].setCharacterSize(20);
   menu[0].setColor(sf::Color::Red);
   menu[0].setString("Continue");
   menu[0].setPosition(sf::Vector2f(150, height/(NUMBER_OF_ITEMS +1)*1));
   
   menu[1].setFont(font);
   menu[1].setCharacterSize(20);
   menu[1].setColor(sf::Color::White);
   menu[1].setString("Exit");
   menu[1].setPosition(sf::Vector2f(150, height/(NUMBER_OF_ITEMS +1)*2));
   
   selectedItemIndex=0;
}

MenuPausa::MenuPausa(const MenuPausa& orig) {
}

MenuPausa::~MenuPausa() {
}

void MenuPausa::Render(){
    
    renderEngine *sfml;
    sfml->Instance().clear('w');  
    
    sfml->Instance().getWindow()->draw(titulo);
    for(int i=0; i<NUMBER_OF_ITEMS;i++){
        sfml->Instance().getWindow()->draw(menu[i]);
    }

     sfml->Instance().display();
    
}

void MenuPausa::MoveUp(){
    if(selectedItemIndex-1>=0){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    } 
}

void MenuPausa::MoveDown(){
    if(selectedItemIndex+1<NUMBER_OF_ITEMS){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}

void MenuPausa::Update(){
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
                                                   
                        case sf::Keyboard::Up:   
                            MoveUp();
                            break;
                            
                        case sf::Keyboard::Down: 
                            MoveDown();
                            break;

                        //Tecla Q para salir
                        case sf::Keyboard::Q:
                            sfml->Instance().close();
                        break;
                        
                        case sf::Keyboard::Return:

                            switch(selectedItemIndex){
                                case 0:
                                    sfml->Instance().ChangeState(Juego::Instance());
                                    std::cout<<"Continue pressed"<< std::endl;
                                    break;

                                case 1:
                                    sfml->Instance().ChangeState(MenuInicio::Instance());
                                    std::cout<<"Exit pressed"<< std::endl;
                                    break;
                            }
 
                       
                            break;
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.getKeyCode() << std::endl;
                        break;
                              
                    }
                     
            }
         
        }  
}

void MenuPausa::Handle(){
    renderEngine *sfml;

    while (sfml->Instance().isOpen())
    {
        //Bucle de obtención de eventos
 
        Update();
        Render();       

    }
}

