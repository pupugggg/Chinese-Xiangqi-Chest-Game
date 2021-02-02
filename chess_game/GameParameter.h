#pragma once
#include"Vector2.h"
#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<conio.h>
#include<ctime>
#include<string>
#include <Windows.h>	// Console window ¬ÛÃö¾Þ§@
#include <stdio.h>
//optional for some computer
/********************************************************/
//#define GET_CH_ONCE
/*******************************************************/
class GameParameter {
public:
	static const int BOARDWIDTH;
	static const int BOARDHEIGHT;
	static const float FRAMERATE;
	static const int REDRIVERSIDE;
	static const int BLACKRIVERSIDE;
	static const int PALACELEFT;
	static const int PALACERIGHT;
	static const int REDPALACETOP;
	static const int BLACKPALACETOP;
	static const int OFFSET_BOARD_X;
	static const int OFFSET_BOARD_Y;
	static const int OFFSET_RECORD_X;
	static const int OFFSET_RECORD_Y;
	static const int OFFSET_INFO_TURN_X;
	static const int OFFSET_INFO_TURN_Y;
	static const int OFFSET_INFO_CHESS_X;
	static const int OFFSET_INFO_CHESS_Y;
	static const int AI_ROUND;
	static const int PLAYER_ROUND;
};

