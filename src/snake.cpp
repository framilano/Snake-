#include <SFML/Graphics.hpp>
#include <iostream>

bool check_boundaries(sf::Sprite &character) {
    if (character.getPosition().x < 645 || character.getPosition().x > 1275 || character.getPosition().y < 205 || character.getPosition().y > 835) return true;
    else return false;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Primo test");
    sf::RectangleShape background(sf::Vector2f(1920, 1080));
    sf::RectangleShape gamefield(sf::Vector2f(700, 700));
    sf::Texture background_texture;
    sf::Texture char_texture;
    sf::Font roboto_font;
    sf::Text score("Score: ", roboto_font, 50);
    sf::Text record("Record: ", roboto_font, 50);
    sf::Sprite character;

    //Character    
    char_texture.loadFromFile("../assets/kiss.png");
    char_texture.setSmooth(true);
    character.setScale(0.1, 0.1);
    character.setOrigin(350, 350);
    character.setTexture(char_texture);
    character.setPosition(sf::Vector2f(645, 205));
    //std::cout << character.getGlobalBounds().height << character.getGlobalBounds().width;

    //Food

    //Background&Gamefield
    background_texture.loadFromFile("../assets/background.jpg");
    roboto_font.loadFromFile("../assets/roboto.ttf");
    background.setTexture(&background_texture);
    gamefield.setFillColor(sf::Color::Black);
    gamefield.setOrigin(350, 350);
    gamefield.setPosition(sf::Vector2f(960, 520));

    //Score&Record
    score.setPosition(sf::Vector2f(30, 30));
    record.setPosition(sf::Vector2f(1640, 30));
    
    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2f current_char_pos = character.getPosition();

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) window.close();

            if (event.key.code == sf::Keyboard::Up) {
                if (character.getRotation() == 0) character.move(sf::Vector2f(0, -35));
                else character.setRotation(0);
                
                //std::cout << "Up key was pressed";
            }
            if (event.key.code == sf::Keyboard::Down) {
                if (character.getRotation() == 180) character.move(sf::Vector2f(0, 35));
                else character.setRotation(180);
                //std::cout << "Down key was pressed";
            }
            if (event.key.code == sf::Keyboard::Right) {
                if (character.getRotation() == 90) character.move(sf::Vector2f(35, 0));
                else character.setRotation(90);
                //std::cout << "Right key was pressed";
            }
            if (event.key.code == sf::Keyboard::Left) {
                if (character.getRotation() == 270) character.move(sf::Vector2f(-35, 0));
                else character.setRotation(270);
                //std::cout << "Left key was pressed";
            }
            
            std::cout << character.getRotation() << "\n";
            //Block char from exiting the field
            if (!check_boundaries(character)) continue;
            else character.setPosition(current_char_pos);

            
        }

        

        window.clear();
        window.draw(background);
        window.draw(gamefield);
        window.draw(score);
        window.draw(record);
        window.draw(character);
        window.display();
    }

    return 0;
}