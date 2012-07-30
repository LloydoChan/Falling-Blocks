#include "TetrisGame.h"
#include "TetrisUpdate.h"


//PreLoad(TetrisGame* game) - Load all the textures and sounds required for the game.

void PreLoad(TetrisGame* game)
{
	game->blockImg.Load("block.png");
	game->wallImg.Load("Invisible.png");
	game->background.Load("background1.png");
	game->textBg.Load("TextBackground.png");
	game->blockBg.Load("BlockBackground.png");
	game->gameOverImage.Load("GameOverImage.png");
	game->titleScreen.Load("TitleScreen.png");
	game->cursorImg.Load("cursor.png");

	//load text
	game->text.LoadImg("Untitled.tga");
	game->text.SetColumns(16);
	game->text.SetCharSize(20,16);
	game->text.LoadWidthData("Untitled.dat");

	g_engine->p_audio->Load("moveblock.wav","rotate");
	g_engine->p_audio->Load("mainMusic.mp3","musicMain");
	g_engine->p_audio->Load("LineCompleted.wav","madeLine");
	g_engine->p_audio->Load("TetrisSound.wav","madeTetris");
	g_engine->p_audio->Load("GameOver.wav","gameOver");

	game->transparency = 0.0f;
	game->transparencyIncrement = 0.05f;

	game->text.SetScale(1.2f);
}

// InitTetrisGame(TetrisGame* game) - init the initial state of a fresh new game
void InitTetrisGame(TetrisGame* game)
{
	//init board
	for(int rows = 0; rows < BOARD_HEIGHT; rows++)
	{
		for(int columns = 1; columns < BOARD_WIDTH; columns++)
		{
			game->GameBoard[rows][columns] = EMPTY;
		}
		game->GameBoard[rows][0]  = INVISIBLE;
		game->GameBoard[rows][11] = INVISIBLE;
		game->visibleLines[rows] = true;
	}

	for(int columns = 0; columns <= BOARD_WIDTH; columns++)
	{
		game->GameBoard[BOARD_HEIGHT-1][columns] = INVISIBLE;
	}

	//set game new block start point
	game->NewBlockStartPoint[0] = 4;
	game->NewBlockStartPoint[1] = 0;



	game->currentRotation = 0;

	game->state = BLOCK_FALLING;

	game->canMove = true;

	//init sets
	for(int i= 0; i < 7; i++)
	{
		game->BlockSetOne[i] = game->BlockSetTwo[i] = i; 
	}


	//shuffleSets
	ShuffleSet((game->BlockSetOne));
	ShuffleSet((game->BlockSetTwo));

	game->inUseSet = game->BlockSetOne;
	game->nextSet  = game->BlockSetTwo;

	game->currentIndex = 2;

	game->currentBlock = &BLOCK_DATA[game->inUseSet[0]][0][0][0];

	game->updateThreshold = 10;

	game->Score = game->numLinesScored = 0;


	game->updateThreshold = (game->Level + 1) * 10;

	game->fallCounter = 0;

	game->fallRate = FALL_RATE - game->Level * FALL_RATE_CHANGE;

	game->numLinesCompleted = 0;

	game->FlickerCounter = 0;

	game->FlickerTimes = FLICKER_RATE;

	
	game->currentBlockPos[0] = game->NewBlockStartPoint[0];
	game->currentBlockPos[1] = game->NewBlockStartPoint[1];

	g_engine->p_audio->Play("musicMain",game->musicVolume);

	game->gameOverX1 = 1;
	game->gameOverY1 = 20;
	game->gameOverX2 = 10;
	game->gameOverY2 = 0;

	game->increment = 1;

	game->GameOverImageBool = false;

}

// MoveBlock(int direction,TetrisGame* game) - move the block based on current input if possible
void MoveBlock(int direction,TetrisGame* game)
{
	//depending on the incoming direction of movement, apply different tests for collision
	switch(direction)
	{
		case LEFT:
			if(!IsThereCollision(game,direction,game->currentRotation))
			{
				game->currentBlockPos[0] -= 1;
			}
			break;
		case RIGHT:
			if(!IsThereCollision(game,direction,game->currentRotation))
			{
				game->currentBlockPos[0] += 1;
			}
			break;
		case DOWN:
			//for down this is a special case - check if we can 'set' the block or not
			if(!IsThereCollision(game,direction,game->currentRotation))
			{
				game->currentBlockPos[1] += 1;
			}
			else
			{
				//if the collision returns true we can set the block, update the board,
				//play a sound effect and check for lines
				UpdateBoard(game);
				g_engine->p_audio->Play("madeLine",game->effectsVolume);
				game->state = CHECK_BOARD;
			}
			
	}
}

// RotateBlock(TetrisGame* game,int direction) - rotate the block if
//possible in the required direction
void RotateBlock(TetrisGame* game,int direction)
{
	int rotation;

	//if the new rotation is above 3 or below zero 'wrap' it around
	if(game->currentRotation + direction > 3)
	{
		rotation = 0;
	}
	else if(game->currentRotation + direction < 0)
	{
		rotation = 3;
	}
	else
	{
		rotation = game->currentRotation + direction;
	}

	//check for collision - if no collision, rotate the block
	if(!IsThereCollision(game,NONE,rotation))
		game->currentRotation = rotation;
}

