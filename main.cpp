#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <SFML/Audio.hpp>

int carsCount = 12;
int startWindow_w = 700;
int startWindow_h = 1000;
int gameWindow_w = 1300;
int gameWindow_h = 1100;
int car_w = 160;
int car_h = 80;
int player_w = 70;
int player_h = 70;
int stick_width_scale = 120;
bool PlayerOnStick = false;
int gameSituation = 0;

class Car : public sf::RectangleShape

{
private:
    int speed;
    char direction;
    char status = 'i'; //o:out i:in
public:
    void setStatus(char c)
    {
        status = c;
    }
    char getStatus()
    {
        return status;
    }
    void setSpeed(int s)
    {
        speed = s;
    }
    int getSpeed()
    {
        return speed;
    }
    void setDirection(char d)
    {
        direction = d;
    }
    char getDirection()
    {
        return direction;
    }
};

class Stick : public sf::RectangleShape
{
private:
    int speed;
    char status;    //o:out i:in
    char direction; //R:right L:left
public:
    void setStatus(char c)
    {
        status = c;
    }
    char getStatus()
    {
        return status;
    }
    void setSpeed(int s)
    {
        speed = s;
    }
    int getSpeed()
    {
        return speed;
    }
    void setDirection(int d)
    {
        direction = d;
    }
    int getDirection()
    {
        return direction;
    }
};

void moveCars(std::vector<Car> &cars)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        for (int i = 0; i < carsCount; i++)
        {
            if (cars[i].getStatus() == 'i')
            {
                if (cars[i].getDirection() == 'R')
                {
                    if (cars[i].getPosition().x >= gameWindow_w)
                    {
                        cars[i].setStatus('o');
                    }
                    else
                    {
                        cars[i].move(cars[i].getSpeed(), 0);
                    }
                }
                else if (cars[i].getDirection() == 'L')
                {
                    if (cars[i].getPosition().x <= -car_w)
                    {
                        cars[i].setStatus('o');
                    }
                    else
                    {
                        cars[i].move(-cars[i].getSpeed(), 0);
                    }
                }
            }
        }
    }
}

