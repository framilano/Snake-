#include "headers/scenes.hpp"

void welcome_scene(sf::RenderWindow &window, sf::RectangleShape &background, sf::Font &eightbit_font, int &chosen_difficulty) {
    
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
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::O) options_scene(window, background, eightbit_font, chosen_difficulty);
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
    lost_msg.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGHT*0.5));
    window.draw(lost_msg);
    window.display();
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R) return 0;
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) return 1;
    }
    window.clear();
    return 0;
}

void create_radios(tgui::Gui &gui, sf::Font &eightbit_font, int &chosen_difficulty, std::vector<tgui::RadioButton::Ptr> &radio_vector) {
    tgui::Layout2d layout(sf::Vector2f(20, 20));
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
    switch (chosen_difficulty) {
        case 0:
        option0->setChecked(true);
        break;
        case 1:
        option1->setChecked(true);
        break;
        case 2:
        option2->setChecked(true);
        break;
        case 3:
        option3->setChecked(true);
        break;
    }
    gui.add(option0);
    gui.add(option1);
    gui.add(option2);
    gui.add(option3);
    radio_vector[0] = option0;
    radio_vector[1] = option1;
    radio_vector[2] = option2;
    radio_vector[3] = option3;
    return;
}

int check_difficulty() {
    std::fstream difficulty_file;
    difficulty_file.open(CONFIGS_FD + "difficulty.txt", std::ios::out | std::ios::in);
    if (difficulty_file.fail()) {
        std::cout << "Non esiste difficulty.txt\n";
        difficulty_file.close();
        difficulty_file.open(CONFIGS_FD + "difficulty.txt", std::fstream::out);
        difficulty_file << "0";
        difficulty_file.close();
        return 0;
    }
    std::string saved_difficulty;
    difficulty_file >> saved_difficulty;
    difficulty_file.close();
    return std::stoi(saved_difficulty);
}

void update_difficulty_file(int &i) {
    std::fstream difficulty_file;
    difficulty_file.open(CONFIGS_FD + "difficulty.txt", std::fstream::out | std::fstream::trunc);
    difficulty_file << std::to_string(i);
    difficulty_file.close();
    return;
}

void check_radios(tgui::Gui &gui, std::vector<tgui::RadioButton::Ptr> &radio_vector) {
    for (int i = 0; i < 4; i++) {
        if (radio_vector[i]->isChecked() == true) update_difficulty_file(i);
    }
    return;
}

void options_scene(sf::RenderWindow &window, sf::RectangleShape &background, sf::Font &eightbit_font, int &chosen_difficulty) {
    chosen_difficulty = check_difficulty();
    
    tgui::Gui gui(window); // Create the gui and attach it to the window
    sf::Text options_msg("Options", eightbit_font, 70);
    sf::Text difficulty_msg("Difficulty", eightbit_font, 50);

    //setting title
    options_msg.setOrigin(sf::Vector2f(options_msg.getLocalBounds().width/2, options_msg.getLocalBounds().height/2));
    options_msg.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGHT*0.1));
    //Setting difficulty title
    difficulty_msg.setOrigin(sf::Vector2f(difficulty_msg.getLocalBounds().width/2, difficulty_msg.getLocalBounds().height/2));
    difficulty_msg.setPosition(sf::Vector2f(WIN_WIDTH/4, WIN_HEIGHT*0.2));
    
    //Creating radiobuttons and saving their pointers inside a vector
    std::vector<tgui::RadioButton::Ptr> radio_vector(4);
    create_radios(gui, eightbit_font, chosen_difficulty, radio_vector);

    bool exit_options = false;
    while (window.isOpen())
    {
        sf::Event event;
        window.clear();
        window.draw(background);
        window.draw(options_msg);
        window.draw(difficulty_msg);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) exit_options = true;
            gui.handleEvent(event); // Pass the event to the widgets
        }
        if(exit_options) break;
        gui.draw(); // Draw all widgets
        window.display();
    }
    check_radios(gui, radio_vector);
}

void win_scene(sf::RenderWindow &window, sf::Font &eightbit_font) {
    window.display();
    sf::Event event;
    sf::Text win_msg("You won!", eightbit_font, 100);
    win_msg.setOrigin(sf::Vector2f(win_msg.getLocalBounds().width/2, win_msg.getLocalBounds().height/2));
    win_msg.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGHT*0.3));
    window.draw(win_msg);
    window.display();
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) window.close();
    }
    window.clear();
    return;
}