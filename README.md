# 🔰 Battle City Game 🔰

[![](https://img.shields.io/badge/author-@OlaBannan-blue.svg?style=flat)](www.linkedin.com/in/ola-bannan-98a667175)


<div align="center"><img src="https://drive.google.com/uc?export=view&id=1aeL_aIJgsSiAIlsslbbz88Sk-EO_TP09" width="500" height="300"/></div>

## Game's Brief Explanation:

The player, controlling a Tank, must destroy enemy tanks in each level, which enter the playfield from the
top of the screen. The enemy tanks attempt to destroy the player's base (represented on the map as a bird, eagle, or Phoenix),
as well as the human tank itself. A level is completed when the player destroys all number of enemy tanks that will be shown at the right
side of the sceen window, but the game ends if the player's base is destroyed or the player loses all available lives. Note that the player tank's
weapon can destroy the base as well, so the player can still lose even after all enemy tanks are destroyed.

Battle City contains 5 different stages. Each map contains different types of terrain and obstacles.

Tank: a symbol that gives an extra life. Player also earns one extra life by won in a level;

Battle City was one of the earlier games to allow two players to play simultaneously. 
Both players have to defend the base together, and if one player shoots the other.

```
*****************************************************************************
* player 2:                   player2:                                      *
*        pgUp                     W                       UP                *
* pgLeft      pgRight           A   D                LEFT    RIGHT          *
*      pgDown                     S                      DOWN               *
*	                                                                    *
*                                                                           *
* Space                         E                    Shot a bullet          *
*                                                                           *
*****************************************************************************
```

## Design:
### List of files
**Note:  (^ X : inheritance from Class X)**

- _main.cpp
Include the main Function.

- macros.h
Include all the sfml library

- block.h + block.cpp = block Class:
Stores all data and the function that related to the map's blocks.

- bullet.h + bullet.cpp = bullet Class - derived class ^ (public sf::Drawable, public Collision):
Stores all data and the function that related to the bullet object.

- Clock.h + Clock.cpp = Timer class - derived class:
Stores all the data and the function that related to the map's clock.

- Collision.h + Collision.cpp = Collision class ---> Base class ABSTRACT:
stores all the function of the collisions between the objects and also for 
every object it's img, type, ID and others 

- Enemy.h + Enemy.cpp =  Enemy class - derived class(^ Tank):
Stores all the data and the function that related to the enemy's tanks.

- Explosion.h + Explosion.cpp = Explosion class - derived class( ^public sf::Drawable):
stores all the data,the function and the clock that related to the explosion.

- Game.h + menu.cpp = Game class:
It is like the game's controller's function.

- Map.h + Map.cpp = Map class - derived class(^public sf::Drawable):
stores all the data and the function that related to the game's Window( sf::RenderWindow).

- Player1.h + Player1.cpp  = Player1 class - derived class(^ Tank):
Stores all the data and the function that related to the first players's tanks.

- Player2.h + Player2.cpp =  Player2 class - derived class(^ Tank):
Stores all the data and the function that related to the second players's tanks.

- Single.h + Single.cpp = Single class:
Stores all the data and the function that related to the first players's tanks.

- Sound.h = Sound class:
Stores all the data and the function that related to the games's sounds.

- Sprite.h + Sprite.cpp = Sprite class:
Stores all the data and the function that related to the games's images.

- Tank.h + Tank.cpp = Tank Class- baseClass &  derived class(^ public sf::Drawable, public Collision):
Base class of the tanks Stores all the data and the function that related to the games's Tanks.
(the player is a tank so it's dervied from Tank class and also the enemy the same story).



## Adding A Stage To The Game

***You can make your own level!*** <br><br>
To add new level:
1. make new notebad's file.
2. rename the file that you created in the first step to be levelN.txt (N is a number > 5 )
PS: Select consecutive numbers(eg :if you created level7.txt in the past, then you have to chose 8 and so on)
3. go to data/levels/level_empty.txt it is an empty ground(in it there is only the player, eagle and the enemies),
4. copy it and paste it in the file that you created in the first step
5. emplace as you like in the empty blocks, you can add water, green(=grass), bricks, stone
 and others, and every thing you add, you have to choose in which style you would like it
 to be, you have 12 different styles
6. go to the map.cpp and in the row number ,change the number 5 to --> N that you had choose 


PS: You have to save the number of the rows and columns like it is, do not add rows and columns :stuck_out_tongue_winking_eye:
If so, I don't know how it will be displayed 	:sweat_smile:


## Main data structures:
- In collision.h:
typedef std::unique_ptr<Tank> TankPtr
enum class Move

- In enemy.h:
  - enum class MoveState { down, left, right, up }

- In sound.h:
  - std::map<int, sf::SoundBuffer> buffer

- In tank.h:
  - std::list<Bullet> & bullets
  - std::list<Explosion> & explosions

- In map.cpp:
  - typedef std::array < Block, blockSIZE > Blocks
  - typedef std::array < Blocks, blockSIZE > BlockTab
  - struct Window
  - struct Level
  - enum class Sett
  - enum class GameState

- In block.cpp:
  - enum class Type
  - enum class Move
  - enum class Pos 


## Known Bugs:
Unkown

## Other Notes:

***You can make your own level!***
To add new level:
1. make new notebad's file.
2. rename the file that you created in the first step to be levelN.txt (N is a number > 5 )
PS: Select consecutive numbers(eg :if you created level7.txt in the past, then you have to chose 8 and so on)
3. go to data/levels/level_empty.txt it is an empty ground(in it there is only the player, eagle and the enemies),
4. copy it and paste it in the file that you created in the first step
5. emplace as you like in the empty blocks, you can add water, green(=grass), bricks, stone
 and others, and every thing you add, you have to choose in which style you would like it
 to be, you have 12 different styles
6. go to the map.cpp and in the row number ,change the number 5 to --> N that you had choose 

***PS:*** You have to save the number of the rows and columns like it is, do not add rows and columns :stuck_out_tongue_winking_eye:
If as, then I don't know how it'll be shown. :laughing:
  
## References

[`VisualStudio`](https://visualstudio.microsoft.com/)
[`CPP`](https://en.cppreference.com/w/cpp/language)

## License

GPL License

Copyright (c) [2020] [Ola Bannan]

  The licenses for most software and other practical works are designed
to take away your freedom to share and change the works.  By contrast,
the GNU General Public License is intended to guarantee your freedom to
share and change all versions of a program--to make sure it remains free
software for all its users.  We, the Free Software Foundation, use the
GNU General Public License for most of our software; it applies also to
any other work released this way by its authors.  You can apply it to
your programs, too.

  When we speak of free software, we are referring to freedom, not
price.  Our General Public Licenses are designed to make sure that you
have the freedom to distribute copies of free software (and charge for
them if you wish), that you receive source code or can get it if you
want it, that you can change the software or use pieces of it in new
free programs, and that you know you can do these things.

  To protect your rights, we need to prevent others from denying you
these rights or asking you to surrender the rights.  Therefore, you have
certain responsibilities if you distribute copies of the software, or if
you modify it: responsibilities to respect the freedom of others.

  For example, if you distribute copies of such a program, whether
gratis or for a fee, you must pass on to the recipients the same
freedoms that you received.  You must make sure that they, too, receive
or can get the source code.  And you must show them these terms so they
know their rights.



---
## Author Info

- Github - [Ola Bannan](https://github.com/OlaBannan)
- Linkedin - [Ola Bannan](www.linkedin.com/in/ola-bannan-98a667175)

