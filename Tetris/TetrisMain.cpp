//TetrisMain.cpp - main entry point for the tetris game - this uses the Advanced2D game engine, so there are
//many empty functions that are necessary due to 'extern' functions in the static library being used
//without them linking errors would happen - such functions are marked

#include "Includes.h"
#include "TetrisGame.h"
#include "TetrisRenderFuncs.h"
#include "TetrisUpdate.h"

//global tetris game pointer
TetrisGame* game = NULL;


bool GamePreload()
{
	g_engine->SetAppTitle("Tetris");
	g_engine->SetFullScreen(false);
	g_engine->SetScreenWidth(640);
	g_engine->SetScreenHeight(480);
	g_engine->SetColourDepth(32);
	g_engine->SetNumberControllers(0);


	
	game = new TetrisGame;
	game->state = TITLE_SCREEN;
	game->Level = 1;

	srand(time(0));

	game->effectsVolume = 1.0f;
	game->musicVolume = 1.0f;

	return 1;
}

bool GameInit(HWND hwnd)
{
	
	PreLoad(game);
	g_engine->SetPaused(false);	
	return true;
}


void RenderStrings()
{

}

void GameRender2D()
{
	RenderGame(game);
}

void GameRender3D()
{
	g_engine->ClearScene(D3DCOLOR_RGBA(0,0,0,0));
	//return to the origin
	g_engine->SetIdentity();
}


void GameUpdate()
{
	UpdateGame(game);
}
		


void GameEnd()
{
	delete game;
}


void GameKeyRelease(int x)
{
	game->canMove = true;
}

void GameKeyPress(int key)
{	
	if(key == DIK_ESCAPE)
	{
		g_engine->Close();
	}
	else if(game->canMove && key != DIK_DOWNARROW)
	{
		game->canMove = false;
		HandleInput(game,key);
	}
	else if(key == DIK_DOWNARROW && game->state == BLOCK_FALLING)
	{
		HandleInput(game,key);
	}
	else if(game->canMove && game->state == TITLE_SCREEN)
	{
		game->canMove = false;
		HandleInput(game,key);
	}
}

void GameMouseMotion(int x,int y)
{
	
}

void GameMouseWheel(int x){}

void GameMouseMove(int x,int y)
{
	
}


void GameMouseButton(int x)
{
	
	


}

void GameMouseButtonRelease(int x)
{
	
}


void GameRightThumbstickMove(short x,short y){}

void GameLeftThumbstickMove(short x,short y){}

void GamePadButtonRelease(unsigned short x){}

void GamePadButtonPress(unsigned short x){}



void GameEntityUpdate(Advanced2D::Entity* ent)
{
}

void GameEntityRender(Advanced2D::Entity* ent)
{
}

void GameEntityCollision(Advanced2D::Entity* ent1,Advanced2D::Entity* ent2)
{
}