void moveSticks(std::vector<Stick> &sticks1, std::vector<Stick> &sticks2, std::vector<Stick> &sticks3, std::vector<Stick> &sticks4, sf::RectangleShape *player)
{

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        bool isPlayerOnStick = false;
        for (int i = 0; i < 3; i++)
        {
            if (sticks1[i].getStatus() == 'i')
            {
                if (sticks1[i].getPosition().x >= gameWindow_w)
                {
                    sticks1[i].setStatus('o');
                }
                else
                {
                    sticks1[i].move(sticks1[i].getSpeed(), 0);
                }

                //check if player is on stick
                if ((player->getPosition().y == sticks1[i].getPosition().y + 5) &&
                    ((player->getPosition().x >= sticks1[i].getPosition().x - (player_w / 2)) &&
                     (player->getPosition().x + player_w <= sticks1[i].getPosition().x + sticks1[i].getSize().x + (player_w / 2))))
                {
                    isPlayerOnStick = true;
                    if (gameWindow_w - 5 - (player->getPosition().x + player_w) < sticks1[i].getSpeed())
                    {
                        player->move(gameWindow_w - 5 - (player->getPosition().x + player_w), 0);
                    }
                    else
                    {
                        player->move(sticks1[i].getSpeed(), 0);
                    }
                }
                //
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (sticks2[i].getStatus() == 'i')
            {
                if (sticks2[i].getPosition().x <= -sticks2[i].getSize().x)
                {
                    sticks2[i].setStatus('o');
                }
                else
                {
                    sticks2[i].move(-sticks2[i].getSpeed(), 0);
                }
                //check if player is on stick
                if ((player->getPosition().y == sticks2[i].getPosition().y + 5) &&
                    ((player->getPosition().x >= sticks2[i].getPosition().x - (player_w / 2)) &&
                     (player->getPosition().x + player_w <= sticks2[i].getPosition().x + sticks2[i].getSize().x + (player_w / 2))))
                {
                    isPlayerOnStick = true;
                    if (player->getPosition().x - 5 < sticks2[i].getSpeed())
                    {
                        player->move(-(player->getPosition().x - 5), 0);
                    }
                    else
                    {
                        player->move(-sticks2[i].getSpeed(), 0);
                    }
                }
                //
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (sticks3[i].getStatus() == 'i')
            {
                if (sticks3[i].getPosition().x >= gameWindow_w)
                {
                    sticks3[i].setStatus('o');
                }
                else
                {
                    sticks3[i].move(sticks3[i].getSpeed(), 0);
                }
            }
            //check if player is on stick
            if ((player->getPosition().y == sticks3[i].getPosition().y + 5) &&
                ((player->getPosition().x >= sticks3[i].getPosition().x - (player_w / 2)) &&
                 (player->getPosition().x + player_w <= sticks3[i].getPosition().x + sticks3[i].getSize().x + (player_w / 2))))
            {
                isPlayerOnStick = true;
                if (gameWindow_w - 5 - (player->getPosition().x + player_w) < sticks3[i].getSpeed())
                {
                    player->move(gameWindow_w - 5 - (player->getPosition().x + player_w), 0);
                }
                else
                {
                    player->move(sticks3[i].getSpeed(), 0);
                }
            }
            //
        }
        for (int i = 0; i < 3; i++)
        {
            if (sticks4[i].getStatus() == 'i')
            {
                if (sticks4[i].getPosition().x <= -sticks4[i].getSize().x)
                {
                    sticks4[i].setStatus('o');
                }
                else
                {
                    sticks4[i].move(-sticks4[i].getSpeed(), 0);
                }
                //check if player is on stick
                if ((player->getPosition().y == sticks4[i].getPosition().y + 5) &&
                    ((player->getPosition().x >= sticks4[i].getPosition().x - (player_w / 2)) &&
                     (player->getPosition().x + player_w <= sticks4[i].getPosition().x + sticks4[i].getSize().x + (player_w / 2))))
                {
                    isPlayerOnStick = true;
                    if (player->getPosition().x - 5 < sticks4[i].getSpeed())
                    {
                        player->move(-(player->getPosition().x - 5), 0);
                    }
                    else
                    {
                        player->move(-sticks4[i].getSpeed(), 0);
                    }
                }
                //
            }
        }
        //ckeck if player has fallen in water
        if (player->getPosition().y >= 100 && player->getPosition().y <= 500)
        {
            if (!isPlayerOnStick)
            {
                gameSituation = 2;
            }
        }
    }
}

void createNewCarSet(std::vector<Car> &cars)
{
    int setNum = 0;
    while (true)
    {
        for (int i = 0; i < 4; i++)
        {
            if (cars[setNum * 4 + i].getStatus() == 'o')
            {
                int speed = (rand() % 5) + 13; //13-17
                char direction = (i % 2 == 0) ? 'R' : 'L';
                if (direction == 'R')
                {
                    cars[setNum * 4 + i].setPosition(-car_w, cars[setNum * 4 + i].getPosition().y);
                }
                else if (direction == 'L')
                {
                    cars[setNum * 4 + i].setPosition(gameWindow_w, cars[setNum * 4 + i].getPosition().y);
                }
                cars[setNum * 4 + i].setSpeed(speed);
                cars[setNum * 4 + i].setStatus('i');
                cars[setNum * 4 + i].setDirection(direction);
            }
        }
        setNum++;
        if (setNum == 3)
        {
            setNum = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1700));
    }
}

void createNewStickLine1(std::vector<Stick> &sticks)
{
    int replacingDelay = ((rand() % 3) + 3) * 1000; //3000-5000millisec
    int speed = (rand() % 5) + 11;                  //11-15
    int width = ((rand() % 4) + 1) * stick_width_scale;
    int i = 0;
    while (true)
    {
        if (sticks[i].getStatus() == 'o')
        {
            sticks[i].setSize(sf::Vector2f(width, car_h));
            sticks[i].setPosition(-sticks[i].getSize().x, sticks[i].getPosition().y);
            sticks[i].setSpeed(speed);
            sticks[i].setStatus('i');
            sticks[i].setDirection('R');
        }
        i++;
        if (i == 3)
        {
            i = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(replacingDelay));
    }
}

