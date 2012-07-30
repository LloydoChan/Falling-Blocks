//TetrisRenderFuncs.h - used to declare all the functions associated with rendering,
//see TetrisRenderFuncs.cpp for descriptions and code
#pragma once
#include "TetrisGame.h"

void RenderBlock(TetrisGame* game,int x, int y,bool rotate);

void RenderBoard(TetrisGame* game);

void RenderPreviews(TetrisGame* game);

void RenderHUD(TetrisGame* game);

void RenderHUDComponent(TetrisGame* game,char* text,const int* position,int value);

void RenderGame(TetrisGame* game);

void RenderBackground(TetrisGame* game);

void RenderImage(TetrisGame* game, int x, int y, D3DXCOLOR color,Texture* image);

void PlotBlock(TetrisGame* game,int x,int y,int blockType);