#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>


#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
#define GF_LENGTH 700
#define PG_LENGTH 70
#define POS 10

void welcome_scene(sf::RenderWindow &window, sf::RectangleShape &background, sf::Font &eightbit_font);

void pause_scene(sf::RenderWindow &window, sf::Music &astro_music, sf::Font &eightbit_font);

int lost_scene(sf::RenderWindow &window, sf::Music &astro_music, sf::Font &eightbit_font, 
 std::vector<sf::Sprite> &character, int &score_int, sf::Text &score);
