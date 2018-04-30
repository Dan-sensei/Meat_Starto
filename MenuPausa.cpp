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
        
    width =  sfml->Instance().getViewSize()[0];
    height = sfml->Instance().getViewSize()[1];
    
    posx = sfml->Instance().getViewCenter()[0];
    posy = sfml->Instance().getViewCenter()[1];

    text_fondo.loadFromFile("assets/fondo.PNG");
    
    f1.setTexture(text_fondo);
    f1.setSize(sfml->Instance().getViewSize()[0], sfml->Instance().getViewSize()[1]);
    
    /*PERSONAJE*/
    std::string sprite_name1 = "assets/personaje.png";
    
    int widthp = AssetManager::GetTexture(sprite_name1).getXSize();
    int heightp = AssetManager::GetTexture(sprite_name1).getYSize();
    
    personaje.setTexture(AssetManager::GetTexture(sprite_name1));
    personaje.setOrigin(widthp / 2, heightp / 2.1);
    personaje.setScale(0.15, 0.15);
    personaje.setPosition(posx-width/11, posy-height/21);

    
    
    /*MANCHAS DEL MENU*/
    std::string sprite_name = "assets/mancha1.png";
    
    int widths = AssetManager::GetTexture(sprite_name).getXSize();
    int heights = AssetManager::GetTexture(sprite_name).getYSize();
    
    for(int i=0; i<NUMBER_OF_ITEMS; i++){
        mancha[i].setTexture(AssetManager::GetTexture(sprite_name));
        mancha[i].setOrigin(widths / 2, heights / 2.1);
        mancha[i].setScale(1.65, 1.65);
    }
    
    InmortalOn=false;
  
  
   if (!font.loadFromFile("resources/fuente.ttf"))
    {
            std::cerr << "Error cargando la imagen sprite.png";
            exit(0);	
    }
    
   titulo.setFont(font);
   titulo.setCharacterSize(56);
   titulo.setFillColor(sf::Color::Black);
   titulo.setString("Pause");  
  
   
   menu[0].setFont(font);
   menu[0].setCharacterSize(48);
   menu[0].setFillColor(sf::Color::White);
   menu[0].setString("Continue");
   
   menu[1].setFont(font);
   menu[1].setCharacterSize(48);
   menu[1].setFillColor(sf::Color::Black);
   menu[1].setString("Controles");
   
   menu[2].setFont(font);
   menu[2].setCharacterSize(48);
   menu[2].setFillColor(sf::Color::Black);
   menu[2].setString("Exit");
   
   /*MENU DE OPCIONES*/
   titulo2.setFont(font);
   titulo2.setCharacterSize(56);
   titulo2.setFillColor(sf::Color::Black);
   titulo2.setString("Controles");
   
   menuhow.setFont(font);
   menuhow.setCharacterSize(48);
   menuhow.setFillColor(sf::Color::White);
   menuhow.setString("Exit");
   menuhow.setPosition(posx-width/3, posy-height/6);
   
    /*Imagen Controles*/
    std::string sprite_namec = "assets/controles.png";
    
    int widthc = AssetManager::GetTexture(sprite_namec).getXSize();
    int heightc = AssetManager::GetTexture(sprite_namec).getYSize();
    
    controles.setTexture(AssetManager::GetTexture(sprite_namec));
    controles.setOrigin(widthc / 2, heightc / 2);
    controles.setScale(1.65,1.65);
    controles.setPosition(posx, posy+height/3);
   
    manchahtp.setTexture(AssetManager::GetTexture(sprite_name));
    manchahtp.setOrigin(widths / 2, heights / 2.1);
    manchahtp.setScale(1.65, 1.65);
   
   selectedItemIndex=0;
   selectedItemIndex2=0;
   statemenu=0;
   
   jugadores= Juego::Instance().getPlayers();
}


MenuPausa::MenuPausa(const MenuPausa& orig) {
}

