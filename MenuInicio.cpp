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
    
    width =  sfml->Instance().getViewSize()[0];
    height = sfml->Instance().getViewSize()[1];
    
    posx = sfml->Instance().getViewCenter()[0];
    posy = sfml->Instance().getViewCenter()[1];
  
    numplayers=1;
    
    text_fondo.loadFromFile("assets/fondo.PNG");
    
    f1.setTexture(text_fondo);
    f1.setSize(sfml->Instance().getViewSize()[0], sfml->Instance().getViewSize()[1]);
  
   if (!font.loadFromFile("resources/fuente.ttf"))
    {
            std::cerr << "Error cargando la imagen sprite.png";
            exit(0);	
    }
    
   titulo.setFont(font);
   titulo.setCharacterSize(18);
   titulo.setFillColor(sf::Color::Black);
   titulo.setString("Meat Starto!");
   titulo.setPosition(sf::Vector2f(posx-width/30, posy-height/3));
  
   
   menu[0].setFont(font);
   menu[0].setCharacterSize(16);
   menu[0].setFillColor(sf::Color::Red);
   menu[0].setString("Play");
   menu[0].setPosition(posx-width/3, posy-height/5);
   
   menu[1].setFont(font);
   menu[1].setCharacterSize(16);
   menu[1].setFillColor(sf::Color::Black);
   menu[1].setString("Options");
   menu[1].setPosition(posx-width/3, posy-height/10);
   
   menu[2].setFont(font);
   menu[2].setCharacterSize(16);
   menu[2].setFillColor(sf::Color::Black);
   menu[2].setString("How to play");
   menu[2].setPosition(posx-width/3, posy+height/10);
   
   menu[3].setFont(font);
   menu[3].setCharacterSize(16);
   menu[3].setFillColor(sf::Color::Black);
   menu[3].setString("Exit");
   menu[3].setPosition(posx-width/3, posy+height/5);
   
   
   /*MENU DE OPCIONES*/
   titulo2.setFont(font);
   titulo2.setCharacterSize(18);
   titulo2.setFillColor(sf::Color::Black);
   titulo2.setString("Options");
   titulo2.setPosition(posx-width/30, posy-height/3);
   
   menuop[0].setFont(font);
   menuop[0].setCharacterSize(16);
   menuop[0].setFillColor(sf::Color::Red);
   menuop[0].setString("Sound");
   menuop[0].setPosition(posx-width/3, posy-height/6);
   
   menuop[1].setFont(font);
   menuop[1].setCharacterSize(16);
   menuop[1].setFillColor(sf::Color::Black);
   menuop[1].setString("Exit");
   menuop[1].setPosition(posx-width/3, posy+height/10);
   
   
   /*Menu players*/
   titulo3.setFont(font);
   titulo3.setCharacterSize(18);
   titulo3.setFillColor(sf::Color::Black);
   titulo3.setString("Players");
   titulo3.setPosition(posx-width/30, posy-height/3);
   
   menuplayer[0].setFont(font);
   menuplayer[0].setCharacterSize(16);
   menuplayer[0].setFillColor(sf::Color::Red);
   menuplayer[0].setString("Play" );
   menuplayer[0].setPosition(posx-width/3, posy-height/6);
   
   menuplayer[1].setFont(font);
   menuplayer[1].setCharacterSize(16);
   menuplayer[1].setFillColor(sf::Color::Black);
   menuplayer[1].setString("Players "  + std::to_string(numplayers));
   menuplayer[1].setPosition(posx-width/3, posy+height/10);
   
   menuplayer[2].setFont(font);
   menuplayer[2].setCharacterSize(16);
   menuplayer[2].setFillColor(sf::Color::Black);
   menuplayer[2].setString("Exit");
   menuplayer[2].setPosition(posx-width/3, posy+height/8);
   
   
   /*How to play*/
   titulo4.setFont(font);
   titulo4.setCharacterSize(18);
   titulo4.setFillColor(sf::Color::Black);
   titulo4.setString("How to play");
   titulo4.setPosition(posx-width/30, posy-height/3);
   
   menuhow.setFont(font);
   menuhow.setCharacterSize(16);
   menuhow.setFillColor(sf::Color::Red);
   menuhow.setString("Exit");
   menuhow.setPosition(posx-width/3, posy-height/6);
   
   
   
   selectedItemIndex=0;
   selectedItemIndex2=0;
   selectedItemIndex3=0;
   selectedItemIndex4=3;
   statemenu=0;
   
   primero=true;
   

}