void createNewStickLine2(std::vector<Stick> &sticks)
{
    int replacingDelay = ((rand() % 3) + 3) * 1000; //3000-5000millisec
    int speed = (rand() % 5) + 11;                  //11-15
    int width = ((rand() % 4) + 1) * stick_width_scale;
    int i = 0;
    while (true)
    {
        if (sticks[i].getStatus() == 'o')
        {
            sticks[i].setSize(sf::Vector2f(width, car_h));
            sticks[i].setPosition(gameWindow_w, sticks[i].getPosition().y);
            sticks[i].setSpeed(speed);
            sticks[i].setStatus('i');
            sticks[i].setDirection('L');
        }
        i++;
        if (i == 3)
        {
            i = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(replacingDelay));
    }
}

void createNewStickLine3(std::vector<Stick> &sticks)
{
    int replacingDelay = ((rand() % 3) + 3) * 1000; //3000-5000millisec
    int speed = (rand() % 5) + 11;                  //11-15
    int width = ((rand() % 4) + 1) * stick_width_scale;
    int i = 0;
    while (true)
    {
        if (sticks[i].getStatus() == 'o')
        {
            sticks[i].setSize(sf::Vector2f(width, car_h));
            sticks[i].setPosition(-sticks[i].getSize().x, sticks[i].getPosition().y);
            sticks[i].setSpeed(speed);
            sticks[i].setStatus('i');
            sticks[i].setDirection('R');
        }
        i++;
        if (i == 3)
        {
            i = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(replacingDelay));
    }
}

void createNewStickLine4(std::vector<Stick> &sticks)
{
    int replacingDelay = ((rand() % 3) + 3) * 1000; //3000-5000millisec
    int speed = (rand() % 5) + 11;                  //11-15
    int width = ((rand() % 4) + 1) * stick_width_scale;
    int i = 0;
    while (true)
    {
        if (sticks[i].getStatus() == 'o')
        {
            sticks[i].setSize(sf::Vector2f(width, car_h));
            sticks[i].setPosition(gameWindow_w, sticks[i].getPosition().y);
            sticks[i].setSpeed(speed);
            sticks[i].setStatus('i');
            sticks[i].setDirection('L');
        }
        i++;
        if (i == 3)
        {
            i = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(replacingDelay));
    }
}

