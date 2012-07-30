//TetrisGame.h - struct and function declarations for main game code
// with the approach i took to this game i didn't use c++ classes but instead c style structs and 
//functions that work on the data itself. I did this just as an experiment in different coding styles
//and to learn about doing things in a different way.

#pragma once
#include <iostream>
#include <sstream>
#include "Includes.h"
#include "Definitions.h"

using namespace Advanced2D;


//the main tetris game struct - all the data used for the game is contained within the below struct
struct TetrisGame
{
	//the main 'board'
	int GameBoard[BOARD_HEIGHT][BOARD_WIDTH];


	//where new blocks 'start', as a ref point in the board
	int NewBlockStartPoint[2];

	//current level
	int Level;

	//current score
	int Score;

	//
	int numLinesScored;
	int numLinesCompleted;

	//an array of completed lines used for clearing the board - there can only be
	//four at a time so make this four elements in size
	int linesToDestroy[4];

	//in tetris, people think every block is generated randomly, however, there are 7 blocks and to
	//avoid situations where somebody will get more than two consecutive blocks of the same type
	//shuffled complete sets of blocks are used and itereated through. there is a pointer to the
	//current set in use by the game
	int  BlockSetOne[7];
	int  BlockSetTwo[7];
	int* inUseSet;
	int* nextSet;
	int  currentIndex;

	//the current rotation index - from 0 to 3
	int currentRotation;

	//a pointer to the current block - points to a place in a big multidimensional array
	//describing block data
	const int* currentBlock;

	//the current ref point in x and y of the top left corner of the block that
	//is controlled by the player
	int currentBlockPos[2];

	//a series of bools - this is used to 'flicker' the lines when lines are completed - 
	//they are set from visible to non visible and back
	bool visibleLines[BOARD_HEIGHT];

		//how many frames should the flicker flicker off for?
	int FlickerCounter;

	//how many times should the lines flicker?
	int FlickerTimes;

	//a counter used to measure time between blocks falling
	int fallCounter;

	//how many ticks the fall counter should count before moving the block down
	int fallRate;

	//current game state
	int state;

	//can the player move?
	bool canMove;

	//can we display the gameOver image?
	bool GameOverImageBool;


	//textures used to make up the screen
	Texture blockImg;
	Texture wallImg;
	Texture background;
	Texture textBg;
	Texture blockBg;
	Texture gameOverImage;
	Texture titleScreen;
	Texture cursorImg;

	int updateThreshold;

	//an ostringstream used to output score info
	std::ostringstream os;

	//a font used with the ostringstream to output score, level number etc
	Font text;



	bool paused;
	
	//transparency - will be used for the synching with music, when 
	//implemented
	float transparency; 
	float transparencyIncrement;

	//gameover display coords
	int gameOverX1;
	int gameOverX2;
	int gameOverY1;
	int gameOverY2;

	int increment;

	float effectsVolume;
	float musicVolume;
};

//function forward declarations

void PreLoad(TetrisGame* game);

void InitTetrisGame(TetrisGame* game);


void MoveBlock(int direction,TetrisGame* game);

void RotateBlock(TetrisGame* game);

bool IsThereCollision(TetrisGame* game,int direction,int rotation);

void HandleInput(TetrisGame* game,int inputKey);

void ShuffleSet(int set[]);

void ChooseNextBlock(TetrisGame* game);

void GameOverSequence(TetrisGame* game);