// IsThereCollision(TetrisGame* game,int direction,int rotation) - using an offset direction check if the block in a new position
// or rotation causes any collision
bool IsThereCollision(TetrisGame* game,int direction,int rotation)
{
	//get x, y
	int x = game->currentBlockPos[0];
	int y = game->currentBlockPos[1];

	int vertOffset  = 0;
	int horizOffset = 0;

	//set the offset depending on the direction
	switch(direction)
	{
	case LEFT:
		horizOffset = -1;
		break;
	case RIGHT:
		horizOffset = 1;
		break;
	case DOWN:
		vertOffset = 1;
		break;
	case NONE:
		;
	}

	//now check every square of the block and also every square in the board
	//using the offset

	for(int row = 0; row < 4; row++)
	{
		for(int col = 0; col < 4; col++)
		{
			if(game->GameBoard[y + vertOffset + row][x + horizOffset + col] != EMPTY && game->currentBlock[rotation * OFFSET + row * 4 + col] != EMPTY)
			{
				return true;
			}
		}
	}

	return false;
}


// HandleInput(TetrisGame* game,int inputKey) input handeler for the main game
void HandleInput(TetrisGame* game,int inputKey)
{
	switch(game->state)
	{
		//if a block is falling it can be moved and rotated
		case BLOCK_FALLING:
			switch(inputKey)
			{
				case DIK_LEFTARROW:
					MoveBlock(LEFT,game);
					break;
				case DIK_RIGHTARROW:
					MoveBlock(RIGHT,game);
					break;
				case DIK_DOWNARROW:
					MoveBlock(DOWN,game);
					break;
				case DIK_Z:
					RotateBlock(game,ANTI_CLOCKWISE);
					g_engine->p_audio->Play("rotate",game->effectsVolume);
					break;
				case DIK_X:
					RotateBlock(game,CLOCKWISE);
					g_engine->p_audio->Play("rotate",game->effectsVolume);
					break;

			}	
			break;
	

		case TITLE_SCREEN:
		
			//if the title screen the player can move the cursor, if the cursor pos is above or below
			//certain indices 'wrap' it around
			switch(inputKey)
			{
				case DIK_S:
					game->state = NEED_NEW_BLOCK;
					InitTetrisGame(game);
					break;
				case DIK_UP:
					game->Level -= 5;
					if(game->Level < 1) 
					{
						game->Level += 10;
					}
					break;
				case DIK_DOWN:
					game->Level += 5;
					if(game->Level > 9) 
					{
						game->Level -= 10;
					}
					break;
				case DIK_LEFT:
					game->Level--;
					if(game->Level < 1)
					{
						game->Level = 9;
					}
					break;
				case DIK_RIGHT:
					game->Level++;
					if(game->Level > 9)
					{
						game->Level = 1;
					}
					break;
			}
		break;

		case GAME_OVER:
			if(inputKey == DIK_S)
			{
				g_engine->p_audio->Stop("musicMain");
				game->state = TITLE_SCREEN;
			}
	}

	switch(inputKey)
	{
		case DIK_U:
			game->musicVolume += 0.1f;

			if(game->musicVolume > 1.0f)
			{
				game->musicVolume = 1.0f;
			}
			break;
		case DIK_Y:
			game->musicVolume -= 0.1f;

			if(game->musicVolume < 0.0f)
			{
				game->musicVolume = 0.0f;
			}
			break;
		case DIK_H:
			game->effectsVolume += 0.1f;

			if(game->effectsVolume > 1.0f)
			{
				game->effectsVolume = 1.0f;
			}
			break;
		case DIK_J:
			game->effectsVolume -= 0.1f;

			if(game->effectsVolume < 0.0f)
			{
				game->effectsVolume = 0.0f;
			}
			break;
	}
	
}



// ShuffleSet(int set[]) - shuffle a set of seven blocks for use in the game
void ShuffleSet(int set[])
{
	for(int i=0; i < 7; i++)
	{
		int randIndex = rand() % 7;
		int temp = set[i];
		set[i] = set[randIndex];
		set[randIndex] = temp;
	}
}


//void ChooseNextBlock(TetrisGame* game) - get the next block from the current set
void ChooseNextBlock(TetrisGame* game)
{
	//using the index from the shuffled set of indices
	int index = game->inUseSet[game->currentIndex++];

	//if the current index is more than 6 wrap it to 0
	if(game->currentIndex == 7)
	{
		game->currentIndex = 0;

		ShuffleSet(game->inUseSet);
		int* temp = game->inUseSet;
		game->inUseSet = game->nextSet;
		game->nextSet = temp;
	}

	game->currentBlock = &BLOCK_DATA[index][0][0][0];

}


//GameOverSequence(TetrisGame* game) - set the game over animation into action, with a snake like
//sequence of blocks coming from the top and the bottom to meet in the middle, then display the
//game over image
void GameOverSequence(TetrisGame* game)
{
	//there are two current y levels for the top and bottom - one increments and the other decrements until they
	//are the same value
	if(game->gameOverY1 >= game->gameOverY2)
	{
		//set the board value to invisible
		game->GameBoard[game->gameOverY1][game->gameOverX1] = INVISIBLE;
		game->GameBoard[game->gameOverY2][game->gameOverX2] = INVISIBLE;

		//now increment the indices used to change the board values
		game->gameOverX1 += game->increment;
		game->gameOverX2 -= game->increment;

		//check the values
		if(game->gameOverX1 > 10 || game->gameOverX1 <= 0)
		{
			game->increment = -(game->increment);
			game->gameOverY1--;
			game->gameOverY2++;
		}

		g_engine->p_audio->Play("gameOver",game->effectsVolume);
	}
	else
	{
		game->GameOverImageBool = true;
	}
}