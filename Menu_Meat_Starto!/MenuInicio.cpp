/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MenuInicio.cpp
 * Author: alba
 * 
 * Created on 22 de marzo de 2018, 20:38
 */

#include "MenuInicio.h"

//Patron Singleton
MenuInicio* MenuInicio::instance=NULL;
MenuInicio* MenuInicio::Instance(){
      if(instance == NULL)
          instance = new MenuInicio();

    return instance;
}

MenuInicio::MenuInicio() {

    window=Motor::Instance()->window;
    
    float width =  window->getSize().x;
    float height = window->getSize().y;
    numplayers=1;
  
   if (!font.loadFromFile("resources/fuente.ttf"))
    {
            std::cerr << "Error cargando la imagen sprite.png";
            exit(0);	
    }
    
   titulo.setFont(font);
   titulo.setCharacterSize(20);
   titulo.setColor(sf::Color::White);
   titulo.setString("Meat Starto!");
   titulo.setPosition(sf::Vector2f(2*width/5, height/(MAX_NUMBER_OF_ITEMS +6)));
  
   
   menu[0].setFont(font);
   menu[0].setCharacterSize(20);
   menu[0].setColor(sf::Color::Red);
   menu[0].setString("Play");
   menu[0].setPosition(sf::Vector2f(150, height/(MAX_NUMBER_OF_ITEMS +1)*1));
   
   menu[1].setFont(font);
   menu[1].setCharacterSize(20);
   menu[1].setColor(sf::Color::White);
   menu[1].setString("Options");
   menu[1].setPosition(sf::Vector2f(150, height/(MAX_NUMBER_OF_ITEMS +1)*2));
   
   menu[2].setFont(font);
   menu[2].setCharacterSize(20);
   menu[2].setColor(sf::Color::White);
   menu[2].setString("How to play");
   menu[2].setPosition(sf::Vector2f(150, height/(MAX_NUMBER_OF_ITEMS +1)*3));
   
   menu[3].setFont(font);
   menu[3].setCharacterSize(20);
   menu[3].setColor(sf::Color::White);
   menu[3].setString("Exit");
   menu[3].setPosition(sf::Vector2f(150, height/(MAX_NUMBER_OF_ITEMS +1)*4));
   
   
   /*MENU DE OPCIONES*/
   titulo2.setFont(font);
   titulo2.setCharacterSize(20);
   titulo2.setColor(sf::Color::White);
   titulo2.setString("Options");
   titulo2.setPosition(sf::Vector2f(2*width/5, height/(MAX_NUMBER_OF_ITEMS +5)));
   
   menuop[0].setFont(font);
   menuop[0].setCharacterSize(20);
   menuop[0].setColor(sf::Color::Red);
   menuop[0].setString("Sound");
   menuop[0].setPosition(sf::Vector2f(150, height/(MAX_NUMBER_OF_ITEMS2 +1)*1));
   
   menuop[1].setFont(font);
   menuop[1].setCharacterSize(20);
   menuop[1].setColor(sf::Color::White);
   menuop[1].setString("Exit");
   menuop[1].setPosition(sf::Vector2f(150, height/(MAX_NUMBER_OF_ITEMS2 +1)*2));
   
   
   /*Menu players*/
   titulo3.setFont(font);
   titulo3.setCharacterSize(20);
   titulo3.setColor(sf::Color::White);
   titulo3.setString("Players");
   titulo3.setPosition(sf::Vector2f(2*width/5, height/(MAX_NUMBER_OF_ITEMS3 +5)));
   
   menuplayer[0].setFont(font);
   menuplayer[0].setCharacterSize(20);
   menuplayer[0].setColor(sf::Color::Red);
   menuplayer[0].setString("Play" );
   menuplayer[0].setPosition(sf::Vector2f(150, height/(MAX_NUMBER_OF_ITEMS3 +1)*1));
   
   menuplayer[1].setFont(font);
   menuplayer[1].setCharacterSize(20);
   menuplayer[1].setColor(sf::Color::White);
   menuplayer[1].setString("Players "  + std::to_string(numplayers));
   menuplayer[1].setPosition(sf::Vector2f(150, height/(MAX_NUMBER_OF_ITEMS3 +1)*2));
   
   menuplayer[2].setFont(font);
   menuplayer[2].setCharacterSize(20);
   menuplayer[2].setColor(sf::Color::White);
   menuplayer[2].setString("Exit");
   menuplayer[2].setPosition(sf::Vector2f(150, height/(MAX_NUMBER_OF_ITEMS3 +1)*3));
   
   
   /*How to play*/
   titulo4.setFont(font);
   titulo4.setCharacterSize(20);
   titulo4.setColor(sf::Color::White);
   titulo4.setString("How to play");
   titulo4.setPosition(sf::Vector2f(2*width/5, height/(MAX_NUMBER_OF_ITEMS +5)));
   
   menuhow.setFont(font);
   menuhow.setCharacterSize(20);
   menuhow.setColor(sf::Color::Red);
   menuhow.setString("Exit");
   menuhow.setPosition(sf::Vector2f(150, height/(MAX_NUMBER_OF_ITEMS +1)*4));
   
   
   
   selectedItemIndex=0;
   selectedItemIndex2=0;
   selectedItemIndex3=0;
   selectedItemIndex4=3;
   statemenu=0;
}

MenuInicio::MenuInicio(const MenuInicio& orig) {
}

MenuInicio::~MenuInicio() {
}

