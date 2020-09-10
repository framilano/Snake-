#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "scenes.h"

/**
* Checking and teleporting the player if he goes over game field limits
*  @param character first element of the character array 
*/
void check_boundaries(sf::Sprite &character) {
    if (character.getPosition().x < WIN_WIDTH/2 - GF_LENGTH/2) character.move(GF_LENGTH, 0);
    if (character.getPosition().x > WIN_WIDTH/2 + GF_LENGTH/2) character.move(-GF_LENGTH, 0);
    if (character.getPosition().y < WIN_HEIGHT/2 - GF_LENGTH/2) character.move(0, GF_LENGTH);
    if (character.getPosition().y > WIN_HEIGHT/2 + GF_LENGTH/2) character.move(0, -GF_LENGTH);
    return;
}

/**
*   Generates possible food position in a matric of sf::Vector2f
*   @return the matrix
**/
std::vector<std::vector<sf::Vector2f>> generate_food_positions() {
    std::vector<std::vector<sf::Vector2f>> positions_matrix(10, std::vector<sf::Vector2f>(10));
    int begin_x = WIN_WIDTH/2 - GF_LENGTH/2 + PG_LENGTH/2;
    int begin_y = WIN_HEIGHT/2 - GF_LENGTH/2 + PG_LENGTH/2;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            positions_matrix[i][j].x = begin_x + j*PG_LENGTH;
            positions_matrix[i][j].y = begin_y + i*PG_LENGTH;
        }
    }
    return positions_matrix;
}

/**
*   Search for an empty space inside the matrix, comparing current character locations and food positions, if an empty space is found food spawns
*   @param food_positions possible food positions
*   @param character character vector
    @param food the food sprite to spawn
**/
void spawn_apple(std::vector<std::vector<sf::Vector2f>> &food_positions, std::vector<sf::Sprite> &character, sf::Sprite &food) {
    srand (time(NULL));
    bool empty = false;
    int poss_x = 0;
    int poss_y = 0;
    while (empty == false) {
        poss_x = rand() % POS;
        poss_y = rand() % POS;
        empty = true;
        for (int i = 0; i < character.size(); i++) {
            if (food_positions[poss_x][poss_y] == character[i].getPosition()) empty = false;
        }
    }
    food.setPosition(food_positions[poss_x][poss_y]);
    return;
}

/**
*   Adding a new element to the character array, updating score and record, reproducing the hit sound too
*   @param  character character vector
*   @param  char_texture character texture to apply 
*   @param  record sf::Text to update eventually
*   @param  record_int current record int variable
*   @param  score sf::Text with Score text inside
*   @param  score_int current score int variable
*   @param  hit_sound sf::Sound with hit sound inside
**/
void increase_score(std::vector<sf::Sprite> &character, sf::Text &record, int &record_int,
 sf::Text &score, int &score_int, sf::Sound &hit_sound, sf::Texture &body_texture, sf::Texture &tail_texture) {
    hit_sound.play();
    score_int += 1;
    score.setString("Score  " + std::to_string(score_int));
    if (score_int > record_int) {
        record_int = score_int;
        record.setString("Record " + std::to_string(record_int));
    }

    for (int i = 1; i < character.size(); i++) character[i].setTexture(body_texture);

    sf::Sprite new_piece;
    new_piece.setOrigin(PG_LENGTH/2, PG_LENGTH/2);
    new_piece.setTexture(tail_texture);
    new_piece.setPosition(sf::Vector2f(-PG_LENGTH/2, -PG_LENGTH/2));
    character.push_back(new_piece);
    return;
}

/**
* At every tick, character positions get updated, from the bottom the top
*   @param character character vector
**/
void update_charpositions(std::vector<sf::Sprite> &character) {
    for(int i = character.size() - 1; i > 0; i--) {
        character[i].setPosition(character[i-1].getPosition());
        character[i].setRotation(character[i-1].getRotation());
    }
    return;
}


/**
* Checking if character front (head) hit his body
*   @param character character vector
*   @return true if hit, false if not
**/
bool check_collision(std::vector<sf::Sprite> &character) {
    for (int i = 1; i < character.size(); i++) {
        if (character.front().getPosition() == character[i].getPosition()) return true;
    }
    return false;
}

/**
* Resetting character vector to one element, resetting score and restarting music
*   @param character character vector
*   @param score_int current score int variable
*   @param score sf::Text with Score text inside
*   @param astro_music sf::Music with game music
**/
void restart_game(std::vector<sf::Sprite> &character, int &score_int, sf::Text &score, sf::Music &astro_music) {
    astro_music.stop();
    astro_music.play();
    score_int = 0;
    score.setString("Score  " + std::to_string(score_int));
    character.erase(character.begin() + 1, character.begin() + character.size());
}

/**
*   Parsing record from record.txt
*   @return current record saved
*
**/
int parse_record() {
    std::fstream record_file;
    record_file.open("../configs/record.txt", std::ios::out | std::ios::in);
    if(record_file.fail()) {
        std::cout << "Non esiste record.txt\n";
        record_file.close();
        record_file.open("../configs/record.txt", std::fstream::out);
        record_file << "0";
        record_file.close();
        return 0;
    }
    std::string saved_record;
    record_file >> saved_record;
    record_file.close();
    return std::stoi(saved_record);
}

