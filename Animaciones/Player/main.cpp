#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <string>
#include "Animator.h"
#include "AssetManager.h"
#include <SFML/Graphics/Sprite.hpp>
#define kVel 5

int main()
{
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");

    Player jugador(1,"Javi");
    std::cout << jugador.getId() << std::endl;
    std::cout << jugador.getName() << std::endl;
    jugador.setId(2);
    std::cout << jugador.getId() << std::endl;
    std::cout << jugador.getName() << std::endl;
    

    
    AssetManager manager;
    manager.GetTexture("resources/player6.png");    
    
    sf::Vector2i spriteSize(60,60);
    sf::Sprite sprite;
    
    sf::Sprite sprite2;
    Animator animator2(sprite2);
    
  
    Animator animator(sprite);
    auto& a_base = animator.CreateAnimation("a_base","resources/player6.png", sf::seconds(3), false);
    a_base.AddFrames(sf::Vector2i(0,0), spriteSize ,1);
    
    //Giro izquierda
    auto& a_left = animator.CreateAnimation("a_left","resources/player6.png", sf::seconds(0.3), false);
    a_left.AddFrames(sf::Vector2i(0,0), spriteSize , 3);
    auto& a_base_l = animator.CreateAnimation("a_base_l","resources/player6.png", sf::seconds(0.2), false);
    a_base_l.AddFrames(sf::Vector2i(180,0), spriteSize , 2);
    
    //Giro derecha
    auto& a_rigth = animator.CreateAnimation("a_rigth","resources/player6.png", sf::seconds(0.3), false);
    a_rigth.AddFrames(sf::Vector2i(300,0), spriteSize , 3);
    auto& a_base_r = animator.CreateAnimation("a_base_r","resources/player6.png", sf::seconds(0.2), false);
    a_base_r.AddFrames(sf::Vector2i(480,0), spriteSize , 2);
    
    //Salto izquierda
    auto& a_jump_l = animator.CreateAnimation("a_jump_l","resources/player6.png", sf::seconds(2), false);
    a_jump_l.AddFrames(sf::Vector2i(0,60), spriteSize ,9);          
    
    //Salto derecha
    auto& a_jump_r = animator.CreateAnimation("a_jump_r","resources/player6.png", sf::seconds(2), false);
    a_jump_r.AddFrames(sf::Vector2i(0,180), spriteSize ,9);   
    
    //Para colision
    auto& a_fall_l = animator.CreateAnimation("a_fall_l","resources/player6.png", sf::seconds(0.5), false);
    a_fall_l.AddFrames(sf::Vector2i(0,120), spriteSize ,3);
    auto& a_fall_r = animator.CreateAnimation("a_fall_r","resources/player6.png", sf::seconds(0.5), false);
    a_fall_r.AddFrames(sf::Vector2i(180,120), spriteSize ,3);
    
    
    
    
    
    
    
    //sf::Time deltaTime;
    sf::Clock clock;

    //Bucle del juego
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        animator.Update(deltaTime);
        
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            //deltaTime =clock.restart();
            //float dtAsSeconds = deltaTime.asSeconds();
            
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                
               
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        
                        //Mapeo del cursor
                        case sf::Keyboard::Right:
                            if(animator.GetCurrentAnimationName() != "a_rigth"){
                                animator.SwitchAnimation("a_rigth");
                            }
                                                    
                            
                        break;

                        case sf::Keyboard::Left:
                           
                            if(animator.GetCurrentAnimationName() != "a_left"){
                                animator.SwitchAnimation("a_left");
                            }
                                                                                  
                        break;
                        
                        case sf::Keyboard::Up:     
                            if(animator.GetCurrentAnimationName() == "a_base_r"){
                                
                            }
                            
                            if(animator.GetCurrentAnimationName() == "a_left"){
                                animator.SwitchAnimation("a_jump_l");
                            }
                            if(animator.GetCurrentAnimationName() == "a_rigth"){
                                animator.SwitchAnimation("a_jump_r");
                            }
                            
                        break;
                        
                        case sf::Keyboard::Down:
                            if(animator.GetCurrentAnimationName() == "a_jump_l" || animator.GetCurrentAnimationName() == "a_base_l" ){
                                animator.SwitchAnimation("a_fall_l");
                            }
                            if(animator.GetCurrentAnimationName() == "a_jump_r" || animator.GetCurrentAnimationName() == "a_base_r" ){
                                animator.SwitchAnimation("a_fall_r");
                            }
                            
                         
                        break;
                        
                        
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                        break;
                              
                    }
                break;
                 
                    
                case sf::Event::EventType::KeyReleased:
                    switch(event.key.code) {
                        case sf::Keyboard::Left:
                            if(animator.GetCurrentAnimationName() != "a_base_l"){
                                animator.SwitchAnimation("a_base_l");
                            }
                        break;
                        case sf::Keyboard::Right:
                            if(animator.GetCurrentAnimationName() != "a_base_r"){
                                animator.SwitchAnimation("a_base_r");
                            }
                        break;
                        
                        case sf::Keyboard::Down:
                            if(animator.GetCurrentAnimationName() == "a_jump_l"){
                                animator.SwitchAnimation("fall_l");
                            }
                            if(animator.GetCurrentAnimationName() == "a_jump_r"){
                                animator.SwitchAnimation("fall_r");
                            }
                            
                        break;
                    }
                break;
                
                
            }
            
        }
        
        window.clear();
        window.draw(sprite);
        //window.draw(jugador.getSprite());
        window.display();
    }

    return 0;
}