void MenuInicio::Render(){
    
    window->clear();
    
    switch(statemenu){
        case 0:   
            window->draw(titulo);
            for(int i=0; i<MAX_NUMBER_OF_ITEMS;i++){
                window->draw(menu[i]);
            }
            break;
        case 1:   
            window->draw(titulo2);
            for(int i=0; i<MAX_NUMBER_OF_ITEMS2;i++){
                window->draw(menuop[i]);
            }
            break;  
        case 2:
            window->draw(titulo3);
            for(int i=0; i<MAX_NUMBER_OF_ITEMS3;i++){
                window->draw(menuplayer[i]);
            }
            break;
        case 3:
            window->draw(titulo4);
            window->draw(menuhow);
            break;
            
    }
     window->display();
    
}

void MenuInicio::MoveUp(){
    switch(statemenu){
        case 0:
            if(selectedItemIndex-1>=0){
                menu[selectedItemIndex].setColor(sf::Color::White);
                selectedItemIndex--;
                menu[selectedItemIndex].setColor(sf::Color::Red);
            }
            break;
        case 1:
            if(selectedItemIndex2-1>=0){
                menuop[selectedItemIndex2].setColor(sf::Color::White);
                selectedItemIndex2--;
                menuop[selectedItemIndex2].setColor(sf::Color::Red);
            }
            break;
        case 2:
            if(selectedItemIndex3-1>=0){
                menuplayer[selectedItemIndex3].setColor(sf::Color::White);
                selectedItemIndex3--;
                menuplayer[selectedItemIndex3].setColor(sf::Color::Red);
            }
            break;
            
    }
    
}

void MenuInicio::MoveDown(){
    switch(statemenu){
        case 0:
            if(selectedItemIndex+1<MAX_NUMBER_OF_ITEMS){
                menu[selectedItemIndex].setColor(sf::Color::White);
                selectedItemIndex++;
                menu[selectedItemIndex].setColor(sf::Color::Red);
            }
            break;
        case 1:
            if(selectedItemIndex2+1<MAX_NUMBER_OF_ITEMS2){
                menuop[selectedItemIndex2].setColor(sf::Color::White);
                selectedItemIndex2++;
                menuop[selectedItemIndex2].setColor(sf::Color::Red);
            }
            break;
        case 2:
            if(selectedItemIndex3+1<MAX_NUMBER_OF_ITEMS3){
                menuplayer[selectedItemIndex3].setColor(sf::Color::White);
                selectedItemIndex3++;
                menuplayer[selectedItemIndex3].setColor(sf::Color::Red);
            }
            break;
    }
}

void MenuInicio::Update(sf::Event event){
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
                                                   
                        case sf::Keyboard::Up:   
                            MoveUp();
                            break;
                            
                        case sf::Keyboard::Down: 
                            MoveDown();
                            break;

                        //Tecla Q para salir
                        case sf::Keyboard::Q:
                            window->close();
                        break;
                        
                        case sf::Keyboard::Return:
                            switch(statemenu){
                                case 0:
                                    switch(selectedItemIndex){
                                        case 0:
                                            statemenu=2;
                                            std::cout<<"Play pressed"<< std::endl;
                                            break;

                                        case 1:
                                            statemenu=1;
                                            std::cout<<"Option pressed"<< std::endl;
                                            break;

                                        case 2:
                                            statemenu=3;
                                            std::cout<<"how to play pressed"<< std::endl;
                                            break;

                                        case 3:
                                            std::cout<<"Exit pressed"<< std::endl;
                                            window->close();
                                            break;                                            

                                    }
                                    break;
                                    
                                case 1:
                                    switch(selectedItemIndex2){
                                        case 0:
                                            std::cout<<"Sound pressed"<< std::endl;
                                            break;

                                        case 1:
                                            statemenu=0;
                                            std::cout<<"Exit pressed"<< std::endl;

                                            break;
                                    }
                                    break;
                                case 2:
                                    switch(selectedItemIndex3){
                                       
                                        case 0:
                                            //cambiar estado a Motor
                                            statemenu=2;
                                            pgame->ChangeState(Juego::Instance());
                                            std::cout<<"Play pressed"<< std::endl;
                                            break;
                                            
                                        case 1:
                                            std::cout<<"Players pressed"<< std::endl;
                                            break;

                                        case 2:
                                            statemenu=0;
                                            std::cout<<"Exit pressed"<< std::endl;

                                            break;
                                    }
                                    break;
                                case 3:
                                    statemenu=0;
                                    std::cout<<"Exit pressed"<< std::endl;
                                    break;
                                    
                            }         
                       
                            break;
                         case sf::Keyboard::Right:
                            if(statemenu==2 && numplayers<4 && menuplayer[1].getColor()==sf::Color::Red){
                                numplayers++;
                                menuplayer[1].setString("Players "  + std::to_string(numplayers));
                            }
                            break;
                            
                        case sf::Keyboard::Left:
                            if(statemenu==2 && numplayers>1 && menuplayer[1].getColor()==sf::Color::Red){
                                numplayers--;
                                menuplayer[1].setString("Players "  + std::to_string(numplayers));
                            }
                            
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                        break;
                              
                    }
                     
            }
         
        }  
}

void MenuInicio::Handle(Motor* pMotor){
      pgame=pMotor;                                
    
    while (window->isOpen())
    {
        //Bucle de obtención de eventos
        sf::Event event;   
 
        Update(event);
        Render();       

    }
}