/**
* Updating record.txt at the end of the match
* @param record_int integer record variable
**/
void update_record(int &record_int) {
    std::fstream record_file;
    record_file.open("../configs/record.txt", std::fstream::out | std::fstream::trunc);
    record_file << std::to_string(record_int);
    record_file.close();
    return;
}


int main() {

    //Window, background and font
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "SnakePlusPlus", sf::Style::Default);
    sf::RectangleShape background(sf::Vector2f(WIN_WIDTH, WIN_HEIGHT));
    sf::Texture background_texture;
    sf::Font eightbit_font;
    eightbit_font.loadFromFile("../assets/8bitwonder.ttf");
    background_texture.loadFromFile("../assets/background.jpg");
    background.setTexture(&background_texture);

    welcome_scene(window, background, eightbit_font);

    //Background&Gamefield
    sf::RectangleShape gamefield(sf::Vector2f(GF_LENGTH, GF_LENGTH));
    gamefield.setFillColor(sf::Color::Black);
    gamefield.setOrigin(GF_LENGTH/2, GF_LENGTH/2);
    gamefield.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGHT/2));

    //Parsing and setting record from record.txt
    sf::Text score("Score  0", eightbit_font, 50);
    sf::Text record("", eightbit_font, 50);
    int score_int = 0;
    int record_int = parse_record();
    record.setString("Record  " + std::to_string(record_int));
    

    //Sound&Music
    sf::SoundBuffer buffer;
    buffer.loadFromFile("../assets/hitmarker.wav");
    sf::Sound hit_sound;
    hit_sound.setBuffer(buffer);
    sf::Music astro_music;
    astro_music.openFromFile("../assets/astronomia.wav");
    astro_music.play();
    astro_music.setLoop(true);

    //Character
    sf::Texture tail_texture;
    sf::Texture body_texture;
    sf::Texture char_texture;
    sf::Texture food_texture;
    std::vector<sf::Sprite> character(1);
    sf::Sprite food;
    char_texture.loadFromFile("../assets/head.png");
    char_texture.setSmooth(true);
    character.front().setOrigin(PG_LENGTH/2, PG_LENGTH/2);
    body_texture.loadFromFile("../assets/body.png");
    body_texture.setSmooth(true);
    tail_texture.loadFromFile("../assets/tail.png");
    tail_texture.setSmooth(true);
    character.front().setTexture(char_texture);
    character.front().setPosition(sf::Vector2f(WIN_WIDTH/2 - GF_LENGTH/2 + PG_LENGTH/2, WIN_HEIGHT/2 - GF_LENGTH/2 + PG_LENGTH/2));

    //Food
    food_texture.loadFromFile("../assets/apple.png");
    food_texture.setSmooth(true);
    food.setOrigin(PG_LENGTH/2, PG_LENGTH/2);
    food.setTexture(food_texture);


    //Score&Record
    score.setPosition(sf::Vector2f(30, 30));
    record.setPosition(sf::Vector2f(30, 90));
    
    //Generating food positions and spawning the first apple
    std::vector<std::vector<sf::Vector2f>> food_positions = generate_food_positions();
    spawn_apple(food_positions, character, food);

    //Defining first character rotation, useful to decide where to move the character sprite
    int current_rotation = 0;

    while (window.isOpen()) {
        sf::sleep(sf::seconds(0.20));
        sf::Event event;

        update_charpositions(character);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) window.close();
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right) {character.front().rotate(90);break;}
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left) {character.front().rotate(-90);break;}
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P) pause_scene(window, astro_music, eightbit_font);
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R) {
                update_record(record_int);
                restart_game(character, score_int, score, astro_music);
            }
        }

        current_rotation = character.front().getRotation();

        switch (current_rotation) {
            case 0:
                character.front().move(0, -PG_LENGTH); 
                break;
            case 90:
                character.front().move(PG_LENGTH, 0); 
                break;
            case 180:
                character.front().move(0, PG_LENGTH); 
                break;
            case 270:
                character.front().move(-PG_LENGTH, 0); 
                break;
        }


        //Teleport char when exiting boundaries
        check_boundaries(character.front());
        
        //Spawn apple if hitting one
        if ((food.getPosition().x == character.front().getPosition().x) && (food.getPosition().y == character.front().getPosition().y)){
            spawn_apple(food_positions, character, food);
            increase_score(character, record, record_int, score, score_int, hit_sound, body_texture, tail_texture);
        }

        if(check_collision(character)) {
            update_record(record_int);
            if(lost_scene(window, astro_music, eightbit_font, character, score_int, score)) window.close();
            else restart_game(character, score_int, score, astro_music);
            
        }

        window.clear();
        window.draw(background);
        window.draw(gamefield);
        window.draw(score);
        window.draw(record);
        for(int i = 0; i < character.size(); i++) {
            window.draw(character[i]);
        }
        window.draw(food);
        window.display();
    }

    return 0;
}