MenuInicio::MenuInicio(const MenuInicio& orig) {
}

MenuInicio::~MenuInicio() {
}

void MenuInicio::Render(){
    
    sfml->Instance().clear('k'); 
        f1.draw();
        
    switch(statemenu){
        case 0:   
            sfml->Instance().getWindow()->draw(titulo);
            for(int i=0; i<MAX_NUMBER_OF_ITEMS;i++){
                sfml->Instance().getWindow()->draw(menu[i]);
            }
            break;
        case 1:   
            sfml->Instance().getWindow()->draw(titulo2);
            for(int i=0; i<MAX_NUMBER_OF_ITEMS2;i++){
                sfml->Instance().getWindow()->draw(menuop[i]);
            }
            break;  
        case 2:
            sfml->Instance().getWindow()->draw(titulo3);
            for(int i=0; i<MAX_NUMBER_OF_ITEMS3;i++){
                sfml->Instance().getWindow()->draw(menuplayer[i]);
            }
            break;
        case 3:
            sfml->Instance().getWindow()->draw(titulo4);
            sfml->Instance().getWindow()->draw(menuhow);
            break;
            
    }
    sfml->Instance().getWindow()->display();     

    
}

void MenuInicio::MoveUp(){
    switch(statemenu){
        case 0:
            if(selectedItemIndex-1>=0){
                menu[selectedItemIndex].setFillColor(sf::Color::Black);
                selectedItemIndex--;
                menu[selectedItemIndex].setFillColor(sf::Color::Red);
            }
            break;
        case 1:
            if(selectedItemIndex2-1>=0){
                menuop[selectedItemIndex2].setFillColor(sf::Color::Black);
                selectedItemIndex2--;
                menuop[selectedItemIndex2].setFillColor(sf::Color::Red);
            }
            break;
        case 2:
            if(selectedItemIndex3-1>=0){
                menuplayer[selectedItemIndex3].setFillColor(sf::Color::Black);
                selectedItemIndex3--;
                menuplayer[selectedItemIndex3].setFillColor(sf::Color::Red);
            }
            break;
            
    }
    
}

void MenuInicio::MoveDown(){
    switch(statemenu){
        case 0:
            if(selectedItemIndex+1<MAX_NUMBER_OF_ITEMS){
                menu[selectedItemIndex].setFillColor(sf::Color::Black);
                selectedItemIndex++;
                menu[selectedItemIndex].setFillColor(sf::Color::Red);
            }
            break;
        case 1:
            if(selectedItemIndex2+1<MAX_NUMBER_OF_ITEMS2){
                menuop[selectedItemIndex2].setFillColor(sf::Color::Black);
                selectedItemIndex2++;
                menuop[selectedItemIndex2].setFillColor(sf::Color::Red);
            }
            break;
        case 2:
            if(selectedItemIndex3+1<MAX_NUMBER_OF_ITEMS3){
                menuplayer[selectedItemIndex3].setFillColor(sf::Color::Black);
                selectedItemIndex3++;
                menuplayer[selectedItemIndex3].setFillColor(sf::Color::Red);
            }
            break;
    }
}

