#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <TGUI/Widgets/RadioButton.hpp>
#include <TGUI/Layout.hpp>
#include <TGUI/TGUI.hpp>
#include "headers/scenes.hpp"

void welcome_scene(sf::RenderWindow &window, sf::RectangleShape &background, sf::Font &eightbit_font) {
    
    sf::Text title_msg("SnakePlusPlus", eightbit_font, 100);
    sf::Text enter_msg("Press Enter to play\nPress O for options\nPress ESC to exit", eightbit_font, 70);
    title_msg.setOrigin(sf::Vector2f(title_msg.getLocalBounds().width/2, title_msg.getLocalBounds().height/2));
    title_msg.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGHT*0.1));
    enter_msg.setOrigin(sf::Vector2f(enter_msg.getLocalBounds().width/2, enter_msg.getLocalBounds().height/2));
    enter_msg.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGHT*0.5));
    int start_game = 0;
    while(window.isOpen()) {
        sf::Event event;
        window.draw(background);
        window.draw(enter_msg);
        window.draw(title_msg);
        window.display();
        while (window.waitEvent(event)) {
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) window.close();
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::O) options_scene(window, background, eightbit_font);
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) start_game = 1;
            break;  
        }
        if (start_game) break;
    }
    
}

void pause_scene(sf::RenderWindow &window, sf::Music &astro_music, sf::Font &eightbit_font) {
    window.display();
    astro_music.pause();
    sf::Event event;
    sf::Text pause_msg("Pause", eightbit_font, 100);
    pause_msg.setOrigin(sf::Vector2f(pause_msg.getLocalBounds().width/2, pause_msg.getLocalBounds().height/2));
    pause_msg.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGHT*0.3));
    window.draw(pause_msg);
    window.display();
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P) break;
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) window.close();
    }
    window.clear();
    astro_music.play();
    return;
}

int lost_scene(sf::RenderWindow &window, sf::Music &astro_music, sf::Font &eightbit_font, 
 std::vector<sf::Sprite> &character, int &score_int, sf::Text &score) {
    window.display();
    astro_music.pause();
    sf::Event event;
    sf::Text lost_msg("You lost\n\nPress R to retry or ESC to exit", eightbit_font, 50);
    lost_msg.setOrigin(sf::Vector2f(lost_msg.getLocalBounds().width/2, lost_msg.getLocalBounds().height/2));
    lost_msg.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGHT*0.3));
    window.draw(lost_msg);
    window.display();
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R) return 0;
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) return 1;
    }
    window.clear();
    return 0;
}

void create_radios(tgui::Gui &gui, sf::Font &eightbit_font) {
    tgui::Layout2d layout(sf::Vector2f(30, 30));
    sf::String option0text("Easy");
    sf::String option1text("Medium");
    sf::String option2text("Hard");
    sf::String option3text("Extreme");
    tgui::RadioButton::Ptr option0 = tgui::RadioButton::create();
    tgui::RadioButton::Ptr option1 = tgui::RadioButton::create();
    tgui::RadioButton::Ptr option2 = tgui::RadioButton::create();
    tgui::RadioButton::Ptr option3 = tgui::RadioButton::create();
    option0->setText(option0text);
    option1->setText(option1text);
    option2->setText(option2text);
    option3->setText(option3text);
    option0->setPosition(WIN_WIDTH*0.2, WIN_HEIGHT*0.3);
    option1->setPosition(WIN_WIDTH*0.2, WIN_HEIGHT*0.4);
    option2->setPosition(WIN_WIDTH*0.2, WIN_HEIGHT*0.5);
    option3->setPosition(WIN_WIDTH*0.2, WIN_HEIGHT*0.6);
    option0->setSize(layout);
    option1->setSize(layout);
    option2->setSize(layout);
    option3->setSize(layout);
    option0->setTextSize(30);
    option1->setTextSize(30);
    option2->setTextSize(30);
    option3->setTextSize(30);
    gui.add(option0);
    gui.add(option1);
    gui.add(option2);
    gui.add(option3);
    return;
}

void options_scene(sf::RenderWindow &window, sf::RectangleShape &background, sf::Font &eightbit_font) {
    window.clear();
    tgui::Gui gui{window}; // Create the gui and attach it to the window

    //setting title
    sf::Text options_msg("Options", eightbit_font, 70);
    options_msg.setOrigin(sf::Vector2f(options_msg.getLocalBounds().width/2, options_msg.getLocalBounds().height/2));
    options_msg.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGHT*0.1));
    //Setting difficulty title
    sf::Text difficulty_msg("Difficulty", eightbit_font, 50);
    difficulty_msg.setOrigin(sf::Vector2f(difficulty_msg.getLocalBounds().width/2, difficulty_msg.getLocalBounds().height/2));
    difficulty_msg.setPosition(sf::Vector2f(WIN_WIDTH/4, WIN_HEIGHT*0.2));
    
    //Creating radiobuttons
    create_radios(gui, eightbit_font);
    int exit_options = 0;
    while (window.isOpen())
    {
        sf::Event event;
        window.draw(background);
        window.draw(options_msg);
        window.draw(difficulty_msg);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) exit_options = 1;
            gui.handleEvent(event); // Pass the event to the widgets
        }
        if(exit_options) break;
        gui.draw(); // Draw all widgets
        window.display();
    }
}