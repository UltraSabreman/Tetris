#ifndef __GINCLUDES__
#define __GINCLUDES__

using namespace std;

//Global Includes
#include <iostream>
#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>



//Enums
//enum TileColors {RED, YELLOW, ORANGE, GREEN, CYAN, BLUE, PURPLE};
enum TetraminoTypes {TETRIS_TYPE_Z, TETRIS_TYPE_L, TETRIS_TYPE_O, TETRIS_TYPE_J, TETRIS_TYPE_I, TETRIS_TYPE_S, TETRIS_TYPE_T};
enum Direction {TETRIS_DIR_NONE, TETRIS_DIR_LEFT, TETRIS_DIR_UP, TETRIS_DIR_RIGHT, TETRIS_DIR_DOWN};

//Global Const Vars
const float FPS = 60;
const int PNG_OFFSET = 18;
const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 22;


const float pi = 3.1415926535897932384626433832795;


//colors:

//void 

//StarterPaterns


#endif