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
    
    /*fondo*/
    text_fondo.loadFromFile("assets/fondo.PNG");
    
    f1.setTexture(text_fondo);
    f1.setSize(sfml->Instance().getViewSize()[0], sfml->Instance().getViewSize()[1]);
    
        /*LOGO*/
    std::string logo_name = "assets/Logo.png";
    
    int widthl = AssetManager::GetTexture(logo_name).getXSize();
    int heightl = AssetManager::GetTexture(logo_name).getYSize();
    
    logo.setTexture(AssetManager::GetTexture(logo_name));
    logo.setOrigin(widthl / 2, heightl / 2);
    logo.setScale(0.4,0.4);
    logo.setPosition(posx, posy+height/3);
    
    tam=0.05;
    logo1.setTexture(AssetManager::GetTexture(logo_name));
    logo1.setOrigin(widthl / 2, heightl/4);
    logo1.setScale(tam, tam);
    logo1.setPosition(posx, posy-height/10);
    
    /*PERSONAJE*/
    std::string sprite_name1 = "assets/personaje.png";
    
    int widthp = AssetManager::GetTexture(sprite_name1).getXSize();
    int heightp = AssetManager::GetTexture(sprite_name1).getYSize();
    
    personaje.setTexture(AssetManager::GetTexture(sprite_name1));
    personaje.setOrigin(widthp / 2, heightp / 2.1);
    personaje.setScale(0.05, 0.05);
    personaje.setPosition(posx-width/11, posy-height/21);


    
    /*MANCHAS DEL MENU*/
    std::string sprite_name = "assets/mancha1.png";
    
    int widths = AssetManager::GetTexture(sprite_name).getXSize();
    int heights = AssetManager::GetTexture(sprite_name).getYSize();
    
    for(int i=0; i<MAX_NUMBER_OF_ITEMS; i++){
        mancha[i].setTexture(AssetManager::GetTexture(sprite_name));
        mancha[i].setOrigin(widths / 2, heights / 2.1);
        mancha[i].setScale(0.55, 0.55);
    }
    
    manchahtp.setTexture(AssetManager::GetTexture(sprite_name));
    manchahtp.setOrigin(widths / 2, heights / 2.1);
    manchahtp.setScale(0.45, 0.45);
    
    /*letras del menu*/
  
   if (!font.loadFromFile("resources/fuente.ttf"))
    {
            std::cerr << "Error cargando la imagen sprite.png";
            exit(0);	
    }
    
   titulo.setFont(font);
   titulo.setCharacterSize(20);
   titulo.setFillColor(sf::Color::Red);
   titulo.setString("PRESS START!!");
   titulo.setPosition(sf::Vector2f(posx-width/40, posy+height/3));
  
   
   menu[0].setFont(font);
   menu[0].setCharacterSize(16);
   menu[0].setFillColor(sf::Color::White);
   menu[0].setString("Play");
   menu[0].setPosition(posx-width/2, posy-height/5);
   
   menu[1].setFont(font);
   menu[1].setCharacterSize(16);
   menu[1].setFillColor(sf::Color::Black);
   menu[1].setString("Options");
   menu[1].setPosition(posx-width/2, posy-height/10);
   
   menu[2].setFont(font);
   menu[2].setCharacterSize(16);
   menu[2].setFillColor(sf::Color::Black);
   menu[2].setString("How to play");
   menu[2].setPosition(posx-width/2, posy+height/10);
   
   menu[3].setFont(font);
   menu[3].setCharacterSize(16);
   menu[3].setFillColor(sf::Color::Black);
   menu[3].setString("Exit");
   menu[3].setPosition(posx-width/2, posy+height/5);
   
   
   /*MENU DE OPCIONES*/
   titulo2.setFont(font);
   titulo2.setCharacterSize(22);
   titulo2.setFillColor(sf::Color::Black);
   titulo2.setString("Options");
   titulo2.setPosition(posx-width/25, posy-height/3);
   
   menuop[0].setFont(font);
   menuop[0].setCharacterSize(16);
   menuop[0].setFillColor(sf::Color::White);
   menuop[0].setString("Sound");
   menuop[0].setPosition(posx-width/2, posy-height/6);
   
   menuop[1].setFont(font);
   menuop[1].setCharacterSize(16);
   menuop[1].setFillColor(sf::Color::Black);
   menuop[1].setString("Exit");
   menuop[1].setPosition(posx-width/2, posy+height/10);
   
   
   /*Menu players*/
   titulo3.setFont(font);
   titulo3.setCharacterSize(22);
   titulo3.setFillColor(sf::Color::Black);
   titulo3.setString("Players");
   titulo3.setPosition(posx-width/25, posy-height/3);
   
   menuplayer[0].setFont(font);
   menuplayer[0].setCharacterSize(16);
   menuplayer[0].setFillColor(sf::Color::White);
   menuplayer[0].setString("Play" );
   menuplayer[0].setPosition(posx-width/2, posy-height/6);
   
   menuplayer[1].setFont(font);
   menuplayer[1].setCharacterSize(16);
   menuplayer[1].setFillColor(sf::Color::Black);
   menuplayer[1].setString("Players "  + std::to_string(numplayers));
   menuplayer[1].setPosition(posx-width/2, posy+height/10);
   
   menuplayer[2].setFont(font);
   menuplayer[2].setCharacterSize(16);
   menuplayer[2].setFillColor(sf::Color::Black);
   menuplayer[2].setString("Exit");
   menuplayer[2].setPosition(posx-width/2, posy+height/8);
   
   
   /*How to play*/
   titulo4.setFont(font);
   titulo4.setCharacterSize(22);
   titulo4.setFillColor(sf::Color::Black);
   titulo4.setString("How to play");
   titulo4.setPosition(posx-width/25, posy-height/2.5);
   
   menuhow.setFont(font);
   menuhow.setCharacterSize(16);
   menuhow.setFillColor(sf::Color::White);
   menuhow.setString("Exit");
   menuhow.setPosition(posx-width/3, posy-height/6);
   
    /*Imagen Controles*/
    std::string sprite_namec = "assets/controles.png";
    
    int widthc = AssetManager::GetTexture(sprite_namec).getXSize();
    int heightc = AssetManager::GetTexture(sprite_namec).getYSize();
    
    controles.setTexture(AssetManager::GetTexture(sprite_namec));
    controles.setOrigin(widthc / 2, heightc / 2);
    controles.setScale(0.6, 0.6);
    controles.setPosition(posx, posy+height/3);
   
   
   
   selectedItemIndex=0;
   selectedItemIndex2=0;
   selectedItemIndex3=0;
  // selectedItemIndex4=3;
   statemenu=4;
   
   primero=true;
   
    //PARA LOS MANDOS
    m_Up = false;
    m_Down = false;
    controller_move = false;
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
           // sfml->Instance().getWindow()->draw(titulo);
            
            for(int i=MAX_NUMBER_OF_ITEMS-1; i>=0;i--){
                mancha[i].draw();
                sfml->Instance().getWindow()->draw(menu[i]);
                personaje.draw();
                logo.draw();
            }
            break;
        case 1:   
            sfml->Instance().getWindow()->draw(titulo2);
            mancha[0].draw();
            mancha[2].draw();
            
            for(int i=MAX_NUMBER_OF_ITEMS2-1; i>=0;i--){
                sfml->Instance().getWindow()->draw(menuop[i]);
                personaje.draw();

            }
            break;  
        case 2:
            sfml->Instance().getWindow()->draw(titulo3);

            for(int i=MAX_NUMBER_OF_ITEMS3-1; i>=0;i--){
                mancha[i].draw();
                sfml->Instance().getWindow()->draw(menuplayer[i]);
                personaje.draw();
            }
            break;
        case 3:
            sfml->Instance().getWindow()->draw(titulo4);
            manchahtp.draw();
            sfml->Instance().getWindow()->draw(menuhow);
            controles.draw();
            break;
        case 4:
           sfml->Instance().getWindow()->draw(titulo);
           logo1.setScale(tam, tam);
           if(tam<1){
                 tam+=0.05;
           }
            logo1.draw();
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
                menu[selectedItemIndex].setFillColor(sf::Color::White);
                muevepersonaje(selectedItemIndex);
            }
            break;
        case 1:
            if(selectedItemIndex2-1>=0){
                menuop[selectedItemIndex2].setFillColor(sf::Color::Black);
                selectedItemIndex2--;
                menuop[selectedItemIndex2].setFillColor(sf::Color::White);
                muevepersonaje(selectedItemIndex2);
            }
            break;
        case 2:
            if(selectedItemIndex3-1>=0){
                menuplayer[selectedItemIndex3].setFillColor(sf::Color::Black);
                selectedItemIndex3--;
                menuplayer[selectedItemIndex3].setFillColor(sf::Color::White);
                muevepersonaje(selectedItemIndex3);
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
                menu[selectedItemIndex].setFillColor(sf::Color::White);
                muevepersonaje(selectedItemIndex);
            }
            break;
        case 1:
            if(selectedItemIndex2+1<MAX_NUMBER_OF_ITEMS2){
                menuop[selectedItemIndex2].setFillColor(sf::Color::Black);
                selectedItemIndex2++;
                menuop[selectedItemIndex2].setFillColor(sf::Color::White);
                if(selectedItemIndex2==1){
                    muevepersonaje(selectedItemIndex2+1);
                }else{
                    muevepersonaje(selectedItemIndex2);
                }
            }
            break;
        case 2:
            if(selectedItemIndex3+1<MAX_NUMBER_OF_ITEMS3){
                menuplayer[selectedItemIndex3].setFillColor(sf::Color::Black);
                selectedItemIndex3++;
                menuplayer[selectedItemIndex3].setFillColor(sf::Color::White);
                muevepersonaje(selectedItemIndex3);
            }
            break;
    }
}

