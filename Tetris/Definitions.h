//Definitions.h - this is to hold all the constant values for the game
#pragma once

//number for blocks, for indexes etc
const int L_BLOCK    = 0;
const int R_BLOCK    = 1;
const int SQ_BLOCK   = 2;
const int S_BLOCK    = 3;
const int Z_BLOCK    = 4;
const int LONG_BLOCK = 5;
const int T_BLOCK    = 6;
const int INVISIBLE  = 7;
const int EMPTY      = 8;

const int CURRENT_BLOCK = 0;
const int NEXT_BLOCK    = 1;

const int BOARD_WIDTH  = 12;
const int BOARD_HEIGHT = 21;

const int START_COL  = 1;
const int END_COL    = 10;

const int GAME_BOARD_TOP_LEFT_X = 71;
const int GAME_BOARD_TOP_LEFT_Y = 53;

const int NEXT_BLOCK_POS[2] = {416,53};
const int LEVEL_TEXT_POS[2] = {416,333};
const int SCORE_TEXT_POS[2] = {416,383};
const int LINES_TEXT_POS[2] = {416,433};

const int FALL_RATE		   = 80;
const int FALL_RATE_CHANGE = 7;

const int FLICKER_RATE   = 9;
const int FLICKER_FRAMES = 5;

const int BLOCK_DATA[7][4][4][4] ={{{{EMPTY,L_BLOCK,EMPTY,  EMPTY},
									{EMPTY,L_BLOCK,EMPTY,  EMPTY},
									{EMPTY,L_BLOCK,L_BLOCK,EMPTY},
									{EMPTY,EMPTY,  EMPTY,  EMPTY}},

								   {{EMPTY,   EMPTY,  EMPTY,  EMPTY},
									{L_BLOCK, L_BLOCK,L_BLOCK,EMPTY},
									{L_BLOCK, EMPTY,  EMPTY,  EMPTY},
									{EMPTY,   EMPTY,  EMPTY,  EMPTY}},

								   {{L_BLOCK, L_BLOCK,  EMPTY,    EMPTY},
									{EMPTY,   L_BLOCK,  EMPTY,    EMPTY},
									{EMPTY,   L_BLOCK,  EMPTY,    EMPTY},
									{EMPTY,   EMPTY,    EMPTY,    EMPTY}},

								   {{EMPTY,   EMPTY,    L_BLOCK,    EMPTY},
									{L_BLOCK, L_BLOCK,  L_BLOCK,    EMPTY},
									{EMPTY,   EMPTY,    EMPTY,      EMPTY},
									{EMPTY,   EMPTY,    EMPTY,      EMPTY}}},

/*R_BLOCK_DATA*/                     {{{EMPTY,  EMPTY,    EMPTY, EMPTY},
									  {EMPTY  ,R_BLOCK,  EMPTY, EMPTY},
									  {EMPTY  ,R_BLOCK,  EMPTY, EMPTY},
									  {R_BLOCK,R_BLOCK,  EMPTY, EMPTY}},


								   {{EMPTY,   EMPTY,    EMPTY,    EMPTY},
									{R_BLOCK, EMPTY,    EMPTY,    EMPTY},
									{R_BLOCK, R_BLOCK,  R_BLOCK,  EMPTY},
									{EMPTY  , EMPTY,    EMPTY,    EMPTY}},

								   {{EMPTY,  EMPTY,      EMPTY,   EMPTY},
									{EMPTY,  R_BLOCK,    R_BLOCK, EMPTY},
									{EMPTY,  R_BLOCK,    EMPTY,   EMPTY},
									{EMPTY,  R_BLOCK,    EMPTY,   EMPTY}},

								   {{EMPTY,   EMPTY,    EMPTY,    EMPTY},
									{EMPTY,    EMPTY,   EMPTY,    EMPTY},
									{R_BLOCK,  R_BLOCK, R_BLOCK,  EMPTY},
									{EMPTY,    EMPTY,   R_BLOCK,  EMPTY}}},

/* SQ_BLOCK_DATA*/				  { {{EMPTY,EMPTY,    EMPTY,    EMPTY},
									{EMPTY, SQ_BLOCK, SQ_BLOCK, EMPTY},
									{EMPTY, SQ_BLOCK, SQ_BLOCK, EMPTY},
									{EMPTY, EMPTY,    EMPTY,    EMPTY}},

								   {{EMPTY, EMPTY,    EMPTY,    EMPTY},
									{EMPTY, SQ_BLOCK, SQ_BLOCK, EMPTY},
									{EMPTY, SQ_BLOCK, SQ_BLOCK, EMPTY},
									{EMPTY, EMPTY,    EMPTY,    EMPTY}},

								   {{EMPTY, EMPTY,    EMPTY,    EMPTY},
									{EMPTY, SQ_BLOCK, SQ_BLOCK, EMPTY},
									{EMPTY, SQ_BLOCK, SQ_BLOCK, EMPTY},
									{EMPTY, EMPTY,    EMPTY,    EMPTY}},

								   {{EMPTY, EMPTY,    EMPTY,    EMPTY},
									{EMPTY, SQ_BLOCK, SQ_BLOCK, EMPTY},
									{EMPTY, SQ_BLOCK, SQ_BLOCK, EMPTY},
									{EMPTY, EMPTY,    EMPTY,    EMPTY}}},

/* LONG_BLOCK_DATA */             { {{EMPTY,LONG_BLOCK,EMPTY,  EMPTY},
									   {EMPTY,LONG_BLOCK,EMPTY,  EMPTY},
									   {EMPTY,LONG_BLOCK,EMPTY,  EMPTY},
									   {EMPTY,LONG_BLOCK,EMPTY,  EMPTY}},

								   {{EMPTY,      EMPTY,      EMPTY,      EMPTY},
									{LONG_BLOCK, LONG_BLOCK, LONG_BLOCK, LONG_BLOCK},
									{EMPTY,      EMPTY,      EMPTY,      EMPTY},
									{EMPTY,      EMPTY,      EMPTY,      EMPTY}},

								      {{EMPTY,LONG_BLOCK,EMPTY,  EMPTY},
									   {EMPTY,LONG_BLOCK,EMPTY,  EMPTY},
									   {EMPTY,LONG_BLOCK,EMPTY,  EMPTY},
									   {EMPTY,LONG_BLOCK,EMPTY,  EMPTY}},

								  
								   {{EMPTY,      EMPTY,      EMPTY,      EMPTY},
									{LONG_BLOCK, LONG_BLOCK, LONG_BLOCK, LONG_BLOCK},
									{EMPTY,      EMPTY,      EMPTY,      EMPTY},
									{EMPTY,      EMPTY,      EMPTY,      EMPTY}}},

/* T_BLOCK_DATA */               { {{EMPTY,T_BLOCK,EMPTY,    EMPTY},
									{EMPTY,T_BLOCK,T_BLOCK,  EMPTY},
									{EMPTY,T_BLOCK,EMPTY,    EMPTY},
									{EMPTY,EMPTY,  EMPTY,    EMPTY}},

								   {{EMPTY,  EMPTY,  EMPTY,    EMPTY},
									{T_BLOCK,T_BLOCK,T_BLOCK,  EMPTY},
									{EMPTY,  T_BLOCK,EMPTY,    EMPTY},
									{EMPTY,EMPTY,  EMPTY,    EMPTY}},

								  { {EMPTY,  T_BLOCK,  EMPTY,    EMPTY},
									{T_BLOCK,T_BLOCK,  EMPTY,    EMPTY},
									{EMPTY,  T_BLOCK,  EMPTY,    EMPTY},
									{EMPTY,  EMPTY,    EMPTY,    EMPTY}},

								   {{EMPTY,  T_BLOCK,  EMPTY,    EMPTY},
									{T_BLOCK,T_BLOCK,  T_BLOCK,  EMPTY},
									{EMPTY,  EMPTY,    EMPTY,    EMPTY},
									{EMPTY,  EMPTY,    EMPTY,    EMPTY}}},

/*S_BLOCK_DATA*/                 { {{EMPTY,S_BLOCK,EMPTY,  EMPTY},
									{EMPTY,S_BLOCK,S_BLOCK,EMPTY},
									{EMPTY,EMPTY,  S_BLOCK,EMPTY},
									{EMPTY,EMPTY,  EMPTY,  EMPTY}},

								   {{EMPTY,   EMPTY,   EMPTY,  EMPTY},
									{EMPTY,   EMPTY,   S_BLOCK,S_BLOCK},
									{EMPTY,   S_BLOCK, S_BLOCK,  EMPTY},
									{EMPTY,   EMPTY,   EMPTY,  EMPTY}},

								   {{EMPTY,S_BLOCK,EMPTY,  EMPTY},
									{EMPTY,S_BLOCK,S_BLOCK,EMPTY},
									{EMPTY,EMPTY,  S_BLOCK,EMPTY},
									{EMPTY,EMPTY,  EMPTY,  EMPTY}},

								    {{EMPTY,   EMPTY,   EMPTY,  EMPTY},
									{EMPTY,   EMPTY,   S_BLOCK,S_BLOCK},
									{EMPTY,   S_BLOCK, S_BLOCK,  EMPTY},
									{EMPTY,   EMPTY,   EMPTY,  EMPTY}}},

/* Z_BLOCK_DATA*/                { {{EMPTY, EMPTY,    Z_BLOCK,  EMPTY},
									{EMPTY, Z_BLOCK,  Z_BLOCK,  EMPTY},
									{EMPTY, Z_BLOCK,  EMPTY,    EMPTY},
									{EMPTY, EMPTY,    EMPTY,    EMPTY}},

								   {{EMPTY,   Z_BLOCK,   Z_BLOCK,  EMPTY},
									{EMPTY,   EMPTY,     Z_BLOCK,  Z_BLOCK},
									{EMPTY,   EMPTY,     EMPTY,    EMPTY},
									{EMPTY,   EMPTY,     EMPTY,    EMPTY}},

								   {{EMPTY, EMPTY,    Z_BLOCK,  EMPTY},
									{EMPTY, Z_BLOCK,  Z_BLOCK,  EMPTY},
									{EMPTY, Z_BLOCK,  EMPTY,    EMPTY},
									{EMPTY, EMPTY,    EMPTY,    EMPTY}},

								     {{EMPTY,   Z_BLOCK,   Z_BLOCK,  EMPTY},
									{EMPTY,   EMPTY,     Z_BLOCK,  Z_BLOCK},
									{EMPTY,   EMPTY,     EMPTY,    EMPTY},
									{EMPTY,   EMPTY,     EMPTY,    EMPTY}}}};

//game state values
const int NEED_NEW_BLOCK = 0;
const int CHECK_GAMEOVER = 1;
const int BLOCK_FALLING  = 2;
const int SET_BLOCK      = 3;
const int DESTROY_BLOCKS = 4;
const int CHECK_BOARD    = 5;
const int FLICKER_LINES  = 6;
const int TITLE_SCREEN   = 7;
const int GAME_OVER      = 8;

//used for directions for moving block
const int RIGHT = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int NONE  = 3;

const int CLOCKWISE      = -1;
const int ANTI_CLOCKWISE = 1;

const int OFFSET = 16;

const int BLOCK_SIZE = 18;