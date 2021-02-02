#pragma once
#include"GameParameter.h"
#include"InputSystem.h"
#include"Displayer.h"
#include"ChessBot.h"
class Manager {
public:
	void start();
	static Manager *instance;
	int round;
	int checkMate;
	Manager();
	void roundCtrl();
	void checkMateCheck();
	void winConditionCheck();
	void withdraw();
	void restart();
	void routeSelect();
	bool gameOver;
	clock_t startT,endT;
	int option;
	int startOption;
	void save();
	void load();
	void quit();
	void Title();
	void doOption();
	void doStartOption();
	void openMenu();
	void releaseBoard();
	bool Botmode;
private:
	void init();
	void update();
	void render();
};
