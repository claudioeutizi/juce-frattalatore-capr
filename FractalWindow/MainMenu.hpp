#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;
using namespace sf;

#define Max_main_menu 5

class MainMenu{
    
public:
    MainMenu(float width, float height);
    ~MainMenu();

    void draw(RenderWindow& window);
    void MoveUp();
    void MoveDown();
    
    int MainMenuPressed() {
        return MainMenuSelected;
    }
    
    
private:
    int MainMenuSelected;
    sf::Font font;
    sf::Text mainMenu[Max_main_menu];
    
};
