//TetrisRenderFuncs.cpp - definitions for all rendering 
#include "TetrisRenderFuncs.h"

//RenderImage(TetrisGame* game, int x, int y, D3DXCOLOR color,Texture* image) - used by many other functions
//to render the supplied image at the x and y position
void RenderImage(TetrisGame* game, int x, int y, D3DXCOLOR color,Texture* image)
{
	D3DXMATRIX mat;
	D3DXVECTOR2 trans(x,y);
	D3DXMatrixTransformation2D(&mat,NULL,0,NULL,NULL,NULL,&trans);
	g_engine->GetSpriteHandler()->SetTransform(&mat);

	g_engine->GetSpriteHandler()->Draw(image->GetTexture(),NULL,NULL,NULL,color);
}

//void PlotBlock(TetrisGame* game,int x,int y,int blockCol)
//used by render board and render block to draw a single block of various
//color types
void PlotBlock(TetrisGame* game,int x,int y,int blockCol)
{
	RECT srcRect = {0,0,BLOCK_SIZE,BLOCK_SIZE};
	D3DXCOLOR color;

	//set the d3d color to the appropriate type
	switch(blockCol)
	{
		case INVISIBLE:
			color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			break;
		case L_BLOCK:
			color = D3DXCOLOR(1.0f,1.0f,0.0f,1.0f);
			break;
		case R_BLOCK:
			color = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
			break;
		case T_BLOCK:
			color = D3DXCOLOR(0.0f,1.0f,0.0f,1.0f);
			break;
		case S_BLOCK:
			color = D3DXCOLOR(0.0f,0.0f,1.0f,1.0f);
			break;
		case SQ_BLOCK:
			color = D3DXCOLOR(1.0f,0.0f,1.0f,1.0f);
			break;
		case Z_BLOCK:
			color = D3DXCOLOR(0.0f,1.0f,1.0f,1.0f);
			break;
		case LONG_BLOCK:
			color = D3DXCOLOR(1.0f,1.0f,0.0f,1.0f);
			break;
		case EMPTY:
			color = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
			break;
	}

	//if the block isn't invisible render the blocktexture,
	//otherwise don't!
	if(blockCol != INVISIBLE)
	{
		RenderImage(game,x,y,color,&(game->blockImg));
	}
	else
	{
		RenderImage(game,x,y,color,&(game->wallImg));
	}
}

//RenderBlock(TetrisGame* game,int x, int y,const int* block,bool rotate) - render the block
void RenderBlock(TetrisGame* game,int x, int y,const int* block,bool rotate)
{
	int offset = 0;

	//calculate an offset into the block data depending on the rotation index
	if(rotate)
	{
		offset = game->currentRotation * 16;
	}

	//for each of the 16 blocks 'plot' a block to the screen, pass in the x and y pixel vales
	for(int row = 0; row < 4; row++)
	{
		for(int col = 0; col < 4; col++)
		{
			if(block[offset + row * 4 + col] != EMPTY)
			{
				PlotBlock(game,x + col * BLOCK_SIZE  ,y + row * BLOCK_SIZE,block[offset + row * 4 + col]);
			}
		}
	}
}


// RenderBoard(TetrisGame* game) - render the whole board that is currently 'set'
void RenderBoard(TetrisGame* game)
{
	//really simple - go through row by row, column by column and render the squares if necessary
	for(int row = 0; row < 21; row++)
	{
		
			for(int col = 0; col < 12; col++)
			{
				if(game->GameBoard[row][col] != EMPTY && game->GameBoard[row][col] != INVISIBLE && game->visibleLines[row])
				{
					PlotBlock(game,GAME_BOARD_TOP_LEFT_X + col * BLOCK_SIZE,GAME_BOARD_TOP_LEFT_Y + row * BLOCK_SIZE,game->GameBoard[row][col]);	
				}
				else if(game->GameBoard[row][col] == INVISIBLE)
				{
					PlotBlock(game,GAME_BOARD_TOP_LEFT_X + col * BLOCK_SIZE,GAME_BOARD_TOP_LEFT_Y + row * BLOCK_SIZE,game->GameBoard[row][col]);	
				
				}
				else if(game->GameBoard[row][col] == EMPTY)
				{
					PlotBlock(game,GAME_BOARD_TOP_LEFT_X + col * BLOCK_SIZE,GAME_BOARD_TOP_LEFT_Y + row * BLOCK_SIZE,game->GameBoard[row][col]);	
				}
			}
	}
}