MenuPausa::~MenuPausa() {
}

void MenuPausa::Render(){
    
    sfml->Instance().clear('k');  
    f1.draw();
    
    switch(statemenu){
        case 0:   
             sfml->Instance().getWindow()->draw(titulo);
           for(int i=NUMBER_OF_ITEMS-1; i>=0 ;i--){
                mancha[i].draw();
                sfml->Instance().getWindow()->draw(menu[i]);
                personaje.draw();
            }
            break;
        case 1:
            sfml->Instance().getWindow()->draw(titulo2);
            manchahtp.draw();
            sfml->Instance().getWindow()->draw(menuhow);
            controles.draw();
            break;
    }

     sfml->Instance().display();
    
}

void MenuPausa::muevepersonaje(int selec){
   
            switch(selec){
                case 0:
                    personaje.setPosition(posx-width/11, posy-height/21);
                    break;

                case 1:
                    personaje.setPosition(posx-width/40, posy+height/12);
                    break;

                case 2:
                    personaje.setPosition(posx-width/11, posy+height/4.7);
                    break;
            }
      
}

void MenuPausa::MoveUp(){
    switch(statemenu){
       case 0:
            if(selectedItemIndex-1>=0){
                menu[selectedItemIndex].setFillColor(sf::Color::Black);
                selectedItemIndex--;
                menu[selectedItemIndex].setFillColor(sf::Color::White);
                muevepersonaje(selectedItemIndex);

            }
           
    }
}

void MenuPausa::MoveDown(){
     switch(statemenu){
       case 0:
            if(selectedItemIndex+1<NUMBER_OF_ITEMS){
                menu[selectedItemIndex].setFillColor(sf::Color::Black);
                selectedItemIndex++;
                menu[selectedItemIndex].setFillColor(sf::Color::White);
                muevepersonaje(selectedItemIndex);

            }
            break;
     }
}


/*void MenuPausa::PonInmortal(){
    for(int i=0; i<jugadores->size(); i++){
      jugadores[0][i]->hazInmortal();
    }
}*/

void MenuPausa::Update(){
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
                                           //std::cout<<"Continue pressed"<< std::endl;
                                            sfml->Instance().ChangeState(&Juego::Instance());
                                            break;

                                        case 1:
                                            statemenu=1;
                                            MoveUp();
                                            personaje.setPosition(posx-width/11, posy-height/21);
                                            //std::cout<<"Options pressed"<< std::endl;
                                            break;

                                        case 2:

                                            sfml->Instance().ChangeState(MenuInicio::Instance());
                                           // std::cout<<"Exit pressed"<< std::endl;
                                            break;
                                    }
                                    break;
                                    
                                case 1:
                                   statemenu=0;
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

    width =  sfml->Instance().getViewSize()[0];
    height = sfml->Instance().getViewSize()[1];
    
    posx = sfml->Instance().getViewCenter()[0];
    posy = sfml->Instance().getViewCenter()[1];
    
    personaje.setPosition(posx-width/11, posy-height/21);

    mancha[0].setPosition(posx-width/30, posy-height/15);
    mancha[1].setPosition(posx+width/30, posy+height/15);
    mancha[2].setPosition(posx-width/30, posy+height/5);
    
    
   titulo.setPosition(sf::Vector2f(posx-width/20, posy-height/3));    
   menu[0].setPosition(posx-width/18, posy-height/15);
   menu[1].setPosition(posx, posy+height/15);
   menu[2].setPosition(posx-width/30, posy+height/5);
   
   
   titulo2.setPosition(posx-width/15, posy-height/2.5);
   menuhow.setPosition(posx+width/40, posy+height/2.5);
   manchahtp.setPosition(posx+width/40, posy+height/2.5);
   controles.setPosition(posx, posy+height/3.9);

    while (sfml->Instance().isOpen())
    {
        //Bucle de obtención de eventos
 
        Update();
        Render();       

    }
}