#include"InputSystem.h"
InputSystem* InputSystem::Instance;

InputSystem::InputSystem()
{
	init();
}

void InputSystem::init()
{
	for (int i = 0; i < 8; i++)
		keyState[i] = false;
	cursor = Vector2(0, 9);
}

void InputSystem::keyUpdate()
{
	for (int i = 0; i < 8; i++)
		keyState[i] = false;
	char tmp = _getch();
	if (tmp == 27)
	{
		keyState[vaildiInput::ESC] = true;
#ifndef GET_CH_ONCE
		tmp = _getch();
#endif 
	}
	else if (tmp == 13)
	{
		keyState[vaildiInput::enter] = true;
#ifndef GET_CH_ONCE
		tmp = _getch();
#endif 
	}
	else if (tmp == 44)
	{
		keyState[vaildiInput::reg] = true;
#ifndef GET_CH_ONCE
		tmp = _getch();
#endif 
		Manager::instance-> withdraw();
	}
	else if (tmp == 46)
	{
		keyState[vaildiInput::ret] = true;
#ifndef GET_CH_ONCE
		tmp = _getch();
#endif 
			Manager::instance->restart();
	}
	else
	{
		switch (tmp=_getch())
		{
		case 72:
			//up
			keyState[vaildiInput::upArrow] = true;
			break;
		case 80:
			//down
			keyState[vaildiInput::downArrow] = true;

			break;
		case 77:
			//right
			keyState[vaildiInput::rightArrow] = true;

			break;
		case 75:
			//left
			keyState[vaildiInput::leftArrow] = true;
			break;
		}
	}
}

void InputSystem::cursorUpdate()
{
	if (keyState[vaildiInput::upArrow])
	{
		if (cursor.y - 1 >= 0)
			cursor.y -= 1;
	}
	else if (keyState[vaildiInput::downArrow])
	{
		if (cursor.y + 1 < GameParameter::BOARDHEIGHT)
			cursor.y += 1;
	}
	else if (keyState[vaildiInput::rightArrow])
	{
		if (cursor.x + 1 < GameParameter::BOARDWIDTH)
			cursor.x += 1;
	}
	else if (keyState[vaildiInput::leftArrow])
	{
		if (cursor.x - 1 >= 0)
			cursor.x -= 1;
	}
}

void InputSystem::choose()
{
	Vector2 tempCur = cursor;
	bool flag = false;
	char tmp;
	while (!flag)
	{
		for (int i = 0; i < 6; i++)
			keyState[i] = false;
		tmp = _getch();
		if (tmp == 27)
		{
			flag = true;
#ifndef GET_CH_ONCE
			tmp = _getch();
#endif 
			Display::Instance->erasePath(tempCur);
			Display::Instance->eraseInfo();
		}
		else if (tmp == 13)
		{
#ifndef GET_CH_ONCE
			tmp = _getch();
#endif 
			for (int i = 0; i < Board::instance->boardState[tempCur.y][tempCur.x]->availablePos.size(); i++)
				if (Board::instance->boardState[tempCur.y][tempCur.x]->availablePos[i].x == cursor.x && Board::instance->boardState[tempCur.y][tempCur.x]->availablePos[i].y == cursor.y)
				{
					Display::Instance->erasePath(tempCur);
					Display::Instance->moveChess(tempCur);
					Display::Instance->eraseInfo();
					Board::instance->replace(Board::instance->boardState[tempCur.y][tempCur.x], Board::instance->boardState[cursor.y][cursor.x]);
					Display::Instance->drawRecord(tempCur);
					Manager::instance->round=!Manager::instance->round;
					flag = true;
					Board::instance->pushBoard();
					//cursor = Vector2(0, 9);
					break;
				}
		}
		else
		{
			switch (tmp = _getch())
			{
			case 72:
				//up
				keyState[vaildiInput::upArrow] = true;
				
				break;
			case 80:
				//down
				keyState[vaildiInput::downArrow] = true;
				
				break;
			case 77:
				//right
				keyState[vaildiInput::rightArrow] = true;
				
				break;
			case 75:
				//left
				keyState[vaildiInput::leftArrow] = true;
				
				break;
			}
			
			cursorUpdate();
			Display::Instance->drawCursor(InputSystem::Instance->cursor);
		}
		
	}
	
	
}