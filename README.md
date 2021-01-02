# SnakePlusPlus
![In-game screenshot](https://i.imgur.com/uuxV2kT.png)

## User Input

**ESC** - exit the game

**P** - pause the game

**R** - restart the game (ignoring score and record)

## Build Instructions: Ubuntu
1. Clone this repo
```
git clone https://github.com/framilano/SnakePlusPlus.git
```
2. You need SFML and TGUI libraries, install them with:
```
sudo add-apt-repository ppa:texus/tgui-0.8
sudo apt-get update
sudo apt-get install libtgui-dev && sudo apt install libsfml-dev 
```

3. Compile snakeplusplus opening a terminal inside src/:
```
g++ -Wall -g scenes.cpp headers/scenes.h snakeplusplus.cpp -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -ltgui -o snakeplusplus
```
4. You need to place the compiled executable near assets and configs folders to run it, like this
![Folders placement example](https://i.imgur.com/73hCPWa.png)


## Build Instructions: Windows
1. Clone this repo
```
git clone https://github.com/framilano/SnakePlusPlus.git
```
To build SnakePlusPlus I highly suggest to use Visual Studio 2019

2. Create a new empty C++ project in Visual Studio, include and link the SFML libraries (using [this](https://www.sfml-dev.org/tutorials/2.5/start-vc.php) guide)
3. As you did with SFML, link [TGUI](https://tgui.eu/download/) libraries in the exact same way
4. Inside your project's root folder copy assets, configs and src folders
![Folders' structure example](https://i.imgur.com/v0lxSB5.png)
5. Add snakeplusplus.cpp and scenes.cpp to source files in VS, add scenes.h to headers files in VS
![Solution Explorer](https://i.imgur.com/M6nKAjL.png)
6. Run in Release x86 mode after compiling the project, the new compiled executable will now appear in \Release
7. Add next to the executable both assets and configs folders
