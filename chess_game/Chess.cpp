#include"Chess.h"
bool Chess::operator==(const Chess& source)
{
	if (id == source.id)
		return true;
	else
		return false;
}
bool Chess::empty(Vector2 pos)
{
	if (pos.x >= 0 && pos.y >= 0 && pos.x < GameParameter::BOARDWIDTH && pos.y < GameParameter::BOARDHEIGHT)
		return (Board::instance->boardState[pos.y][pos.x]->id == 0);
	else
		return false;
}
bool Chess::movable(Vector2 pos)
{
	if (pos.x >= 0 && pos.y >= 0 && pos.x < GameParameter::BOARDWIDTH && pos.y < GameParameter::BOARDHEIGHT)
	{
		if (id < 8)
		{
			if ((id == 1 || id == 2) && pos.x >= GameParameter::PALACELEFT && pos.x <= GameParameter::PALACERIGHT && pos.y <= GameParameter::BLACKPALACETOP)
			{
				if ((empty(pos)) || (Board::instance->boardState[pos.y][pos.x]->id > 7))
					return true;
			}
			else if (id == 1 || id == 2)
				return false;
			else if ((empty(pos)) || (Board::instance->boardState[pos.y][pos.x]->id > 7))
				return true;
		}
		else
		{
			if ((id == 8 || id == 9) && pos.x >= GameParameter::PALACELEFT && pos.x <= GameParameter::PALACERIGHT && pos.y >= GameParameter::REDPALACETOP)
			{
				if ((empty(pos)) || (Board::instance->boardState[pos.y][pos.x]->id < 8))
					return true;
			}
			else if (id == 8 || id == 9)
				return false;
			else if ((empty(pos)) || (Board::instance->boardState[pos.y][pos.x]->id < 8))
				return true;
		}
	}
	return false;
}

Chess::Chess(int in)
{
	id = in;
	iconSelector(in);
}

Chess::Chess()
{
	
	id = 0;
	icon = "";
}

void Chess::iconSelector(int in)
{
	switch (in)
	{
		case 1:
			icon = "將";
			break;
		case 2:
			icon = "士";
			break;
		case 3:
			icon = "象";
			break;
		case 4:
			icon = "車";
			break;
		case 5:
			icon = "馬";
			break;
		case 6:
			icon = "包";
			break;
		case 7:
			icon = "卒";
			break;
		case 8:
			icon = "帥";
			break;
		case 9:
			icon = "仕";
			break;
		case 10:
			icon = "相";
			break;
		case 11:
			icon = "車";
			break;
		case 12:
			icon = "傌";
			break;
		case 13:
			icon = "炮";
			break;
		case 14:
			icon = "兵";
			break;
		default:
			icon = "";
			break;
	}
}

void Chess::cleanAvailablePos() {
	availablePos.clear();
}