void MenuInicio::muevepersonaje(int selec){
    

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
                    
                case renderEngine::rEvent::EventType::JoystickMoved:
                    if(event.getJoystickMovePosition()<20 && event.getJoystickMoveAxis()==1){
                        if(!controller_move){
                            controller_move = true;
                            MoveUp();
                            //std::cout << "ARRIBA TRUE" << std::endl;
                        }
                        else{
                            controller_move = false;
                            //std::cout << "ARRIBA FALSE" << std::endl;
                        }
                    }
                    if(event.getJoystickMovePosition()>20 && event.getJoystickMoveAxis()==1){ 
                        if(!controller_move){
                            controller_move = true;
                            MoveDown();
                            //std::cout << "ABAJO TRUE" << std::endl;
                        }
                        else{
                            controller_move = false;
                            //std::cout << "ABAJO FALSE" << std::endl;
                        }
                    }
                    if(event.getJoystickMovePosition()>20 && event.getJoystickMoveAxis()==0){ 
                        if(!controller_move){
                            controller_move = true;
                            if(statemenu==2 && numplayers<4 && menuplayer[1].getFillColor()==sf::Color::White){
                                numplayers++;
                                menuplayer[1].setString("Players "  + std::to_string(numplayers));
                            }
                        }
                        else{
                            controller_move = false;
                        }
                    }
                    if(event.getJoystickMovePosition()<20 && event.getJoystickMoveAxis()==0){ 
                        if(!controller_move){
                            controller_move = true;
                            if(statemenu==2 && numplayers>1 && menuplayer[1].getFillColor()==sf::Color::White){
                                numplayers--;
                                menuplayer[1].setString("Players "  + std::to_string(numplayers));
                            }
                        }
                        else{
                            controller_move = false;
                        }
                    }
                    break;
                    
                case renderEngine::rEvent::EventType::JoystickButtonPressed:
                    if(event.getJoystickButton()==0) stateMenu();
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
                         case sf::Keyboard::Right:
                            if(statemenu==2 && numplayers<4 && menuplayer[1].getFillColor()==sf::Color::White){
                                numplayers++;
                                menuplayer[1].setString("Players "  + std::to_string(numplayers));
                            }
                            break;
                            
                        case sf::Keyboard::Left:
                            if(statemenu==2 && numplayers>1 && menuplayer[1].getFillColor()==sf::Color::White){
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

void MenuInicio::stateMenu() {
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
                    personaje.setPosition(posx-width/11, posy-height/21);

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
                    MoveUp();
                    statemenu=0;
                    selectedItemIndex2=0;
                    personaje.setPosition(posx-width/11, posy-height/21);
                    MoveUp();

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
                    MoveUp();
                    MoveUp();
                    statemenu=0;
                    selectedItemIndex=0;
                    personaje.setPosition(posx-width/11, posy-height/21);
                  // std::cout<<"Exit pressed"<< std::endl;

                    break;
            }
            break;
        case 3:
            statemenu=0;
            break;
        case 4:
            statemenu=0;
            break;

    }         
                       
}

