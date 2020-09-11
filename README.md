# SnakePlusPLus
![In-game screenshot](https://i.imgur.com/uuxV2kT.png)

# User Input

**ESC** - exit the game

**P** - pause the game

**R** - restart the game (ignoring score and record)

# Compiling: Ubuntu
1.Clone this repo
```
git clone https://github.com/framilano/SnakePlusPlus.git
```
2. You need SFML libraries, install them with:
```
sudo apt install libsfml-dev
```

3. Compile snakeplusplus opening a terminal inside src/:
```
g++ scenes.cpp headers/scenes.h snakeplusplus.cpp -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -o snakeplusplus

```
4. You need to place the compiled executable near assets and configs folders to run it, like this
![Folders placement example](https://i.imgur.com/73hCPWa.png)

# Compiling: Windows
To compile SnakePlusPlus I highly suggest to use Visual Studio 2019
1. Create a new empty C++ project in Visual Studio, include and link the SFML libraries (using [this](https://www.sfml-dev.org/tutorials/2.5/start-vc.php) guide)
2. Inside your project's root folder copy assets, configs and src folders
3. Add snakeplusplus.cpp and scenes.cpp to source files in VS, add scenes.h to headers files in VS
4. Run in Release x86 mode after compiling the project, the new compiled executable will now appear in \Release
5. Add next to the executable both assets and configs folders
