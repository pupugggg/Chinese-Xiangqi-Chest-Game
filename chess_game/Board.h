#include"GameParameter.h"
#include"Chess.h"
#include"Manager.h"
#ifndef Board_H
#define Board_H



class Chess;
class Empty;
class General;
class Soldier;
class Elephant;
class Car;
class Hourse;
class Cannon;
class Minion;

class Board {
public:
	int BId;
	static Board *instance;
	Board();
	void init();
	vector<vector<Chess*>> boardState;
	vector<vector<vector<Chess*>>> record;
	Chess* constructorInvoker(int);
	void replace(Chess*,Chess*);
	void pushBoard();
};

#endif