//RenderBackground(TetrisGame* game) - render the space image
void RenderBackground(TetrisGame* game)
{
	RenderImage(game,0,0,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),&(game->background));
}


//RenderGame(TetrisGame* game) - depending on the game state, render the game 
void RenderGame(TetrisGame* game)
{
	if(game->state != TITLE_SCREEN)
	{
		//we are in main game mode, or a version of it - render from back to front
		RenderBackground(game);

		RenderBoard(game);

		//if the block is falling render it 
		if(game->state == BLOCK_FALLING)
		{
			RenderBlock(game,game->currentBlockPos[0] * BLOCK_SIZE + GAME_BOARD_TOP_LEFT_X,
						game->currentBlockPos[1] * BLOCK_SIZE + GAME_BOARD_TOP_LEFT_Y,game->currentBlock,true);
		}

		//render the score and level display etc
		RenderHUD(game);

		//if game over, render the game over sign
		if(game->state == GAME_OVER && game->GameOverImageBool)
		{
			RenderImage(game,200,200,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),&(game->gameOverImage));
		}
	}
	else
	{
		//otherwise, we are in title screen mode, so render the main title,
		//the levels to choose from and the transparent cursor
		int xOffset = 230 + (game->Level + 4) % 5 * 35;
		int yOffset = 310 + (game->Level / 6) * 35;
		RenderImage(game,0,0,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),&(game->titleScreen));
		RenderImage(game,xOffset,yOffset,D3DXCOLOR(1.0f,1.0f,1.0f,game->transparency),&(game->cursorImg));
	}
}

// RenderHUD(TetrisGame* game) - render the score and upcoming blocks
void RenderHUD(TetrisGame* game)
{
	
	
	RenderHUDComponent(game,"Level: ",&LEVEL_TEXT_POS[0],game->Level);
	RenderHUDComponent(game,"Lines: ",&LINES_TEXT_POS[0],game->numLinesCompleted);
	RenderHUDComponent(game,"Score: ",&SCORE_TEXT_POS[0],game->Score);
	RenderHUDComponent(game,"Next Blocks: ",&NEXT_BLOCK_POS[0],-1);

	RenderPreviews(game);

	//RenderBlock(game,true);
}

// RenderPreviews(TetrisGame* game) - render the next four blocks as a preview
void RenderPreviews(TetrisGame* game)
{
	int index = game->currentIndex;
	int blockNum;

	for(int y = 0; y < 2; y++)
	{
		for(int x = 0; x < 2; x++)
		{

			if(index >= 7)
			{
				index = 0;
				blockNum = game->nextSet[index++];
			}
			else
			{
				blockNum = game->inUseSet[index++];
			}

			RenderImage(game,NEXT_BLOCK_POS[0] + x * 110 - 10,NEXT_BLOCK_POS[1] + 50 + y * 100,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),&(game->blockBg));
			RenderBlock(game,NEXT_BLOCK_POS[0] + x * 110,NEXT_BLOCK_POS[1] + 70 + y * 100,&BLOCK_DATA[blockNum][0][0][0],false);
		}
	}
}

void RenderHUDComponent(TetrisGame* game,char* text,const int* position,int value)
{
	game->os.str("");

	game->os << text;
	
	if(value != -1)
	{
		game->os << value;
	}


	RenderImage(game,position[0] - 10, position[1] - 10,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),&(game->textBg));

	game->text.Print(position[0],position[1],game->os.str(),0xFFFFFFFF);
}