void MenuInicio::Update(){
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
                            switch(statemenu){
                                case 0:
                                    switch(selectedItemIndex){
                                        case 0:
                                            statemenu=2;
                                           // std::cout<<"Play pressed"<< std::endl;
                                            break;

                                        case 1:
                                            statemenu=1;
                                          //  std::cout<<"Option pressed"<< std::endl;
                                            break;

                                        case 2:
                                            statemenu=3;
                                         //   std::cout<<"how to play pressed"<< std::endl;
                                            break;

                                        case 3:
                                         //   std::cout<<"Exit pressed"<< std::endl;
                                            sfml->Instance().close();
                                            break;                                            

                                    }
                                    break;
                                    
                                case 1:
                                    switch(selectedItemIndex2){
                                        case 0:
                                           // std::cout<<"Sound pressed"<< std::endl;
                                            break;

                                        case 1:
                                            statemenu=0;
                                          //  std::cout<<"Exit pressed"<< std::endl;

                                            break;
                                    }
                                    break;
                                case 2:
                                    switch(selectedItemIndex3){
                                       
                                        case 0:
                                            //cambiar estado a Motor
                                            statemenu=2;
                                            sfml->Instance().ChangeState(&Juego::Instance());
                                          //  std::cout<<"Play pressed"<< std::endl;
                                            break;
                                            
                                        case 1:
                                            sfml->Instance().ChangeState(&Juego::Instance());
                                          //  std::cout<<"Players pressed"<< std::endl;
                                            break;

                                        case 2:
                                            statemenu=0;
                                          // std::cout<<"Exit pressed"<< std::endl;

                                            break;
                                    }
                                    break;
                                case 3:
                                    statemenu=0;
                                 //   std::cout<<"Exit pressed"<< std::endl;
                                    break;
                                    
                            }         
                       
                            break;
                         case sf::Keyboard::Right:
                            if(statemenu==2 && numplayers<4 && menuplayer[1].getFillColor()==sf::Color::Red){
                                numplayers++;
                                menuplayer[1].setString("Players "  + std::to_string(numplayers));
                            }
                            break;
                            
                        case sf::Keyboard::Left:
                            if(statemenu==2 && numplayers>1 && menuplayer[1].getFillColor()==sf::Color::Red){
                                numplayers--;
                                menuplayer[1].setString("Players "  + std::to_string(numplayers));
                            }
                            
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.getKeyCode() << std::endl;
                        break;
                              
                    }
                     
            }
         
        }  
}

void MenuInicio::Handle(){
    statemenu=0;
    
    if(primero==false){
           titulo.setCharacterSize(56);
            menu[0].setCharacterSize(50);
            menu[1].setCharacterSize(50);
            menu[2].setCharacterSize(50);
            menu[3].setCharacterSize(50);


            /*MENU DE OPCIONES*/
            titulo2.setCharacterSize(56);
            menuop[0].setCharacterSize(50);
            menuop[1].setCharacterSize(50);


            /*Menu players*/
            titulo3.setCharacterSize(56);
            menuplayer[0].setCharacterSize(50);
            menuplayer[1].setCharacterSize(50);
            menuplayer[2].setCharacterSize(50);


            /*How to play*/
            titulo4.setCharacterSize(56);
            menuhow.setCharacterSize(50);
            
    }
    
    
    
    width =  sfml->Instance().getViewSize()[0];
    height = sfml->Instance().getViewSize()[1];
    
    posx = sfml->Instance().getViewCenter()[0];
    posy = sfml->Instance().getViewCenter()[1];
    
   titulo.setPosition(sf::Vector2f(posx-width/20, posy-height/3));    
   menu[0].setPosition(posx-width/3, posy-height/5);
   menu[1].setPosition(posx-width/3, posy-height/15);
   menu[2].setPosition(posx-width/3, posy+height/15);
   menu[3].setPosition(posx-width/3, posy+height/5);
   
   
   /*MENU DE OPCIONES*/
   titulo2.setPosition(posx-width/30, posy-height/3);
   menuop[0].setPosition(posx-width/3, posy);
   menuop[1].setPosition(posx-width/3, posy+height/5);
   
   
   /*Menu players*/
   titulo3.setPosition(posx-width/30, posy-height/3);
   menuplayer[0].setPosition(posx-width/3, posy-height/5);
   menuplayer[1].setPosition(posx-width/3, posy);
   menuplayer[2].setPosition(posx-width/3, posy+height/5);
   
   
   /*How to play*/
   titulo4.setPosition(posx-width/30, posy-height/3);
   menuhow.setPosition(posx-width/3, posy-height/6);
   
    primero=false;
    
    while (sfml->Instance().isOpen())
    {
        //Bucle de obtención de eventos
        Update();
        Render();       

    }
}
