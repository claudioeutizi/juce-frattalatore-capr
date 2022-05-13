#include "MainMenu.hpp"


MainMenu::MainMenu(float width, float height){
    
    if(!font.loadFromFile("Font/sansation.ttf")){
        cout << "No font is here";
    }
    
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::White);
    mainMenu[0].setString("MANDELBROT");
    mainMenu[0].setCharacterSize(50);
    mainMenu[0].setPosition(50,50);
    //mainMenu[0].setRotation( 20.0);
    
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("JULIA 1");
    mainMenu[1].setCharacterSize(50);
    mainMenu[1].setPosition(50,150);
    
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("JULIA 2");
    mainMenu[2].setCharacterSize(50);
    mainMenu[2].setPosition(50,250);
    
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::White);
    mainMenu[3].setString("BURNING SHIP");
    mainMenu[3].setCharacterSize(50);
    mainMenu[3].setPosition(50,350);
    
    mainMenu[4].setFont(font);
    mainMenu[4].setFillColor(Color::White);
    mainMenu[4].setString("EXIT");
    mainMenu[4].setCharacterSize(50);
    mainMenu[4].setPosition(50,700);
    
    
    
    MainMenuSelected = -1;
}

MainMenu::~MainMenu(){
    
}

//Draw MainMenu
void MainMenu::draw(RenderWindow& window){
    for(int i=0; i<Max_main_menu; i++){
        window.draw(mainMenu[i]);
    }
}

//MoveUp
void MainMenu::MoveUp(){
    if(MainMenuSelected-1 >= 0){
        mainMenu[MainMenuSelected].setFillColor(Color::White);
        
        MainMenuSelected--;
        if(MainMenuSelected == -1){
            MainMenuSelected = 2;
        }
        mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    }
}

//MoveDown
void MainMenu::MoveDown(){
    if(MainMenuSelected+1 <= Max_main_menu){
        mainMenu[MainMenuSelected].setFillColor(Color::White);
        
        MainMenuSelected++;
        if(MainMenuSelected == 4){
            MainMenuSelected = 0;
        }
        mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    }
}
