#include <SFML/Graphics.hpp>
#include <iostream>



int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Primo test");
    sf::RectangleShape background(sf::Vector2f(1920, 1080));
    sf::Texture background_texture;
    sf::Font roboto_font;
    sf::Text score("Score: ", roboto_font, 50);
    sf::Text record("Record: ", roboto_font, 50);
    sf::Sprite character;

    //Character    
    character.setColor(sf::Color(255, 0, 0));
    character.setScale(sf::Vector2f(30, 30));
    character.setPosition(sf::Vector2f(960, 540));

    //Background
    background_texture.loadFromFile("../assets/background.jpg");
    roboto_font.loadFromFile("../assets/roboto.ttf");
    background.setTexture(&background_texture);

    //Score&Record
    score.setPosition(sf::Vector2f(30, 30));
    record.setPosition(sf::Vector2f(1640, 30));
    
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        window.draw(background);
        window.draw(score);
        window.draw(record);
        window.draw(character);
        window.display();
    }

    return 0;
}