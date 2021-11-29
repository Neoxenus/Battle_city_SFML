#include "SFML/Graphics.hpp"
#include "Server.h"
#include "Client.h"
#include "Tank.h"
#include <ctime>
#include <iostream>
#include "windows.h"
#include "Menu.h"
//при каждой отрисовке танка рисовать все пули?

void newGame(Tank& tank1, std::vector<Tank>& tankAI, Field& field1)
{
    field1.setField(constants::field1);
    Tank buf(true, 0);
    tank1 = buf;
    std::vector<Tank> bufTankAI{ {false, 0}, {false, 0}, {false, 0}, {false, 0} };
    tankAI = bufTankAI;
}

int main()
{
    srand(time(NULL)); // for random

    //hide console
    HWND Hide;
    AllocConsole();
    Hide = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Hide, 1);
    //

    sf::Texture texture_all;
    texture_all.loadFromFile("allSprites.png");
    sf::Texture texture_block;
    texture_block.loadFromFile("tiles.png");
    sf::Texture texture_base;
    texture_base.loadFromFile("sprites.png");

    Field field1;
    field1.setField(constants::field1);
    Tank tank1(true , 0);
    std::vector<Tank> tankAI{ {false, 0}, {false, 0}, {false, 0}, {false, 0} };
    std::vector<double> tankAIRespawnTime{ 0.0, 3.0, 6.0, 9.0};

    sf::RenderWindow window(sf::VideoMode(768, 768), "", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(240);
    sf::View view = window.getDefaultView();

    view.zoom(constants::zoom);
    window.setView(view);
   
    Menu menu(768, 768, constants::MAX_NUMBER_OPTIONS_MAIN_MENU, constants::mainMenu);

    sf::Clock clock;
    double timer = 0;
    int fps = 0;
    double delay = constants::delay;

    bool isGameActive = false;
    bool isMP = false , isHost = false;
    while (window.isOpen())
    {
        sf::Event event;
        if (!isGameActive)
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    int x = sf::Mouse::getPosition(window).x, y = sf::Mouse::getPosition(window).y;
                    /*std::cout << std::endl;
                    std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << std::endl;
                    std::cout << menu.choose(x, y) << std::endl;*/
                    switch (menu.choose(x, y))
                    {
                    case 0://new s0l0 game
                        newGame(tank1, tankAI, field1);
                        clock.restart();
                        isGameActive = true;
                        isMP = false;
                        timer = 0;
                        fps = 0;
                        delay = constants::delay;
                        break;
                    case 1://new host
                        isGameActive = true;
                        isMP = true;
                        isHost = true;
                        break;
                    case 2://new client
                        isGameActive = true;
                        isMP = true;
                        isHost = false;
                        break;
                    default:
                        //std::cout << "Something wrong with mouse coordinate\n";
                        break;
                    }


                }
            }
                
            window.clear(sf::Color::Black);
            menu.draw(window);
            window.display();
        }
        else
        {
                if (!isMP )
                    {
                        timer = clock.getElapsedTime().asMilliseconds() / 1000.0;
                        sf::Event event;
                        if (timer > delay)
                        {
                            while (window.pollEvent(event))
                            {
                                tank1.bullet_shoot(window, event);

                                    if (event.type == sf::Event::Closed)
                                        window.close();
                                    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                                    //    isGameActive = false;
                                }

                            for (int i = 0; i < tankAIRespawnTime.size(); ++i)
                            {
                                if (timer > tankAIRespawnTime[i] && abs(timer - tankAIRespawnTime[i]) <= 15)
                                {
                                    /*for (auto& tank : tankAI)
                                    {
                                        if ()
                                    }*/
                                    tankAI[i].setVisibility(true);
                                    tankAI[i].setCoordX(constants::DEFAULT_ENEMY_COORD_X[rand() % 2]);
                                    tankAI[i].setSubCoordX(tankAI[i].getCoordX());
                                    tankAI[i].setCoordY(constants::DEFAULT_ENEMY_COORD_Y);
                                    tankAI[i].setSubCoordY(tankAI[i].getCoordY());
                                    tankAIRespawnTime[i] = 257;
                                }
                            }
                                for (int i = 0; i < 1/*tankAIRespawnTime.size()*/; ++i)
                                {
                                    if (timer > tankAIRespawnTime[i])
                                    {
                                        /*for (auto& tank : tankAI)
                                        {
                                            if ()
                                        }*/
                                        tankAI[i].setVisibility(true);
                                        tankAIRespawnTime[i] = 0.0;
                                    }
                                }

                            tank1.animation(fps);
                            for (int i = 0; i < tankAI.size(); ++i)
                            {
                                tankAI[i].animation(fps);
                                if (tankAI[i].isVisible() && tankAI[i].tankDeath(tank1))
                                {
                                    tankAI[i].setVisibility(false);
                                    tankAI[i].setCoordX(0);
                                    tankAI[i].setCoordY(0);
                                    tankAIRespawnTime[i] = (static_cast<int>(timer) + 3) % 256;
                                }
                            }

                            if (timer < 24.0)
                            {
                                for (auto& tank : tankAI)
                                {
                                    if (tank.isVisible())
                                    {
                                        tank.moveAIRandomly(window, field1, event);
                                    }
                                }
                            }
                            else if (timer < 48.0)
                            {
                                for (auto& tank : tankAI)
                                {
                                    if (tank.isVisible())
                                    {
                                        tank.moveAIToAlly(window, field1, event, tank1);
                                    }
                                }
                            }
                            else
                            {
                                for (auto& tank : tankAI)
                                {
                                    if (tank.isVisible())
                                    {
                                        tank.moveAIToBase(window, field1, event);
                                    }
                                }
                            }
                            for (int i = 0; i < tankAI.size(); ++i)
                                for (int j = 1; j < tankAI.size(); ++j)
                                {
                                    if (i == j) continue;
                                    if (tankAI[i].tankWithTankCollision(tankAI[j]))
                                    {
                                        tankAI[i].setDirection(static_cast<constants::Directions>((static_cast<int>(tankAI[i].getDirection()) + 2) % 4));
                                    }
                                }

                                delay += constants::delay;

                            ++fps;
                            //if (timer > 1 && fps < 129)
                            //{
                            //    std::cout << fps << "\n";
                            //    //exit(1);
                            //}
               
                            window.clear(sf::Color::Black);                           
                            field1.draw(window, texture_block, texture_base);
                            tank1.draw(window, texture_all); // coord in tiles // spawn tank
                            tank1.control(window, field1, event);
                            tank1.bullets_colision(field1); 

                            for (auto& tank : tankAI)
                                if (tank.isVisible())
                                    tank.draw(window, texture_all);
                
                            timer = 0;
                            window.display();
                
                            //clock.restart();
                        }
                        if (timer > constants::delay * 128 * 256)
                        {
                            delay = constants::delay;
                            timer = 0;
                            clock.restart();
                        }
                    }

                if (isMP)
                {
                    if (isHost)
                    {
                        Server serv;
                        serv.server();
                        serv.loop(field1, tank1);
                    }
                    else
                    {
                        Client cl;
                        cl.client();
                        cl.exchange(field1, tank1);
                    }
                }
            }
        }

    
}