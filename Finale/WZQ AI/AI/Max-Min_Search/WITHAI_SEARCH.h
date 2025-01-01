
#pragma once
#include "C:\\Users\\H\\CLionProjects\\WZQ AI\\CHESS_GAME\\CHESS_GAME_SOURCE.h"
#include "Max-Min_Search.h"
#include "Zorbists.h"
#include <graphics.h>


bool AI_Finish_Put_Process(Chess_Board &p,int AIDepth);
bool Chess_Process_With_AI(Chess_Board &p,int Screen_Width,int Screen_Height,int IsFirstPut,int AIDepth,int QUICK_Limit,bool EnableQUICK,bool EnableHash);
