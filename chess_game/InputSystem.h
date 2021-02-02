#pragma once
#include"GameParameter.h"
#include"Board.h"
enum vaildiInput
{
	upArrow=0,downArrow=1,leftArrow=2,rightArrow=3,enter=4,ESC=5,reg=6,ret=7
};

class InputSystem
{
public:
	static InputSystem* Instance;
	Vector2 cursor;
	void cursorUpdate();
	void keyUpdate();
	bool keyState[6];
	void choose();
	InputSystem();
private:
	void init();
};