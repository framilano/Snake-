
# Compiling: Ubuntu
You need SFML libraries, install them with:
sudo apt install libsfml-dev

Compile snakeplusplus with this command inside src/:
g++ snakeplusplus.cpp scenes.cpp headers/scenes.h -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o snakeplusplus

Execute it with:
./snakeplusplus_ubuntu

# Compiling: Windows
The compilation is much easier using Visual Studio
