

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include "scenes.h"

void welcome_scene(sf::RenderWindow &window, sf::RectangleShape &background, sf::Font &eightbit_font) {
    sf::Event event;
    sf::Text title_msg("SnakePlusPlus", eightbit_font, 100);
    sf::Text enter_msg("Press Enter to play\nPress ESC to exit", eightbit_font, 70);
    title_msg.setOrigin(sf::Vector2f(title_msg.getLocalBounds().width/2, title_msg.getLocalBounds().height/2));
    title_msg.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGHT*0.3));
    enter_msg.setOrigin(sf::Vector2f(enter_msg.getLocalBounds().width/2, enter_msg.getLocalBounds().height/2));
    enter_msg.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGHT/1.5));
    window.draw(background);
    window.draw(enter_msg);
    window.draw(title_msg);
    window.display();
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) window.close();
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Enter) break;
    }
}

void pause_scene(sf::RenderWindow &window, sf::Music &astro_music, sf::Font &eightbit_font) {
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