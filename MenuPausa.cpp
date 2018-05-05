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
#include "AssetManager.h"

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
  
  
    font.loadFromFile("resources/fuente.ttf");

    titulo.setFont(font);
    titulo.setCharacterSize(56);
    titulo.setFillColor('k');
    titulo.setString("Pause");  


    menu[0].setFont(font);
    menu[0].setCharacterSize(48);
    menu[0].setFillColor('w');
    menu[0].setString("Continue");

    menu[1].setFont(font);
    menu[1].setCharacterSize(48);
    menu[1].setFillColor('k');
    menu[1].setString("Controls");

    menu[2].setFont(font);
    menu[2].setCharacterSize(44);
    menu[2].setFillColor('k');
    menu[2].setString("God Mode OFF");

    menu[3].setFont(font);
    menu[3].setCharacterSize(48);
    menu[3].setFillColor('k');
    menu[3].setString("Exit");

    /*MENU DE OPCIONES*/
    titulo2.setFont(font);
    titulo2.setCharacterSize(56);
    titulo2.setFillColor('k');
    titulo2.setString("Controls");

    menuhow.setFont(font);
    menuhow.setCharacterSize(48);
    menuhow.setFillColor('w');
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
       
    god_mode=false;
    
    controller_move_u = false;
    controller_move_d = false;
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
            titulo.draw();
           for(int i=NUMBER_OF_ITEMS-1; i>=0 ;i--){
                mancha[i].draw();
                menu[i].draw();
                personaje.draw();
            }
            break;
        case 1:
            titulo2.draw();
            manchahtp.draw();
            menuhow.draw();
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
                case 3:
                     personaje.setPosition(posx-width/40, posy+height/2.9);
                break;
            }
      
}

void MenuPausa::MoveUp(){
    if(statemenu==0){
            if(selectedItemIndex-1>=0){
                menu[selectedItemIndex].setFillColor('k');
                selectedItemIndex--;
                menu[selectedItemIndex].setFillColor('w');
                muevepersonaje(selectedItemIndex);

            }          
    }
}

void MenuPausa::MoveDown(){
    if(statemenu==0){
        if(selectedItemIndex+1<NUMBER_OF_ITEMS){
            menu[selectedItemIndex].setFillColor('k');
            selectedItemIndex++;
            menu[selectedItemIndex].setFillColor('w');
            muevepersonaje(selectedItemIndex);

        }
       
    }
}


/*void MenuPausa::PonInmortal(){
    for(int i=0; i<jugadores->size(); i++){
      jugadores[0][i]->hazInmortal();
    }
}*/

void MenuPausa::Update(){
    int c_sens = 90;
    renderEngine::rEvent event;
  
    f1.setSize(sfml->Instance().getViewSize()[0], sfml->Instance().getViewSize()[1]);
    f1.setPosition(((sfml->Instance().getViewCenter()[0])-(sfml->Instance().getViewSize()[0])/2), (sfml->Instance().getViewCenter()[1])-(sfml->Instance().getViewSize()[1])/2);

    
       while (sfml->Instance().pollEvent(event))
        {
            
            switch(event.sfType()){
                case renderEngine::rEvent::EventType::JoystickMoved:
                    /*
                    if(event.getJoystickMovePosition()>c_sens){
                        std::cout << "AXIS:" << event.getJoystickMoveAxis() << std::endl;
                        std::cout << "POSITION:" << event.getJoystickMovePosition() << std::endl;
                    }
                     */
                    if(abs(event.getJoystickMovePosition())>c_sens){
                        if(event.getJoystickMovePosition()<0 && event.getJoystickMoveAxis()==1){
                            if(!controller_move_u){
                                MoveUp();
                                controller_move_u = true;
                                if(controller_move_d) controller_move_d = false;
                            }
                        }
                        if(event.getJoystickMovePosition()>0 && event.getJoystickMoveAxis()==1){ 
                            if(!controller_move_d){
                                MoveDown();
                                controller_move_d = true;

                                if(controller_move_u) controller_move_u = false;
                            }
                        }
                    }
                    else{
                        if(event.getJoystickMoveAxis()==1 && controller_move_u){
                            controller_move_u = false;
                        }
                        if(event.getJoystickMoveAxis()==1 && controller_move_d){
                            controller_move_d = false;
                        }
                    }
                    break;
                    
                case renderEngine::rEvent::EventType::JoystickButtonPressed:
                    //std::cout << event.getJoystickButton() << std::endl;
                    if(event.getJoystickButton()==6) sfml->Instance().close();
                    if(event.getJoystickButton()==0 || event.getJoystickButton()==7) stateMenu();
                    break;
                    
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
                            stateMenu();
                             
                                                  
                            break;
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.getKeyCode() << std::endl;
                        break;
                              
                    }
                     
            }
         
        }  
}

void MenuPausa::stateMenu() {
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
                    //std::cout<<"Controls pressed"<< std::endl;
                    break;
                case 2:
                    
                    //GOD MODE
                    if(god_mode==false){
                        menu[2].setString("God Mode ON");
                        god_mode=true;
                    }
                    else{
                        menu[2].setString("God Mode OFF");     
                        god_mode=false; 
                    }
                    break;

                case 3:
                    sfml->Instance().ChangeState(MenuInicio::Instance());
                    // std::cout<<"Exit pressed"<< std::endl;
                    break;
            }
            break;

        case 1:
            statemenu=0;
            MoveUp();
            break;
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
    mancha[3].setPosition(posx+width/30, posy+height/3);

    
    
   titulo.setPosition(posx-width/20, posy-height/3);    
   menu[0].setPosition(posx-width/18, posy-height/15);
   menu[1].setPosition(posx, posy+height/15);
   menu[2].setPosition(posx-width/15, posy+height/5);
   menu[3].setPosition(posx+width/30, posy+height/3);
   
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