void resetGame(sf::RectangleShape &player)
{
    player.setPosition((gameWindow_w - player_w) / 2, gameWindow_h - player_h - 15);
    gameSituation = 0;
}
int main()
{
    srand(time(NULL));
    using namespace sf;
    using namespace std;
    RenderWindow startWindow;
    RenderWindow gameWindow;
    startWindow.create(sf::VideoMode(startWindow_w, startWindow_h), "works!");

    vector<Car> cars;
    vector<Stick> sticks1;
    vector<Stick> sticks2;
    vector<Stick> sticks3;
    vector<Stick> sticks4;

    char const *fileNamesLeft[] = {"Images/carl0.png", "Images/carl1.png", "Images/carl2.png", "Images/carl3.png", "Images/carl4.png", "Images/carl5.png", "Images/carl6.png"};
    char const *fileNamesRight[] = {"Images/carr0.png", "Images/carr1.png", "Images/carr2.png", "Images/carr3.png", "Images/carr4.png", "Images/carr5.png", "Images/carr6.png"};
    Texture txt[carsCount];
    Texture logg[5];
    logg[0].loadFromFile("Images/log1.png");
    logg[1].loadFromFile("Images/log2.png");
    logg[2].loadFromFile("Images/log3.png");
    logg[3].loadFromFile("Images/log4.png");
    logg[4].loadFromFile("Images/log5.png");

    for (int i = 0; i < carsCount; i++)
    {
        int n = rand();
        if (i % 4 == 0 || i % 4 == 2)
        {
            txt[i].loadFromFile(fileNamesRight[n % 7]);
        }
        else if (i % 4 == 1 || i % 4 == 3)
        {
            txt[i].loadFromFile(fileNamesLeft[n % 7]);
        }
        Car car;
        //car.setFillColor(sf::Color::Red);
        car.setSize(Vector2f(car_w, car_h));
        car.setStatus('o');
        car.setPosition(0, gameWindow_h - (((i % 4) + 2) * 100) + ((100 - car_h) / 2));
        car.setTexture(&txt[i]);
        cars.push_back(car);
    }

    for (int i = 0; i < 3; i++)
    {
        int n = rand();
        Stick stick;
        stick.setSize(Vector2f(100, car_h));
        stick.setStatus('o');
        stick.setPosition(0, gameWindow_h - 700 + 10);
        stick.setTexture(&logg[n % 5]);
        sticks1.push_back(stick);
    }

    for (int i = 0; i < 3; i++)
    {
        int n = rand();
        Stick stick;
        stick.setSize(Vector2f(100, car_h));
        stick.setStatus('o');
        stick.setPosition(0, gameWindow_h - 800 + 10);
        stick.setTexture(&logg[n % 5]);
        sticks2.push_back(stick);
    }

    for (int i = 0; i < 3; i++)
    {
        int n = rand();
        Stick stick;
        stick.setSize(Vector2f(100, car_h));
        stick.setStatus('o');
        stick.setPosition(0, gameWindow_h - 900 + 10);
        stick.setTexture(&logg[n % 5]);
        sticks3.push_back(stick);
    }

    for (int i = 0; i < 3; i++)
    {
        int n = rand();
        Stick stick;
        stick.setSize(Vector2f(100, car_h));
        stick.setStatus('o');
        stick.setPosition(0, gameWindow_h - 1000 + 10);
        stick.setTexture(&logg[n % 5]);
        sticks4.push_back(stick);
    }

    //startWindowBackground
    RectangleShape rectStartGame;
    rectStartGame.setSize(Vector2f(450, 150));
    rectStartGame.setPosition(Vector2f((startWindow_w - 450) / 2, 600));
    rectStartGame.setFillColor(Color::Black);
    rectStartGame.setOutlineColor(Color::White);
    rectStartGame.setOutlineThickness(3);
    RectangleShape rectExitGame;
    rectExitGame.setSize(Vector2f(450, 150));
    rectExitGame.setPosition(Vector2f((startWindow_w - 450) / 2, 800));
    rectExitGame.setFillColor(Color::Black);
    rectExitGame.setOutlineColor(Color::White);
    rectExitGame.setOutlineThickness(3);
    Font titleFont;
    titleFont.loadFromFile("Fonts/title.ttf");
    Font font;
    font.loadFromFile("Fonts/normal.otf");
    Text txtTitle;
    txtTitle.setFont(titleFont);
    txtTitle.setString("FROGGER");
    txtTitle.setPosition(200, 100);
    txtTitle.setFillColor(Color::Blue);
    txtTitle.setCharacterSize(116);
    Text txtStatus;
    txtStatus.setFont(font);
    txtStatus.setString("");
    txtStatus.setPosition(280, 335);
    txtStatus.setCharacterSize(54);
    txtStatus.setStyle(Text::Underlined);
    txtStatus.setFillColor(sf::Color::White);
    Text txtStart;
    txtStart.setFont(font);
    txtStart.setString("Start");
    txtStart.setPosition(270, 645);
    txtStart.setCharacterSize(54);
    txtStart.setFillColor(sf::Color::White);
    Text txtExit;
    txtExit.setFont(font);
    txtExit.setString("Exit");
    txtExit.setPosition(295, 845);
    txtExit.setCharacterSize(54);
    txtExit.setFillColor(sf::Color::White);
    //startWindowBackground

    //gameWindowBackground
    RectangleShape player;
    Texture frog[4];
    char const *frogFilesName[] = {"Images/frogt.png", "Images/frogr.png", "Images/frogd.png", "Images/frogl.png"};
    for (int i = 0; i < 4; i++)
    {
        frog[i].loadFromFile(frogFilesName[i]);
    }
    player.setTexture(&frog[0]);
    player.setSize(Vector2f(player_w, player_h));
    player.setPosition((gameWindow_w - player_w) / 2, gameWindow_h - player_h - 15);

    Texture checkedl;
    Sprite checkedline;
    if (!checkedl.loadFromFile("Images/beach1.jpg"))
        cout << "Failed loading";
    checkedline.setTexture(checkedl); //checked line pos 0
    checkedline.setPosition(0, 500);

    Texture checkel1;
    Sprite checkel1ine;
    if (!checkel1.loadFromFile("Images/checked.jpg"))
        cout << "Failed loading";
    checkel1ine.setTexture(checkel1); //beach line pos 500
    checkel1ine.setPosition(0, 0);

    Texture taroad100;
    Sprite aroad100;
    if (!taroad100.loadFromFile("Images/aroad.jpg"))
        cout << "Failed loading";
    aroad100.setTexture(taroad100); //road 600
    aroad100.setPosition(0, 600);

    Texture taroad200;
    Sprite aroad200;
    if (!taroad200.loadFromFile("Images/aroad200.jpg"))
        cout << "Failed loading";
    aroad200.setTexture(taroad200); //road 700
    aroad200.setPosition(0, 700);

    Texture taroad300;
    Sprite aroad300;
    if (!taroad300.loadFromFile("Images/aroad.jpg"))
        cout << "Failed loading";
    aroad300.setTexture(taroad300); //road8 800
    aroad300.setPosition(0, 800);

    Texture taroad400;
    Sprite aroad400;
    if (!taroad400.loadFromFile("Images/aroad200.jpg"))
        cout << "Failed loading";
    aroad400.setTexture(taroad400); //road 900
    aroad400.setPosition(0, 900);

    Texture tsea1;
    Sprite sea1;
    if (!tsea1.loadFromFile("Images/rivertop.jpg"))
        cout << "Failed loading";
    sea1.setTexture(tsea1); //road100
    sea1.setPosition(0, 0);

    Texture tsea2;
    Sprite sea2;
    if (!tsea2.loadFromFile("Images/riverbottom.jpg"))
        cout << "Failed loading";
    sea2.setTexture(tsea2); //road100
    sea2.setPosition(0, 300);
    //gameWindowBackground

    std::thread thread_set_cars(&createNewCarSet, ref(cars));
    std::thread thread_set_sticks1(&createNewStickLine1, ref(sticks1));
    std::thread thread_set_sticks2(&createNewStickLine2, ref(sticks2));
    std::thread thread_set_sticks3(&createNewStickLine3, ref(sticks3));
    std::thread thread_set_sticks4(&createNewStickLine4, ref(sticks4));
    std::thread thread_move_cars(&moveCars, ref(cars));
    std::thread thread_move_sticks(&moveSticks, ref(sticks1), ref(sticks2), ref(sticks3), ref(sticks4), &player);
   
    int c = 0;
    bool isGameStarted = 0;
    while (startWindow.isOpen())
    {

        Event startEvent;
        while (startWindow.pollEvent(startEvent))
        {
            if (startEvent.type == Event::Closed)
            {
                startWindow.close();
            }
            if (startEvent.type == Event::MouseButtonReleased)
            {
                if (startEvent.mouseButton.button == sf::Mouse::Left)
                {
                    if ((startEvent.mouseButton.x >= 125 && startEvent.mouseButton.x <= 575) && (startEvent.mouseButton.y >= 600 && startEvent.mouseButton.y <= 750))
                    {
                        //startButton
                        gameWindow.create(sf::VideoMode(gameWindow_w, gameWindow_h), "SFML works!");
                        resetGame(player);
                        isGameStarted = 1;
                        txtStatus.setString("");
                    }
                    if ((startEvent.mouseButton.x >= 125 && startEvent.mouseButton.x <= 575) && (startEvent.mouseButton.y >= 800 && startEvent.mouseButton.y <= 950))
                    {
                        //exitButton
                        exit(0);
                    }
                }
            }
        }

        if (isGameStarted == 1)
        {
            Event gameEvent;
            while (gameWindow.pollEvent(gameEvent))
            {
                if (gameEvent.type == Event::Closed)
                {
                    txtStatus.setString("");
                    gameWindow.close();
                }
                if (gameEvent.type == Event::KeyReleased)
                {
                    if (gameEvent.key.code == sf::Keyboard::Up)
                    {
                        if (player.getPosition().y != 15)
                        {
                            player.move(0, -100);
                            player.setTexture(&frog[0]);
                        }
                    }
                    if (gameEvent.key.code == sf::Keyboard::Down)
                    {
                        if (player.getPosition().y != gameWindow_h - player_h - 15)
                        {
                            player.move(0, 100);
                            player.setTexture(&frog[2]);
                        }
                    }
                    if (gameEvent.key.code == sf::Keyboard::Right)
                    {
                        if (gameWindow_w - 5 - (player.getPosition().x + player_w) < 100)
                        {
                            player.move(gameWindow_w - 5 - (player.getPosition().x + player_w), 0);
                        }
                        else
                        {
                            player.move(100, 0);
                        }
                        player.setTexture(&frog[1]);
                    }
                    if (gameEvent.key.code == sf::Keyboard::Left)
                    {
                        if (player.getPosition().x - 5 < 100)
                        {
                            player.move(-(player.getPosition().x - 5), 0);
                        }
                        else
                        {
                            player.move(-100, 0);
                        }
                        player.setTexture(&frog[3]);
                    }
                }
            }

            for (int i = 0; i < carsCount; i++)
            {
                if (cars[i].getStatus() == 'i')
                {
                    if ((((player.getPosition().x <= cars[i].getPosition().x) && (player.getPosition().x + player_w - cars[i].getPosition().x >= 0)) ||
                         ((player.getPosition().x >= cars[i].getPosition().x) && (cars[i].getPosition().x + car_w - player.getPosition().x >= 0))) &&
                        (((player.getPosition().y <= cars[i].getPosition().y) && (player.getPosition().y + player_h - cars[i].getPosition().y >= 0)) ||
                         ((player.getPosition().y >= cars[i].getPosition().y) && (cars[i].getPosition().y + car_h - player.getPosition().y >= 0))))
                    {
                        //accident
                        gameSituation = 1;
                        break;
                    }
                }
            }

            gameWindow.clear();
            gameWindow.draw(checkedline);
            gameWindow.draw(checkel1ine);
            gameWindow.draw(aroad100);
            gameWindow.draw(aroad200);
            gameWindow.draw(aroad300);
            gameWindow.draw(aroad400);
            gameWindow.draw(sea1);
            gameWindow.draw(sea2);

            for (int i = 0; i < carsCount; i++)
            {
                if (cars[i].getStatus() == 'i')
                {
                    gameWindow.draw(cars[i]);
                }
            }
            for (int i = 0; i < 3; i++)
            {
                if (sticks1[i].getStatus() == 'i')
                {
                    gameWindow.draw(sticks1[i]);
                }
            }
            for (int i = 0; i < 3; i++)
            {
                if (sticks2[i].getStatus() == 'i')
                {
                    gameWindow.draw(sticks2[i]);
                }
            }
            for (int i = 0; i < 3; i++)
            {
                if (sticks3[i].getStatus() == 'i')
                {
                    gameWindow.draw(sticks3[i]);
                }
            }
            for (int i = 0; i < 3; i++)
            {
                if (sticks4[i].getStatus() == 'i')
                {
                    gameWindow.draw(sticks4[i]);
                }
            }
            gameWindow.draw(player);
            gameWindow.display();

            if (gameSituation == 1)
            {
                SoundBuffer buffer;
                Sound accident;

                buffer.loadFromFile("Audios/accident.wav");
                accident.setBuffer(buffer);
                accident.play();
                sleep(sf::milliseconds(1100));
                gameWindow.close();
                isGameStarted = 0;
                txtStatus.setPosition(200, 370);
                txtStatus.setString("YOU LOST!");
            }
            if (gameSituation == 2)
            {
                SoundBuffer buffer;
                Sound drop;

                buffer.loadFromFile("Audios/drop.wav");
                drop.setBuffer(buffer);
                drop.play();
                sleep(sf::milliseconds(1100));
                gameWindow.close();
                isGameStarted = 0;
                txtStatus.setPosition(200, 370);
                txtStatus.setString("YOU LOST!");
            }
            if (player.getPosition().y == 15)
            {
                //player won
                sleep(sf::milliseconds(1100));
                gameWindow.close();
                isGameStarted = 0;
                txtStatus.setPosition(210, 370);
                txtStatus.setString("YOU WON!");
            }
        }

        startWindow.clear();
        startWindow.draw(rectStartGame);
        startWindow.draw(rectExitGame);
        startWindow.draw(txtTitle);
        startWindow.draw(txtStatus);
        startWindow.draw(txtStart);
        startWindow.draw(txtExit);
        startWindow.display();
    }

    return 0;
}
