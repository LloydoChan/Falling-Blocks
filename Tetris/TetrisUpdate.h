//TetrisUpdate.h - this file shows all declarations for tetris game updating the state of objects logic
//see tetrisupdate.cpp for for the explanations and definitions of the functions
#include "TetrisGame.h"

void UpdateGame(TetrisGame* game);

void UpdateBoard(TetrisGame* game);

void UpdateScoreAndLevel(TetrisGame* game);

bool CheckBoardForLines(TetrisGame* game);

void CreateParticles(TetrisGame* game);

void RemoveLines(TetrisGame* game);

void ShuffleLines(TetrisGame* game,int line);

void FlickerLines(TetrisGame* game);