void MenuInicio::Handle(){    
    if(primero==false){
        statemenu=0;
           titulo.setCharacterSize(60);
            menu[0].setCharacterSize(48);
            menu[1].setCharacterSize(48);
            menu[2].setCharacterSize(48);
            menu[3].setCharacterSize(48);
            
            for(int i=0; i<MAX_NUMBER_OF_ITEMS; i++){
                mancha[i].setScale(1.6, 1.6);
            }
            personaje.setScale(0.15, 0.15);
            logo.setScale(1.2, 1.2);
            controles.setScale(1.65, 1.65);
            manchahtp.setScale(1.65, 1.65);



            /*MENU DE OPCIONES*/
            titulo2.setCharacterSize(60);
            menuop[0].setCharacterSize(50);
            menuop[1].setCharacterSize(50);
          

            /*Menu players*/
            titulo3.setCharacterSize(60);
            menuplayer[0].setCharacterSize(50);
            menuplayer[1].setCharacterSize(50);
            menuplayer[2].setCharacterSize(50);


            /*How to play*/
            titulo4.setCharacterSize(60);
            menuhow.setCharacterSize(50);
            
            
    }
    
    
    
    width =  sfml->Instance().getViewSize()[0];
    height = sfml->Instance().getViewSize()[1];
    
    posx = sfml->Instance().getViewCenter()[0];
    posy = sfml->Instance().getViewCenter()[1];
        
    personaje.setPosition(posx-width/11, posy-height/21);
    logo.setPosition(posx-width/40, posy-height/6);


                
   titulo.setPosition(posx-width/10, posy+height/2.8);    
   menu[0].setPosition(posx-width/30, posy-height/15);
   menu[1].setPosition(posx+width/60, posy+height/15);
   menu[2].setPosition(posx-width/15, posy+height/5);
   menu[3].setPosition(posx+width/30, posy+height/3);

    /*manchas del menu*/   
    mancha[0].setPosition(posx-width/30, posy-height/15);
    mancha[1].setPosition(posx+width/30, posy+height/15);
    mancha[2].setPosition(posx-width/30, posy+height/5);
    mancha[3].setPosition(posx+width/30, posy+height/3);
    

    
   /*MENU DE OPCIONES*/
   titulo2.setPosition(posx-width/15, posy-height/3);
   menuop[0].setPosition(posx-width/30, posy-height/15);
   menuop[1].setPosition(posx-width/30, posy+height/5);
   
   
   /*Menu players*/
   titulo3.setPosition(posx-width/15, posy-height/3);
   menuplayer[0].setPosition(posx-width/30, posy-height/15);
   menuplayer[1].setPosition(posx, posy+height/15);
   menuplayer[2].setPosition(posx-width/20, posy+height/5);
   

   /*How to play*/
   titulo4.setPosition(posx-width/15, posy-height/2.5);
   menuhow.setPosition(posx+width/30, posy+height/2.5);
   manchahtp.setPosition(posx+width/40, posy+height/2.5);
   controles.setPosition(posx, posy+height/3.9);
   
    primero=false;
    
    while (sfml->Instance().isOpen())
    {
        //Bucle de obtención de eventos
        Update();
        Render();       

    }
}
