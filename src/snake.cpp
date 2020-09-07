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

void check_boundaries(sf::Sprite &character) {
    if (character.getPosition().x < WIN_WIDTH/2 - GF_LENGTH/2) character.move(GF_LENGTH, 0);
    if (character.getPosition().x > WIN_WIDTH/2 + GF_LENGTH/2) character.move(-GF_LENGTH, 0);
    if (character.getPosition().y < WIN_HEIGHT/2 - GF_LENGTH/2) character.move(0, GF_LENGTH);
    if (character.getPosition().y > WIN_HEIGHT/2 + GF_LENGTH/2) character.move(0, -GF_LENGTH);
    return;
}

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

void add_life(std::vector<sf::Sprite> &character, sf::Texture &char_texture, sf::Text &record, int &record_int, int &score_int, sf::Sound &hit_sound) {
    hit_sound.play();
    sf::Sprite new_piece;
    new_piece.setOrigin(PG_LENGTH/2, PG_LENGTH/2);
    new_piece.setTexture(char_texture);
    new_piece.setPosition(sf::Vector2f(-PG_LENGTH/2, -PG_LENGTH/2));
    character.push_back(new_piece);
    if (score_int > record_int) {
        record_int = score_int;
        record.setString("Record: " + std::to_string(record_int));
    }
    return;
}

void update_charpositions(std::vector<sf::Sprite> &character) {
    for(int i = character.size() - 1; i > 0; i--) {
        character[i].setPosition(character[i-1].getPosition());
        character[i].setRotation(character[i-1].getRotation());
    }
    return;
}

bool check_collision(std::vector<sf::Sprite> &character) {
    for (int i = 1; i < character.size(); i++) {
        if (character.front().getPosition() == character[i].getPosition()) return true;
    }
    return false;
}


void restart_game(std::vector<sf::Sprite> &character, int &score_int, sf::Text &score) {
    score_int = 0;
    score.setString("Score: " + std::to_string(score_int));
    character.erase(character.begin()+1, character.begin() + character.size());
}

int parse_record() {
    std::fstream record_file;
    record_file.open("record.txt", std::ios::out | std::ios::in);
    if(record_file.fail()) {
        std::cout << "Non esiste record.txt\n";
        record_file.close();
        record_file.open("record.txt", std::fstream::out);
        record_file << "0";
        record_file.close();
        return 0;
    }
    std::string saved_record;
    record_file >> saved_record;
    record_file.close();
    return std::stoi(saved_record);
}

void update_record(int &record_int) {
    std::fstream record_file;
    record_file.open("record.txt", std::fstream::out | std::fstream::trunc);
    record_file << std::to_string(record_int);
    record_file.close();
    return;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "SnakePlusPlus");
    sf::RectangleShape background(sf::Vector2f(WIN_WIDTH, WIN_HEIGHT));
    sf::RectangleShape gamefield(sf::Vector2f(GF_LENGTH, GF_LENGTH));
    sf::Texture background_texture;
    sf::Texture char_texture;
    sf::Texture food_texture;
    sf::Font roboto_font;

    //Parsing and setting record from record.txt
    sf::Text score("Score: 0", roboto_font, 50);
    sf::Text record("", roboto_font, 50);
    int score_int = 0;
    int record_int = parse_record();
    record.setString("Record: " + std::to_string(record_int));
    std::vector<sf::Sprite> character(1);
    sf::Sprite food;

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
    char_texture.loadFromFile("../assets/kiss.png");
    char_texture.setSmooth(true);
    character.front().setOrigin(PG_LENGTH/2, PG_LENGTH/2);
    character.front().setTexture(char_texture);
    character.front().setPosition(sf::Vector2f(WIN_WIDTH/2 - GF_LENGTH/2 + PG_LENGTH/2, WIN_HEIGHT/2 - GF_LENGTH/2 + PG_LENGTH/2));
    //std::cout << character.getGlobalBounds().height << character.getGlobalBounds().width;

    //Food
    food_texture.loadFromFile("../assets/apple.png");
    food_texture.setSmooth(true);
    food.setOrigin(PG_LENGTH/2, PG_LENGTH/2);
    food.setTexture(food_texture);
    food.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGHT/2));
    

    //Background&Gamefield
    background_texture.loadFromFile("../assets/background.jpg");
    roboto_font.loadFromFile("../assets/roboto.ttf");
    background.setTexture(&background_texture);
    gamefield.setFillColor(sf::Color::Black);
    gamefield.setOrigin(GF_LENGTH/2, GF_LENGTH/2);
    gamefield.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGHT/2));

    //Score&Record
    score.setPosition(sf::Vector2f(30, 30));
    record.setPosition(sf::Vector2f(30, 90));
    
    //Generating food positions and spawning the first apple
    std::vector<std::vector<sf::Vector2f>> food_positions = generate_food_positions();
    spawn_apple(food_positions, character, food);

    while (window.isOpen()) {
        sf::sleep(sf::seconds(0.25));
        sf::Event event;
        int current_rotation = 0;

        update_charpositions(character);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) window.close();
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right) {character.front().rotate(90);break;}
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left) {character.front().rotate(-90);break;}
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R) {
                astro_music.stop();
                astro_music.play();
                update_record(record_int);
                restart_game(character, score_int, score);
            }
            //std::cout << character.getPosition().x << "\t" << character.getPosition().y  << "\n";
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
        
        //std::cout << food.getPosition().x << "\t" << food.getPosition().y << "\n" << character.getPosition().x << "\t" << character.getPosition().y << "\n\n";
        //Spawn apple
        if ((food.getPosition().x == character.front().getPosition().x) && (food.getPosition().y == character.front().getPosition().y)){
            spawn_apple(food_positions, character, food);
            score_int += 1;
            score.setString("Score: " + std::to_string(score_int));
            add_life(character, char_texture, record, record_int, score_int, hit_sound);
        }

        if(check_collision(character)) {
            astro_music.stop();
            astro_music.play();
            update_record(record_int);
            restart_game(character, score_int, score);
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