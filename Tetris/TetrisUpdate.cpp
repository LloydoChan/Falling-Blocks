//TetrisUpdate.cpp - all the definitions of functions that the game's logic heavily relies on
#include "TetrisUpdate.h"
#include "TetrisRenderFuncs.h"


// UpdateGame(TetrisGame* game) - main update function for the game, calls all support functions
void UpdateGame(TetrisGame* game)
{
	
	//what is the games state?
	switch(game->state)
	{
		case TITLE_SCREEN:

			//change the transparency values for the cursor on the level select so that it
			//'glows'

			game->transparency += game->transparencyIncrement;

			if(game->transparency > 1.0f)
			{
				game->transparency = 1.0f;
				game->transparencyIncrement = -game->transparencyIncrement;
			}
			else if(game->transparency < 0.0f)
			{
				game->transparency = 0.0f;
				game->transparencyIncrement = -game->transparencyIncrement;
			}

			break;

		case NEED_NEW_BLOCK:


			//the game needs a new block so set the current block pos to the 
			//start point for all blocks

			game->currentBlockPos[0] = game->NewBlockStartPoint[0];
			game->currentBlockPos[1] = game->NewBlockStartPoint[1];

			//choose a new block
			ChooseNextBlock(game);

			//change the game state to block falling
			game->state = BLOCK_FALLING;

			//set the current rotation to the 0 index
			game->currentRotation = 0;

			//update the score and level for the game, it may be enough lines 
			//for a new level

			UpdateScoreAndLevel(game);

			//however if there is a collision at this start position we
			//have reached the conditions for a game over!

			if(IsThereCollision(game,1000,game->currentRotation))
			{
				game->state = GAME_OVER;
			}
			break;

		case BLOCK_FALLING:
			//increment fall counter
			game->fallCounter++;


			//if the fall counter is high enough, move the block and
			//reset the counter

			if(game->fallCounter > game->fallRate)
			{
				game->fallCounter = 0;
				MoveBlock(DOWN,game);
			}

			break;

		case CHECK_BOARD:

			//if there are some lines completed
			if(CheckBoardForLines(game))
			{
				//if there is a 'tetris' play a special sound!
				if(game->numLinesCompleted == 4)
					g_engine->p_audio->Play("madeTetris",game->effectsVolume);

				//put the state into flicering lines
				game->state = FLICKER_LINES;
			}
			else
			{
				//other wise just choose/select a new block
				game->state = NEED_NEW_BLOCK;
			}
			break;

		case FLICKER_LINES:
			//call the code to flicker lines if a line has been completed
			FlickerLines(game);
			break;

		case DESTROY_BLOCKS:

			//remove the completed lines from the gameboard
			RemoveLines(game);

			//update the score, lines completed,update state etc
			game->numLinesScored += game->numLinesCompleted;
			game->state = NEED_NEW_BLOCK;
			g_engine->p_audio->Play("madeLine",game->effectsVolume);
			break;

		case GAME_OVER:

			//it's game over so start the sequence!
			GameOverSequence(game);
			break;

	}
	
}

// UpdateBoard(TetrisGame* game) - a block has been put into place so add it to the board
void UpdateBoard(TetrisGame* game)
{
	//get the x and y pos of the block
	int xPos = game->currentBlockPos[0];
	int yPos = game->currentBlockPos[1];

	//get the rotation
	int rotation = game->currentRotation;


	//now for each square of the block, if it is non empty add the square to the current board
	for(int row = 0; row < 4; row++)
	{
		for(int col = 0; col < 4; col++)
		{
			if(game->currentBlock[rotation * 16 + row * 4 + col] != EMPTY)
				game->GameBoard[yPos+row][xPos+col] = game->currentBlock[rotation * 16 + row * 4 + col];
		}
	}
}

// UpdateScoreAndLevel(TetrisGame* game) - check if level can increase
void UpdateScoreAndLevel(TetrisGame* game)
{
	//if the total number scored is more than the current 'threshold'
	// and not already at the maximum 19 increase the level
	if(game->numLinesScored >= game->updateThreshold)
	{
		if(game->Level < 19)
		{
			game->Level++;
			game->fallRate -= FALL_RATE_CHANGE;
			game->updateThreshold += 10;
		}
	}

	//update score
	int score = 2 * game->numLinesCompleted * game->Level * 100;

	game->Score += score;
}

//CheckBoardForLines(TetrisGame* game) - go through the game board to see if any lines have been completed
bool CheckBoardForLines(TetrisGame* game)
{
	//the current number of recorded completed lines is 0
	game->numLinesCompleted = 0;

	//go through line by line
	for(int row = BOARD_HEIGHT - 2; row >= 0; row--)
	{
		//go through each horizontal square
		for(int col = 1; col < BOARD_WIDTH-1; col++)
		{
			//if there is an empty square break out of this loop
			if(game->GameBoard[row][col] == EMPTY)
				break;

			//otherwise if this is the last one in the row the line
			//must be complete

			if(col == BOARD_WIDTH-2)
			{
				//add this line to the array of completed lines and increase the number of
				//completed lines

				game->linesToDestroy[game->numLinesCompleted++] = row + game->numLinesCompleted;
				
			}
		}
	}

	return game->numLinesCompleted;
}

// RemoveLines(TetrisGame* game) - remove the completed lines from the board
void RemoveLines(TetrisGame* game)
{
	//for each completed line, shuffle the lines above down by one
	for(int line = 0; line < game->numLinesCompleted; line++)
	{
		ShuffleLines(game,game->linesToDestroy[line]);
	}
}

//ShuffleLines(TetrisGame* game,int line) - shuffle all the lines above 'line' down by one place
//in the board
void ShuffleLines(TetrisGame* game,int line)
{
	//from the line passed in to the top of the board
	for(int row = line; row >0; row--)
	{
		//copy each column of the above row into this one
		for(int column = 1; column < BOARD_WIDTH-1; column++)
		{
			game->GameBoard[row][column] = game->GameBoard[row-1][column];
		}
	}
}

// FlickerLines(TetrisGame* game) - flicker the lines for a little graphical
//effect
void FlickerLines(TetrisGame* game)
{
	//check if the amount of times left to flicker are above 0
	if(game->FlickerTimes >= 0)
	{
		//check if the counter to check if we 'switch' the line's visibility is more than 0
		if(game->FlickerCounter == 0)
		{
			//if so get each line that was completed and set them to the opposite of what they 
			//currently are
			for(int row = 0; row < game->numLinesCompleted; row++)
			{
			
				game->visibleLines[game->linesToDestroy[row]-row] = !game->visibleLines[game->linesToDestroy[row]-row];
			
			}

			//reset the flicker counter and decrement the number of times to flicker
			game->FlickerCounter = FLICKER_FRAMES;
			game->FlickerTimes--;
		}
		else
		{
			game->FlickerCounter--;
		}
	}
	else
	{
		//update game state and reset flickertimes to the original rate for next time
		game->state = DESTROY_BLOCKS;
		game->FlickerTimes = FLICKER_RATE;
	}
}