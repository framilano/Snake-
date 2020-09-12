#ifndef SCENES_HPP
#define SCENES_HPP


#include <TGUI/Widgets/RadioButton.hpp>
#include <TGUI/Layout.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>


#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
#define GF_LENGTH 700
#define POS 10
#define PG_LENGTH GF_LENGTH/POS

#ifdef _WIN32
const std::string ASSETS_FD = "assets\\";
const std::string CONFIGS_FD = "configs\\";
#endif

#ifdef __linux__
const std::string ASSETS_FD = "assets/";
const std::string CONFIGS_FD = "configs/";
#endif

//Spawn welcome scene and wait for events to launch the game, exit or launch options
void welcome_scene(sf::RenderWindow &window, sf::RectangleShape &background, sf::Font &eightbit_font, int &chosen_difficulty);

void pause_scene(sf::RenderWindow &window, sf::Music &astro_music, sf::Font &eightbit_font);

int lost_scene(sf::RenderWindow &window, sf::Music &astro_music, sf::Font &eightbit_font, 
 std::vector<sf::Sprite> &character, int &score_int, sf::Text &score);

void create_radios(tgui::Gui &gui, sf::Font &eightbit_font, int &chosen_difficulty);

int check_difficulty();

void update_difficulty_file(int &i);

void check_radios(tgui::Gui &gui, std::vector<tgui::RadioButton::Ptr> &radio_vector);

void options_scene(sf::RenderWindow &window, sf::RectangleShape &background, sf::Font &eightbit_font, int &chosen_difficulty);

void win_scene(sf::RenderWindow &window, sf::Font &eightbit_font);
#endif