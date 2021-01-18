#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <iostream>

void moveObjects(sf::RectangleShape *car1,sf::RectangleShape *car2,sf::RectangleShape *car3,sf::RectangleShape *car4)
{

    int direction = 1; //1:to right , 0=to left
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (car1->getPosition().x==500)
        {
            direction=0;
        }
        if (car1->getPosition().x==0)
        {
            direction=1;
        }
        if (direction==1)
        {
            car1->move(5,0);
        }else if (direction==0)
        {
            car1->move(-5,0);
        }

        if (car2->getPosition().x==500)
        {
            direction=0;
        }
        if (car2->getPosition().x==0)
        {
            direction=1;
        }
        if (direction==1)
        {
            car2->move(6,0);
        }else if (direction==0)
        {
            car2->move(-6,0);
        }

        if (car3->getPosition().x==500)
        {
            direction=0;
        }
        if (car3->getPosition().x==0)
        {
            direction=1;
        }
        if (direction==1)
        {
            car3->move(3,0);
        }else if (direction==0)
        {
            car3->move(-3,0);
        }

        if (car4->getPosition().x==500)
        {
            direction=0;
        }
        if (car4->getPosition().x==0)
        {
            direction=1;
        }
        if (direction==1)
        {
            car4->move(8,0);
        }else if (direction==0)
        {
            car4->move(-8,0);
        }

    }


}

int main()
{
    using namespace sf;
    using namespace std;
    RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    RectangleShape player;
    RectangleShape car1;
    RectangleShape car2;
    RectangleShape car3;
    RectangleShape car4;

    player.setSize(Vector2f(40, 100));
    player.setPosition(290, 490);
    player.setFillColor(sf::Color::Blue);

    car1.setSize(Vector2f(80, 40));
    car1.setPosition(0, 430);
    car1.setFillColor(sf::Color::Red);
    car2.setSize(Vector2f(80, 40));
    car2.setPosition(0, 380);
    car2.setFillColor(sf::Color::Red);
    car3.setSize(Vector2f(80, 40));
    car3.setPosition(0, 330);
    car3.setFillColor(sf::Color::Red);
    car4.setSize(Vector2f(80, 40));
    car4.setPosition(0, 280);
    car4.setFillColor(sf::Color::Red);

    
    std::thread th(&moveObjects,&car1,&car2,&car3,&car4);
    

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                player.move(0, -10);
            }
        }
        
        window.clear();
        window.draw(player);
        window.draw(car1);
        window.draw(car2);
        window.draw(car3);
        window.draw(car4);
        window.display();
    }

    return 0;
}