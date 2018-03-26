#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <string>
#include "Animator.h"
#include "AssetManager.h"
#include <SFML/Graphics/Sprite.hpp>


int main()
{
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(640, 480), "Animaciones Player");

    //Creación de jugadores
    Player jugador(0,"Jugador 1");
    
    std::cout << jugador.getId() << std::endl;
    std::cout << jugador.getName() << std::endl;
    
    Player jugador2(1,"Jugador 2");
    
    std::cout << jugador2.getId() << std::endl;
    std::cout << jugador2.getName() << std::endl;
    
    
    //INICIALIZAR ASSET MANAGER
    AssetManager* manager;
    manager->Instance();
    
    
    //sf::Time deltaTime;
    sf::Clock clock;

    //Bucle del juego
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        
        //Cambiar el sprite de los jugadores
        jugador.update(deltaTime);
        jugador2.update(deltaTime);
        
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                
               
                //Se pulsó una tecla
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        
                        //JUGADOR 1
                        case sf::Keyboard::Right:
                            jugador.moveRigth();
                        break;

                        case sf::Keyboard::Left:
                            jugador.moveLeft();
                        break;
                        
                        case sf::Keyboard::Up:     
                            jugador.moveUp();
                        break;
                        
                        case sf::Keyboard::Down:
                            jugador.moveDown();
                         
                        break;
                        //JUGADOR 2
                        case sf::Keyboard::D:
                            jugador2.moveRigth();
                        break;
                        case sf::Keyboard::A:
                            jugador2.moveLeft();
                        break;
                        case sf::Keyboard::W:
                            jugador2.moveUp();
                        break;
                        case sf::Keyboard::S:
                            jugador2.moveDown();
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
                        //JUGADOR 1
                        case sf::Keyboard::Left:
                            jugador.moveLeft_b();
                        break;
                        
                        case sf::Keyboard::Right:
                            jugador.moveRigth_b();
                        break;
                        
                        //JUGADOR 2
                        case sf::Keyboard::A:
                            jugador2.moveLeft_b();
                        break;
                        
                        case sf::Keyboard::D:
                            jugador2.moveRigth_b();
                        break;
                    }
                break;
                    
                
                
            }
            
        }
        
        //Dibujado
        window.clear();
        window.draw(jugador.getSprite());
        window.draw(jugador2.getSprite());
        window.display();
    }

    return 0;
}